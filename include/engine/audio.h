#ifndef AUDIO_H_
#define AUDIO_H_

#include "stdbool.h"
#include "stdlib.h"
#include "stddef.h"

static int SAMPLE_RATE = 44100;
static int NUMBER_OF_CHANNELS = 2;
static int FRAME_SIZE = 4;
static int PERIOD_SIZE = 64;
//static int PERIOD_SIZE = 256;
//static int PERIOD_SIZE = 8 * 256;

static int pcmFramesPerFrame = 44100 / 60;

static float CONSTANT_VOLUME_FACTOR = 0.5;

enum Audio_SoundTypeEnum{
	AUDIO_SOUND_TYPE_SFX,
	AUDIO_SOUND_TYPE_MUSIC,
};

void Audio_init(char **, int);

void Audio_setVolume(float, enum Audio_SoundTypeEnum);

float Audio_getVolume(enum Audio_SoundTypeEnum);

size_t Audio_playSound(char *, float, bool, enum Audio_SoundTypeEnum);

void Audio_stopSoundByID(size_t);

void Audio_resumeSoundByID(size_t);

void Audio_killSoundByID(size_t);

float Audio_getSoundVolumeByID(size_t);

void Audio_setSoundVolumeByID(size_t, float);

void Audio_increaseSoundVolumeByID(size_t, float);

void Audio_decreaseSoundVolumeByID(size_t, float);

void Audio_setSoundTimeByID(size_t, int);

char *Audio_getSoundNameByID(size_t);

#endif
