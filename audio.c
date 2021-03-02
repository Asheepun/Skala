#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "stdio.h"
#include "stdbool.h"

#define NUMBER_OF_DEVICES 20

typedef struct Sound{
	ma_decoder decoder;
	ma_device_config deviceConfig;
	char *name;
}Sound;

typedef struct DeviceHolder{
	ma_device device;
	bool playing;
	bool stopped;
}DeviceHolder;

Sound sounds[255];
int soundsLength;

DeviceHolder playDevices[NUMBER_OF_DEVICES];
DeviceHolder loopDevices[NUMBER_OF_DEVICES];

void dataCallbackPlay(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount){

	ma_decoder *pDecoder = (ma_decoder *)pDevice->pUserData;

	ma_result result = ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL, MA_FALSE);

	DeviceHolder *deviceHolder_p = (DeviceHolder *)pDevice;

	if(result == 0){

	}else{
		deviceHolder_p->stopped = true;
	}

}

void dataCallbackLoop(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount){

	ma_decoder *pDecoder = (ma_decoder *)pDevice->pUserData;

	ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL, MA_TRUE);

}

void initSounds(char **assets, int assetsLength){

	ma_result result;

	for(int i = 0; i < assetsLength; i++){

		Sound *sound_p = &sounds[i];

		sound_p->name = assets[i];

		char path[255];

		sprintf(path, "assets/audio/%s.wav", assets[i]);

		ma_decoder_init_file(path, NULL, &sound_p->decoder);

		sound_p->deviceConfig = ma_device_config_init(ma_device_type_playback);
		sound_p->deviceConfig.playback.format = sound_p->decoder.outputFormat;
		sound_p->deviceConfig.playback.channels = sound_p->decoder.outputChannels;
		sound_p->deviceConfig.sampleRate = sound_p->decoder.outputSampleRate;
		sound_p->deviceConfig.dataCallback = dataCallbackPlay;
		sound_p->deviceConfig.pUserData = &sound_p->decoder;

	}
	
	soundsLength = assetsLength;

}

void playSound(char *soundName){

	Sound *sound_p;

	for(int i = 0; i < soundsLength; i++){
		if(strcmp(soundName, sounds[i].name) == 0){
			sound_p = &sounds[i];
		}
	}

	DeviceHolder *deviceHolder_p;

	for(int i = 0; i < NUMBER_OF_DEVICES; i++){

		if(!playDevices[i].playing){
			deviceHolder_p = &playDevices[i];
		}

		//remove inactive devices
		if(playDevices[i].playing
		&& playDevices[i].stopped){

			ma_device_uninit(&playDevices[i].device);

			playDevices[i].playing = false;
			playDevices[i].stopped = false;

		}

	}

	deviceHolder_p->playing = true;
	deviceHolder_p->stopped = false;

	ma_device_init(NULL, &sound_p->deviceConfig, &deviceHolder_p->device);
	ma_device_start(&deviceHolder_p->device);

}
