#include "engine/engine.h"

#include "game.h"

#include "math.h"
#include "stdio.h"

void World_initCredits(World *world_p){

	World_restore(world_p);

	world_p->renderer.offset.x = 0;
	world_p->renderer.offset.y = 0;

	World_addSprite(world_p, getVec2f(0, 0), getVec2f(WIDTH, HEIGHT), COLOR_BLACK, "obstacle", 1, GAME_LAYER_BACKGROUND);

	World_addTextSprite(world_p, getVec2f(80, 100), "Thank you for playing Skala", "times30", COLOR_WHITE, GAME_LAYER_TEXT);

	World_addTextSprite(world_p, getVec2f(120, 150), "A game by Gustav Almstrom", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

	world_p->saveData.playerPos = getVec2f(330, -240);

}

int counter = 0;

void World_creditsState(World *world_p){

	if(world_p->fadeTransitionCounter > 0){
		return;
	}

	if(counter > 60 * 5
	|| counter > 60 * 2
	&& world_p->actions[DO_ACTION].down){
		World_fadeTransitionToState(world_p, LEVEL_HUB_STATE);
	}

	counter++;

}
