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

#define SAMPLE_RATE 44100
#define NUMBER_OF_CHANNELS 2

//#define LOG_INFO_WAV_READER

void local_printf(const char *format, ...){

	va_list args;
    va_start(args, format);

#ifdef LOG_INFO_WAV_READER
	vprintf(format, args);
#endif

    va_end(args);

}

void lowPassFrequency(int16_t *, int16_t *, int, int, int, int);

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

	float resamplingFactor = (float)SAMPLE_RATE / (float)sampleRate;

	int resampledNumberOfPcmFrames = (float)numberOfPcmFrames * resamplingFactor;

	//int resampledNumberOfPcmFrames = (float)numberOfPcmFrames * (float)L / (float)M;

	int16_t *audioData = malloc(sizeof(int16_t) * resampledNumberOfPcmFrames * NUMBER_OF_CHANNELS);

	if(SAMPLE_RATE == sampleRate){

		memcpy(audioData, rawAudioData, sizeof(int16_t) * resampledNumberOfPcmFrames * NUMBER_OF_CHANNELS);

		resampledNumberOfPcmFrames = numberOfPcmFrames;

	}else{

		//resample data

		int L = 147;
		int M = 160;
		int cuttoffFrequency = 220500;

		int16_t conversionBuffer[L * NUMBER_OF_CHANNELS];
		int16_t filteredBuffer[L * NUMBER_OF_CHANNELS];

		int processedFrames = 0;
		int pickedFrames = 0;

		int processingCounter = 0;
		int pickingCounter = 0;

		double RC = 1.0 / ((double)cuttoffFrequency * 2 * 3.14);
		double dt = 1.0 / ((double)sampleRate * (double)L);

		double alpha = dt / (RC + dt);

		printf("RC: %f\n", RC);
		printf("dt: %f\n", dt);
		printf("alpha: %f\n", alpha);

		while(processedFrames < numberOfPcmFrames){

			memset(conversionBuffer, 0, L * NUMBER_OF_CHANNELS * sizeof(int16_t));

			conversionBuffer[0 + 0] = rawAudioData[processedFrames * NUMBER_OF_CHANNELS + 0];
			conversionBuffer[0 + 1] = rawAudioData[processedFrames * NUMBER_OF_CHANNELS + 1];

			filteredBuffer[0 + 0] = conversionBuffer[0 + 0];
			filteredBuffer[0 + 1] = conversionBuffer[0 + 1];

			//printf("%i\n", filteredBuffer[0]);

			for(int i = 1; i < L; i++){
				filteredBuffer[i * NUMBER_OF_CHANNELS + 0] = (int16_t)((double)filteredBuffer[(i - 1) * NUMBER_OF_CHANNELS + 0] + (alpha * ((double)conversionBuffer[i * NUMBER_OF_CHANNELS + 0] - (double)filteredBuffer[(i - 1) * NUMBER_OF_CHANNELS + 0])));
				filteredBuffer[i * NUMBER_OF_CHANNELS + 1] = (int16_t)((double)filteredBuffer[(i - 1) * NUMBER_OF_CHANNELS + 1] + (alpha * ((double)conversionBuffer[i * NUMBER_OF_CHANNELS + 1] - (double)filteredBuffer[(i - 1) * NUMBER_OF_CHANNELS + 1])));

				//if(i == L - 1){
					//printf("---\n");
					//printf("%i\n", filteredBuffer[i * NUMBER_OF_CHANNELS + 0]);
					//printf("%i\n", filteredBuffer[i * NUMBER_OF_CHANNELS + 1]);
				//}

			}

			processingCounter += L;

			while(processingCounter > pickingCounter){

				audioData[pickedFrames * NUMBER_OF_CHANNELS + 0] = filteredBuffer[(processingCounter - pickingCounter) * NUMBER_OF_CHANNELS + 0];
				audioData[pickedFrames * NUMBER_OF_CHANNELS + 1] = filteredBuffer[(processingCounter - pickingCounter) * NUMBER_OF_CHANNELS + 1];

				pickedFrames++;
				pickingCounter += M;
			
			}

			processedFrames++;
		
		}
	
	}

	local_printf("\nFINNISHED PROCESSING DATA\n");

	fclose(fileHandle);

	*numberOfPcmFrames_p = resampledNumberOfPcmFrames;

	free(rawAudioData);

	return audioData;

}

//Lånat från schysst snubbe
void lowPassFrequency(int16_t *input, int16_t *output, int points, int cuttoffFrequency, int sampleRate, int numberOfChannels){

    double RC = 1.0 / (cuttoffFrequency*2*3.14);
    double dt = 1.0 / sampleRate;

    double alpha = dt/(RC+dt);

    output[0] = input[0];

    for(int i = 1; i < points; i++){
		for(int j = 0; j < numberOfChannels; j++){
			output[i] = (int16_t)((double)output[(i - 1) * numberOfChannels + j] + (alpha * ((double)input[i * numberOfChannels + j] - (double)output[(i - 1) * numberOfChannels + j])));
		}
    }

}
