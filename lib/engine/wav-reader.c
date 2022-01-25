#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "stdarg.h"
#include "stddef.h"

#define FILE_SIZE_INDEX 4
#define FORMAT_TYPE_INDEX 20
#define NUMBER_OF_CHANNELS_INDEX 22
#define SAMPLE_RATE_INDEX 24
#define BITS_PER_SAMPLE_INDEX 34
#define DATA_SIZE_INDEX 40

#define DESIRED_SAMPLE_RATE 44100
#define DESIRED_NUMBER_OF_CHANNELS 2

//#define LOG_INFO_WAV_READER

void local_printf(const char *format, ...){

	va_list args;
    va_start(args, format);

#ifdef LOG_INFO_WAV_READER
	vprintf(format, args);
#endif

    va_end(args);

}

int16_t *WavReader_getDataFromWavFile(char *path, int *numberOfPcmFrames_p){

	FILE *fileHandle = NULL;
	
	fileHandle = fopen(path, "r");

	if(fileHandle == NULL){

		printf("COULD NOT READ FILE: %s\n", path);
		
		return NULL;
	}

	local_printf("\nfile path: %s\n\n", path);

	//read header data
	int8_t fileHeader[44];
	memset(fileHeader, 0, 44);

	fread(fileHeader, 1, 44, fileHandle);

	local_printf("RAW HEADER\n");
	for(int i = 0; i < 44; i++){
		local_printf("%c", fileHeader[i]);
	}
	local_printf("\n\n");

	int32_t sampleRate;
	int16_t numberOfChannels;
	int32_t dataSize;
	int16_t bitsPerSample;

	memcpy(&numberOfChannels, fileHeader + NUMBER_OF_CHANNELS_INDEX, 2);
	memcpy(&sampleRate, fileHeader + SAMPLE_RATE_INDEX, 4);
	memcpy(&dataSize, fileHeader + DATA_SIZE_INDEX, 4);
	memcpy(&bitsPerSample, fileHeader + BITS_PER_SAMPLE_INDEX, 2);

	local_printf("numberOfChannels: %i\n", numberOfChannels);
	local_printf("sampleRate: %i\n", sampleRate);
	local_printf("dataSize: %i\n", dataSize);
	local_printf("bitsPerSample: %i\n", bitsPerSample);

	int numberOfPcmFrames = dataSize / numberOfChannels / (bitsPerSample / 8);

	int time = numberOfPcmFrames / sampleRate;

	local_printf("\nnumberOfPcmFrames: %i\n", numberOfPcmFrames);
	local_printf("time: %i seconds\n", time);

	//read audio data

	local_printf("\nBEGAN PROCESSING DATA\n");

	int16_t *rawAudioData = malloc(sizeof(int16_t) * numberOfPcmFrames * numberOfChannels);

	memset(rawAudioData, 0, sizeof(int16_t) * numberOfPcmFrames * numberOfChannels);

	fseek(fileHandle, 44, SEEK_SET);

	fread(rawAudioData, 1, dataSize, fileHandle);

	//float resamplingFactor = (float)DESIRED_SAMPLE_RATE / (float)sampleRate;

	//int resampledNumberOfPcmFrames = (float)numberOfPcmFrames * resamplingFactor;

	//resample data
	float resamplingFactor = (float)DESIRED_SAMPLE_RATE / (float)sampleRate;

	int resampledNumberOfPcmFrames = (int)((float)numberOfPcmFrames * resamplingFactor);

	//printf("%f\n", resamplingFactor);

	int16_t *audioData = malloc(resampledNumberOfPcmFrames * sizeof(int16_t) * DESIRED_NUMBER_OF_CHANNELS);
	memset(audioData, 0, resampledNumberOfPcmFrames * sizeof(int16_t) * DESIRED_NUMBER_OF_CHANNELS);

	for(int i = 0; i < resampledNumberOfPcmFrames; i++){

		for(int j = 0; j < DESIRED_NUMBER_OF_CHANNELS; j++){
			audioData[i * DESIRED_NUMBER_OF_CHANNELS + j] = rawAudioData[(int)((float)i * (float)numberOfChannels * (1 / resamplingFactor))];
		}
	
	}

	/*
	float *audioDataF32 = malloc(sizeof(float) * resampledNumberOfPcmFrames * DESIRED_NUMBER_OF_CHANNELS);

	memset(audioDataF32, 0, sizeof(float) * resampledNumberOfPcmFrames * DESIRED_NUMBER_OF_CHANNELS);

	local_printf("\nresamplingFactor: %f\n", resamplingFactor);

	local_printf("resampledNumberOfPcmFrames: %i\n", resampledNumberOfPcmFrames);

	for(int i = 0; i < numberOfPcmFrames; i++){

		int index = floor((float)i * resamplingFactor);

		audioDataF32[indexF32] = ((float)audioData[i * numberOfChannels]) / (float)pow(2, bitsPerSample - 1);

	}

	for(int i = 0; i < resampledNumberOfPcmFrames; i++){
		if(audioData[i] == 0
		&& audioData[i - 1] != 0
		&& audioData[i + 1] != 0){
			audioData[i] = (audioData[(i - 1)] + audioData[(i + 1)]) / 2;
		}
	}
	*/

	local_printf("\nFINNISHED PROCESSING DATA\n");

	//free(audioData);

	fclose(fileHandle);

	*numberOfPcmFrames_p = resampledNumberOfPcmFrames;

	free(rawAudioData);

	return audioData;

	//return audioDataF32;

}
