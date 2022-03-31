#include "engine/audio.h"

#include "engine/array.h"
#include "engine/wav-reader.h"
#include "engine/geometry.h"
#include "engine/strings.h"

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MA_NO_GENERATION
#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#define MA_ENABLE_ALSA 
#define MA_ENABLE_PULSEAUDIO 
#define MA_ENABLE_WASAPI 
#include "miniaudio/miniaudio.h"

#ifdef __linux
#include "stddef.h"
#endif

#ifdef _WIN32
#include "stdint.h"
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

typedef struct DelayedSound{
	Sound sound;
	int ticksLeft;
}DelayedSound;

typedef struct SoundData{
	int16_t *data;
	int framesLength;
	char *name;
}SoundData;

SoundData soundData[255];

int soundDataLength = 0;

Array sounds;
Array delayedSounds;

float volumes[2];

int soundFilesLength;
int loadedSoundFiles = 0;

ma_result result;
ma_device_config deviceConfig;
ma_device device;

void data_callback(ma_device* device_p, void* output_p, const void* input_p, ma_uint32 frameCount){

	float *outputF32_p = (float *)output_p;

	//mix sound frames
	for(int i = 0; i < sounds.length; i++){

		Sound *sound_p = Array_getItemPointerByIndex(&sounds, i);
		SoundData *soundData_p = &soundData[sound_p->soundDataIndex];
		
		if(sound_p->stopped
		|| sound_p->soundDataIndex >= loadedSoundFiles){
			continue;
		}

		sound_p->currentFrame += frameCount;

		if(sound_p->currentFrame + frameCount > soundData_p->framesLength - frameCount){
			if(sound_p->loop){
				sound_p->currentFrame = 0;
			}else{
				Array_removeItemByIndex(&sounds, i);
				i--;
				continue;
			}
		}

		for(int j = 0; j < frameCount * NUMBER_OF_CHANNELS; j++){
			outputF32_p[j] += (((float)soundData_p->data[sound_p->currentFrame * NUMBER_OF_CHANNELS + j]) / 32767.0) * sound_p->volume * volumes[sound_p->type] * CONSTANT_VOLUME_FACTOR;
		}
	
	}

}

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
//#ifdef __linux__
	//load audio on seperate thread
	//loadAudioFiles(NULL);
	//pthread_t loadThread;
	//pthread_create(&loadThread, NULL, loadAudioFiles, NULL);
//#endif
//#ifdef _WIN32
	loadAudioFiles(NULL);
//#endif

	//init sound and volume handling
	Array_init(&sounds, sizeof(Sound));

	volumes[AUDIO_SOUND_TYPE_SFX] = 1.0;
	volumes[AUDIO_SOUND_TYPE_MUSIC] = 1.0;

	//init miniaudio

	deviceConfig = ma_device_config_init(ma_device_type_playback);
    //deviceConfig.playback.format   = ma_format_s16;
    deviceConfig.playback.format   = ma_format_f32;
    deviceConfig.playback.channels = NUMBER_OF_CHANNELS;
    deviceConfig.sampleRate        = SAMPLE_RATE;
    deviceConfig.dataCallback      = data_callback;

	if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
		printf("Could not initialize miniaudio device!\n");
    }

	ma_device_start(&device);

}

void Audio_setVolume(float volume, enum Audio_SoundTypeEnum soundType){

	volumes[soundType] = volume;

}

float Audio_getVolume(enum Audio_SoundTypeEnum soundType){

	return volumes[soundType];

}

size_t Audio_playSound(char *soundName, float volume, bool loop, enum Audio_SoundTypeEnum soundType, int delay){

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

	Sound *sound_p;

	if(delay == 0){
		sound_p = Array_addItem(&sounds);
	}else{

		//printf("obobo\n");

		DelayedSound *delayedSound_p = Array_addItem(&delayedSounds);

		delayedSound_p->ticksLeft = delay;
		sound_p = &delayedSound_p->sound;

		//printf("nanana\n");

	}

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

size_t Audio_playSoundVariation(char *soundName, int variations, float volume, bool loop, enum Audio_SoundTypeEnum soundType, int delay){

	char variationName[STRING_SIZE];

	int variationNumber = (int)((float)variations * getRandom()) + 1;

	memset(variationName, 0, sizeof(char) * STRING_SIZE);
	sprintf(variationName, "%s-%i", soundName, variationNumber);

	return Audio_playSound(variationName, volume, loop, soundType, delay);

}

void Audio_updateDelayedSounds(){
	
	for(int i = 0; i < delayedSounds.length; i++){

		DelayedSound *delayedSound_p = Array_getItemPointerByIndex(&delayedSounds, i);

		delayedSound_p->ticksLeft--;

		if(delayedSound_p->ticksLeft <= 0){

			//printf("GOT HERE\n");

			Sound *sound_p = Array_addItem(&sounds);

			*sound_p = delayedSound_p->sound;

			Array_removeItemByIndex(&delayedSounds, i);
			i--;
		
		}
	
	}

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
