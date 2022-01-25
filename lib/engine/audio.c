#include "engine/audio.h"

#include "engine/array.h"
#include "engine/wav-reader.h"

#include "alsa/asoundlib.h"

#include "pthread.h"
#include "stdarg.h"
#include "stddef.h"
#include "string.h"
#include "stdio.h"
#include "time.h"
#include "unistd.h"
#include "math.h"

typedef struct Sound{
	EntityHeader entityHeader;
	int currentFrame;
	int soundDataIndex;
	float volume;
	bool loop;
	bool stopped;
	enum Audio_SoundTypeEnum type;
}Sound;

typedef struct SoundData{
	int16_t *data;
	int framesLength;
	char *name;
}SoundData;

SoundData soundData[255];

int soundDataLength = 0;

Array sounds;

float volumes[2];

int device;
int dir;
snd_pcm_t *handle;
snd_pcm_hw_params_t *params;
snd_pcm_status_t *status;

pthread_mutex_t soundMutex = PTHREAD_MUTEX_INITIALIZER;

int firstFramesLeft = 0;
int framesLeft = 0;

void *renderLoop(void *ptr){

	while(true){

		snd_pcm_status(handle, status);

		framesLeft = snd_pcm_status_get_avail(status);

		if(firstFramesLeft == 0){
			firstFramesLeft = framesLeft;
		}

		int framesToWrite = 4 * PERIOD_SIZE;

		if(abs(firstFramesLeft - framesLeft) < framesToWrite){

			pthread_mutex_lock(&soundMutex);

			//mix sound frames
			int16_t mixedFrames[framesToWrite * NUMBER_OF_CHANNELS];
			memset(mixedFrames, 0, framesToWrite * NUMBER_OF_CHANNELS * sizeof(int16_t));

			for(int i = 0; i < sounds.length; i++){

				Sound *sound_p = Array_getItemPointerByIndex(&sounds, i);
				SoundData *soundData_p = &soundData[sound_p->soundDataIndex];
				
				if(sound_p->stopped){
					continue;
				}

				sound_p->currentFrame += framesToWrite;

				if(sound_p->currentFrame + framesToWrite > soundData_p->framesLength - framesToWrite){
					if(sound_p->loop){
						sound_p->currentFrame = 0;
					}else{
						Array_removeItemByIndex(&sounds, i);
						i--;
						continue;
					}
				}

				for(int j = 0; j < framesToWrite * NUMBER_OF_CHANNELS; j++){
					mixedFrames[j] += (int16_t)((float)soundData_p->data[sound_p->currentFrame * NUMBER_OF_CHANNELS + j] * sound_p->volume * volumes[sound_p->type] * CONSTANT_VOLUME_FACTOR);
				}
			
			}

			pthread_mutex_unlock(&soundMutex);
			
			//write frames to sound card
			snd_pcm_writei(handle, mixedFrames, framesToWrite);

		}

		int sleepTime = 1000000.0 * PERIOD_SIZE / (float)SAMPLE_RATE;

		usleep(sleepTime);
		
	}

	return NULL;

}

void Audio_init(char **soundFiles, int soundFilesLength){

	for(int i = 0; i < soundFilesLength; i++){

		SoundData *soundData_p = &soundData[i];

		soundData_p->name = soundFiles[i];

		char path[255];

		sprintf(path, "assets/audio/%s.wav", soundFiles[i]);

		soundData_p->data = WavReader_getDataFromWavFile(path, &soundData_p->framesLength);

		printf("Loaded WAV file: %s\n", soundData_p->name);
		
	}
	
	soundDataLength = soundFilesLength;

	Array_init(&sounds, sizeof(Sound));

	volumes[AUDIO_SOUND_TYPE_SFX] = 1.0;
	volumes[AUDIO_SOUND_TYPE_MUSIC] = 1.0;

	device = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);

	snd_pcm_hw_params_alloca(&params);

	snd_pcm_hw_params_any(handle, params);

	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

	snd_pcm_hw_params_set_channels(handle, params, NUMBER_OF_CHANNELS);

	snd_pcm_hw_params_set_rate_near(handle, params, &SAMPLE_RATE, &dir);

	snd_pcm_hw_params_set_period_size_near(handle, params, (snd_pcm_uframes_t* )&PERIOD_SIZE, &dir);

	snd_pcm_hw_params(handle, params);

	snd_pcm_status_malloc(&status);

	pthread_t thread;
	pthread_create(&thread, NULL, renderLoop, NULL);

}

void Audio_setVolume(float volume, enum Audio_SoundTypeEnum soundType){

	volumes[soundType] = volume;

}

float Audio_getVolume(enum Audio_SoundTypeEnum soundType){

	return volumes[soundType];

}

size_t Audio_playSound(char *soundName, float volume, bool loop, enum Audio_SoundTypeEnum soundType){

	int soundDataIndex = -1;
	for(int i = 0; i < soundDataLength; i++){
		if(strcmp(soundData[i].name, soundName) == 0){
			soundDataIndex = i;
			break;
		}
	}

	if(soundDataIndex == -1){
		printf("No sound with name: %s\n", soundName);
		return -1;
	}

	pthread_mutex_lock(&soundMutex);

	Sound *sound_p = Array_addItem(&sounds);

	pthread_mutex_unlock(&soundMutex);

	EntityHeader_init(&sound_p->entityHeader);

	sound_p->currentFrame = 0;
	sound_p->soundDataIndex = soundDataIndex;
	sound_p->volume = volume;
	sound_p->loop = loop;
	sound_p->type = soundType;
	sound_p->stopped = false;

	return sound_p->entityHeader.ID;

}

void Audio_stopSoundByID(size_t ID){

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);

	sound_p->stopped = true;

}

void Audio_resumeSoundByID(size_t ID){

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);

	sound_p->stopped = false;

}

void Audio_killSoundByID(size_t ID){

	Array_removeItemByID(&sounds, ID);

}

float Audio_getSoundVolumeByID(size_t ID){

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);

	return sound_p->volume;
	
}

void Audio_setSoundVolumeByID(size_t ID, float newVolume){

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);
	
	sound_p->volume = newVolume;
	
}

void Audio_increaseSoundVolumeByID(size_t ID, float increment){

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);
	
	sound_p->volume += increment;

	if(sound_p->volume > 1){
		sound_p->volume = 1;
	}
	if(sound_p->volume < 0){
		sound_p->volume = 0;
	}
	
}

void Audio_decreaseSoundVolumeByID(size_t ID, float decrement){

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);
	
	sound_p->volume -= decrement;

	if(sound_p->volume > 1){
		sound_p->volume = 1;
	}
	if(sound_p->volume < 0){
		sound_p->volume = 0;
	}
	
}

void Audio_setSoundTimeByID(size_t ID, int newTime){

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);
	
	sound_p->currentFrame = newTime;

}

char *Audio_getSoundNameByID(size_t ID){

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);

	SoundData *soundData_p = &soundData[sound_p->soundDataIndex];

	return soundData_p->name;

}
