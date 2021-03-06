#ifndef AUDIO_H_
#define AUDIO_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

typedef struct Sound{
	Mix_Chunk *chunk;
	char *name;
}Sound;

Sound sounds[255];
int soundsLength;

void initAudio(char **assets, int assetsLength){

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	for(int i = 0; i < assetsLength; i++){

		char path[255];
		sprintf(path, "assets/audio/%s.wav", assets[i]);

		sounds[i].chunk = Mix_LoadWAV(path);

		sounds[i].name = assets[i];
	
	}

	soundsLength = assetsLength;

}

void setVolume(float volume){
	Mix_Volume(-1, (int)(volume * (float)MIX_MAX_VOLUME));
}

void playSound(char *name){
	for(int i = 0; i < soundsLength; i++){
		if(strcmp(name, sounds[i].name) == 0){
			Mix_PlayChannel(-1, sounds[i].chunk, 0);
		}
	}
}

#endif
