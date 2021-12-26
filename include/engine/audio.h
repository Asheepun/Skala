#ifndef AUDIO_H_
#define AUDIO_H_

#include "stdbool.h"
#include "stdlib.h"
#include "stddef.h"

#define SAMPLE_FORMAT ma_format_f32
#define CHANNEL_COUNT 1
#define SAMPLE_RATE 48000

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
