#include "engine/engine.h"
#include "engine/audio.h"

#include "game.h"

#include "math.h"
#include "stdio.h"

size_t creditTextParticleIDs[16];
int creditTextParticlesLength = 0;

int counter = 0;

void World_initCredits(World *world_p){

	World_restore(world_p);

	world_p->renderer.offset.x = 0;
	world_p->renderer.offset.y = 0;

	creditTextParticlesLength = 0;

	World_addSprite(world_p, getVec2f(0, 0), getVec2f(WIDTH, HEIGHT), COLOR_BLACK, "obstacle", 1, GAME_LAYER_BACKGROUND);

	int activationTime = 1 * 60;
	int fadeInTime = 0.5 * 60;

	creditTextParticleIDs[creditTextParticlesLength] = World_addFadeInTextParticle(world_p, getVec2f(80, 100), "Thank you for playing Skala", "times30", COLOR_WHITE, activationTime, fadeInTime);
	creditTextParticlesLength++;
	creditTextParticleIDs[creditTextParticlesLength] = World_addFadeInTextParticle(world_p, getVec2f(130, 150), "A game by Gustav Almstrom", "times20", COLOR_WHITE, activationTime, fadeInTime);
	creditTextParticlesLength++;

	world_p->saveData.playerPos = getVec2f(330, -240);

	if(!Audio_soundIsPlaying(world_p->creditsMusicID)){
		world_p->creditsMusicID = Audio_playSound("music/credits", 1.0, false, AUDIO_SOUND_TYPE_MUSIC, 0);
	}

	counter = 0;

}

void World_creditsState(World *world_p){

	if(world_p->fadeTransitionCounter > 0){
		return;
	}

	if(counter > 60 * 2
	&& world_p->actions[DO_ACTION].downed){
		World_fadeTransitionToState(world_p, LEVEL_HUB_STATE);

		return;
	}

	if(counter == 60 * 20){
		for(int i = 0; i < creditTextParticlesLength; i++){
			union ParticleProperty property;
			property.alpha = 0;
			Particle_addEvent(World_getParticleByID(world_p, creditTextParticleIDs[i]), PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, property, 0, 0.3 * 60);
		}

		int activationTime = 0.5 * 60;
		int fadeInTime = 0.5 * 60;

		creditTextParticleIDs[creditTextParticlesLength] = World_addFadeInTextParticle(world_p, getVec2f(157, 50), "Special Thanks", "times30", COLOR_WHITE, activationTime, fadeInTime);
		creditTextParticlesLength++;

		creditTextParticleIDs[creditTextParticlesLength] = World_addFadeInTextParticle(world_p, getVec2f(195, 100), "Lukas Nord", "times20", COLOR_WHITE, activationTime, fadeInTime);
		creditTextParticlesLength++;

		creditTextParticleIDs[creditTextParticlesLength] = World_addFadeInTextParticle(world_p, getVec2f(205, 130), "Olle Hall", "times20", COLOR_WHITE, activationTime, fadeInTime);
		creditTextParticlesLength++;

		creditTextParticleIDs[creditTextParticlesLength] = World_addFadeInTextParticle(world_p, getVec2f(185, 160), "Klara Almstrom", "times20", COLOR_WHITE, activationTime, fadeInTime);
		creditTextParticlesLength++;

	}

	if(counter > 60 * 40){
		World_fadeTransitionToState(world_p, LEVEL_HUB_STATE);

		return;
	}

	//fade out previous music
	for(int i = 0; i < world_p->musicIDs.length; i++){

		size_t ID = *(size_t *)Array_getItemPointerByIndex(&world_p->musicIDs, i);

		Audio_decreaseSoundVolumeByID(ID, MUSIC_FADE_OUT_SPEED);

	}

	counter++;

}
