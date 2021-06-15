#include "engine/audio.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

#include "stdio.h"
#include "pthread.h"
#include "engine/array.h"

#define SAMPLE_FORMAT ma_format_f32
#define SAMPLE_RATE 48000
#define CHANNEL_COUNT 2

typedef struct Sound{
	EntityHeader entityHeader;
	int currentFrame;
	int decoderIndex;
	float volume;
	bool loop;
	bool stopped;
	enum Audio_SoundTypeEnum type;
}Sound;

ma_result result;
ma_decoder_config decoderConfig;
ma_device device;
ma_device_config deviceConfig;

pthread_mutex_t soundMutex = PTHREAD_MUTEX_INITIALIZER;

ma_decoder decoders[255];
char *decoderNames[255];

int decodersLength = 0;

Array sounds;

float volumes[2];

void data_callback(ma_device* device_p, void* output_p, const void* input_p, ma_uint32 frameCount){

	pthread_mutex_lock(&soundMutex);

	float *outputF32_p = (float *)output_p;
	MA_ASSERT(device_p->playback.format == SAMPLE_FORMAT);

	for(int i = 0; i < sounds.length; i++){

		Sound *sound_p = Array_getItemPointerByIndex(&sounds, i);
		ma_decoder *decoder_p = &decoders[sound_p->decoderIndex];

		if(sound_p->stopped){
			continue;
		}

		ma_decoder_seek_to_pcm_frame(decoder_p, sound_p->currentFrame);

		float tmpBuffer[4096];

		int readFrames = ma_decoder_read_pcm_frames(decoder_p, tmpBuffer, frameCount);
		sound_p->currentFrame += readFrames;

		for(int i = 0; i < readFrames * CHANNEL_COUNT; i++){
			outputF32_p[i * CHANNEL_COUNT] += tmpBuffer[i * CHANNEL_COUNT] * sound_p->volume * volumes[sound_p->type] * 1;
		}

		if(readFrames < frameCount){
			if(sound_p->loop){
				sound_p->currentFrame = 0;
			}else{
				Array_removeItemByIndex(&sounds, i);
				i--;
			}
		}
	
	}

	for(int i = 0; i < frameCount * CHANNEL_COUNT; i++){
		outputF32_p[i] /= 1;
	}

	pthread_mutex_unlock(&soundMutex);

}

void Audio_init(char **soundFiles, int soundFilesLength){

	decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);

	for(int i = 0; i < soundFilesLength; i++){

		ma_decoder *decoder_p = &decoders[i];

		decoderNames[i] = soundFiles[i];

		char path[255];

		sprintf(path, "assets/audio/%s.wav", soundFiles[i]);

		result = ma_decoder_init_file_wav(path, &decoderConfig, decoder_p);
		if (result != MA_SUCCESS){
			printf("Could not read file: %s\n", path);
		}
		
	}

	decodersLength = soundFilesLength;

	Array_init(&sounds, sizeof(Sound));

	volumes[AUDIO_SOUND_TYPE_SFX] = 1.0;
	volumes[AUDIO_SOUND_TYPE_MUSIC] = 1.0;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = SAMPLE_FORMAT;
    deviceConfig.playback.channels = CHANNEL_COUNT;
    deviceConfig.sampleRate        = SAMPLE_RATE;
    deviceConfig.dataCallback      = data_callback;
	deviceConfig.wasapi.noAutoConvertSRC = true;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
    }

}

void Audio_setVolume(float volume, enum Audio_SoundTypeEnum soundType){

	pthread_mutex_lock(&soundMutex);

	volumes[soundType] = volume;

	pthread_mutex_unlock(&soundMutex);

}

float Audio_getVolume(enum Audio_SoundTypeEnum soundType){

	pthread_mutex_lock(&soundMutex);

	return volumes[soundType];

	pthread_mutex_unlock(&soundMutex);

}

size_t Audio_playSound(char *soundName, float volume, bool loop, enum Audio_SoundTypeEnum soundType){

	pthread_mutex_lock(&soundMutex);

	Sound *sound_p = Array_addItem(&sounds);

	int decoderIndex = -1;
	for(int i = 0; i < decodersLength; i++){
		if(strcmp(decoderNames[i], soundName) == 0){
			decoderIndex = i;
			break;
		}
	}

	if(decoderIndex == -1){
		printf("No sound with name: %s\n", soundName);
	}

	sound_p->currentFrame = 0;
	sound_p->decoderIndex = decoderIndex;
	sound_p->volume = volume;
	sound_p->loop = loop;
	sound_p->type = soundType;
	sound_p->stopped = false;

	pthread_mutex_unlock(&soundMutex);

	return sound_p->entityHeader.ID;

}

void Audio_stopSoundByID(size_t ID){

	pthread_mutex_lock(&soundMutex);

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);

	sound_p->stopped = true;

	pthread_mutex_unlock(&soundMutex);

}

void Audio_resumeSoundByID(size_t ID){

	pthread_mutex_lock(&soundMutex);

	Sound *sound_p = Array_getItemPointerByID(&sounds, ID);

	sound_p->stopped = false;

	pthread_mutex_unlock(&soundMutex);

}

void Audio_killSoundByID(size_t ID){

	pthread_mutex_lock(&soundMutex);

	Array_removeItemByID(&sounds, ID);

	pthread_mutex_unlock(&soundMutex);

}
