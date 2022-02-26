#ifndef WAV_READER_H_
#define WAV_READER_H_

#ifdef __linux__
#include "stddef.h"
#endif

#ifdef _WIN32
#include "stdint.h"
#endif

//get data and number of pcm frames
int16_t *WavReader_getDataFromWavFile(char *, int *);

#endif
