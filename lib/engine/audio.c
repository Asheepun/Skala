#include "engine/audio.h"

#include "engine/array.h"
#include "engine/wav-reader.h"
#include "engine/geometry.h"
#include "engine/strings.h"

#ifdef __linux
#include "alsa/asoundlib.h"
#include "stddef.h"
#include "pthread.h"
#endif

#ifdef _WIN32
#include "stdint.h"
#include "Windows.h"
#endif

#include "stdarg.h"
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

int soundFilesLength;
int loadedSoundFiles = 0;

#ifdef __linux__
int device;
int dir;
snd_pcm_t *handle;
snd_pcm_hw_params_t *params;
snd_pcm_status_t *status;

//pthread_mutex_t soundMutex = PTHREAD_MUTEX_INITIALIZER;

int firstFramesLeft = 0;
int framesLeft = 0;
int deltaFrames = 0;
int lastDeltaFrames = 0;

int preBurnLoops = 10;
int loopCount = 0;
int burnLoops = 0;

void *renderLoop(void *ptr){

	while(true){

		snd_pcm_status(handle, status);

		framesLeft = snd_pcm_status_get_avail(status);

		if(firstFramesLeft == 0){
			firstFramesLeft = framesLeft;
		}

		int framesToWrite = 4 * PERIOD_SIZE;

		deltaFrames = abs(firstFramesLeft - framesLeft);
		lastDeltaFrames = deltaFrames;

		int deltaDeltaFrames = abs(deltaFrames - lastDeltaFrames);

		if(deltaDeltaFrames == 0
		&& deltaFrames < framesToWrite){
			burnLoops = 10;
		}

		loopCount++;

		//printf("%i\n", deltaFrames);
		//printf("framesToWrite: %i\n", deltaFrames);

		if(deltaFrames < framesToWrite
		//|| deltaDeltaFrames == 0
		//&& deltaFrames < framesToWrite){
		//|| deltaDeltaFrames == 0){
		|| burnLoops > 0){

			burnLoops--;

			//pthread_mutex_lock(&soundMutex);

			//mix sound frames
			int16_t mixedFrames[framesToWrite * NUMBER_OF_CHANNELS];
			memset(mixedFrames, 0, framesToWrite * NUMBER_OF_CHANNELS * sizeof(int16_t));

			for(int i = 0; i < sounds.length; i++){

				Sound *sound_p = Array_getItemPointerByIndex(&sounds, i);
				SoundData *soundData_p = &soundData[sound_p->soundDataIndex];
				
				if(sound_p->stopped
				|| sound_p->soundDataIndex >= loadedSoundFiles){
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

			//pthread_mutex_unlock(&soundMutex);

			if(loopCount < preBurnLoops){
				memset(mixedFrames, 0, framesToWrite * NUMBER_OF_CHANNELS * sizeof(int16_t));
			}

			//if(deltaDeltaFrames == 0)
			
			//write frames to sound card
			snd_pcm_writei(handle, mixedFrames, framesToWrite);

		}

		int sleepTime = 1000000.0 * PERIOD_SIZE / (float)SAMPLE_RATE;

		usleep(sleepTime);
		
	}

	return NULL;

}
#endif

#ifdef _WIN32

HWAVEOUT hWaveOut;
WAVEFORMATEX wfx;
MMRESULT result;

#define FRAMES_PER_WRITE (SAMPLE_RATE / 50)
#define FRAMES_PER_HEADER SAMPLE_RATE / 100
#define NUMBER_OF_HEADERS 1000

WAVEHDR headers[NUMBER_OF_HEADERS];
int16_t mixedFrameBuffers[NUMBER_OF_HEADERS][FRAMES_PER_WRITE * NUMBER_OF_CHANNELS];
int currentHeader = 0;

int writtenFrames = 0;

DWORD WINAPI renderLoop(LPVOID argument){

	while(true){

		MMTIME currentPosition;
		waveOutGetPosition(hWaveOut, &currentPosition, sizeof(MMTIME));

		int deltaFrames = writtenFrames - (currentPosition.u.sample / NUMBER_OF_CHANNELS / sizeof(int16_t));

		printf("---\n");
		printf("%i\n", currentPosition.u.sample / NUMBER_OF_CHANNELS / sizeof(int16_t));
		printf("%i\n", writtenFrames);
		printf("%i\n", deltaFrames);
		printf("%i\n", sounds.length);

		//int framesToWrite = FRAMES_PER_WRITE - deltaFrames;
		int framesToWrite = FRAMES_PER_WRITE;

		//if(framesToWrite < 0){
			//framesToWrite = 0;
		//}

		while(deltaFrames < framesToWrite * 2){

			//mix sound frames
			int16_t *mixedFrames = mixedFrameBuffers[currentHeader % NUMBER_OF_HEADERS];
			memset(mixedFrames, 0, sizeof(int16_t) * NUMBER_OF_CHANNELS * FRAMES_PER_WRITE);

			for(int i = 0; i < sounds.length; i++){

				Sound *sound_p = Array_getItemPointerByIndex(&sounds, i);
				SoundData *soundData_p = &soundData[sound_p->soundDataIndex];
				
				if(sound_p->stopped
				|| sound_p->soundDataIndex >= loadedSoundFiles){
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

			//WINDOWS STUFF
			WAVEHDR *header_p = &headers[currentHeader % NUMBER_OF_HEADERS];
			currentHeader++;

			ZeroMemory(header_p, sizeof(WAVEHDR));
			header_p->dwBufferLength = NUMBER_OF_CHANNELS * framesToWrite * sizeof(int16_t);
			header_p->lpData = (char *)mixedFrames;

			if(currentHeader >= NUMBER_OF_HEADERS){
				waveOutUnprepareHeader(hWaveOut, header_p, sizeof(WAVEHDR));
			}

			waveOutPrepareHeader(hWaveOut, header_p, sizeof(WAVEHDR));

			waveOutWrite(hWaveOut, header_p, sizeof(WAVEHDR));

			writtenFrames += framesToWrite;

			//re check delta frames
			MMTIME currentPosition;
			waveOutGetPosition(hWaveOut, &currentPosition, sizeof(MMTIME));

			deltaFrames = writtenFrames - (currentPosition.u.sample / NUMBER_OF_CHANNELS / sizeof(int16_t));

		}
	
	}

}

#endif

void *loadAudioFiles(void *ptr){

	for(int i = 0; i < soundFilesLength; i++){

		SoundData *soundData_p = &soundData[i];

		char path[255];

		sprintf(path, "assets/audio/%s.wav", soundData_p->name);

		soundData_p->data = WavReader_getDataFromWavFile(path, &soundData_p->framesLength);

		printf("Loaded WAV file: %s\n", soundData_p->name);

		loadedSoundFiles++;
		
	}

}

void Audio_init(char **soundFiles, int soundFilesLengthIn){

	soundFilesLength = soundFilesLengthIn;

	//set names for audio before load
	for(int i = 0; i < soundFilesLength; i++){

		SoundData *soundData_p = &soundData[i];

		soundData_p->name = soundFiles[i];

	}

	soundDataLength = soundFilesLength;

	//load audio files on seperate thread
#ifdef __linux__
	//load audio on seperate thread
	//loadAudioFiles(NULL);
	pthread_t loadThread;
	pthread_create(&loadThread, NULL, loadAudioFiles, NULL);
#endif
#ifdef _WIN32
	loadAudioFiles(NULL);
#endif

	//init sound and volume handling
	Array_init(&sounds, sizeof(Sound));

	volumes[AUDIO_SOUND_TYPE_SFX] = 1.0;
	volumes[AUDIO_SOUND_TYPE_MUSIC] = 1.0;

	//init native sound device
#ifdef __linux__
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
#endif
#ifdef _WIN32
	wfx.nSamplesPerSec = SAMPLE_RATE;
	wfx.wBitsPerSample = 16;
	wfx.nChannels = NUMBER_OF_CHANNELS;

	wfx.cbSize = 0;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nBlockAlign = (wfx.wBitsPerSample >> 3) * wfx.nChannels;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR){
		fprintf(stderr, "unable to open WAVE_MAPPER device\n");
		ExitProcess(1);
	}
#endif

	//start render loop on seperate thread
#ifdef __linux__
	pthread_t renderThread;
	pthread_create(&renderThread, NULL, renderLoop, NULL);
#endif
#ifdef _WIN32
	DWORD threadID;
	HANDLE thread = CreateThread(
		NULL, 0, renderLoop, NULL, 0, &threadID
	);
#endif

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

	//pthread_mutex_lock(&soundMutex);

	Sound *sound_p = Array_addItem(&sounds);

	//pthread_mutex_unlock(&soundMutex);

	EntityHeader_init(&sound_p->entityHeader);

	sound_p->currentFrame = 0;
	sound_p->soundDataIndex = soundDataIndex;
	sound_p->volume = volume;
	sound_p->loop = loop;
	sound_p->type = soundType;
	sound_p->stopped = false;

	return sound_p->entityHeader.ID;

}

size_t Audio_playSoundVariation(char *soundName, int variations, float volume, bool loop, enum Audio_SoundTypeEnum soundType){

	char variationName[STRING_SIZE];

	int variationNumber = (int)((float)variations * getRandom()) + 1;

	memset(variationName, 0, sizeof(char) * STRING_SIZE);
	sprintf(variationName, "%s-%i", soundName, variationNumber);

	return Audio_playSound(variationName, volume, loop, soundType);

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
