#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

void World_initLevelHub(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(10, 100), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(10000, 60), NONE);

	//World_addObstacle(world_p, getVec2f(100, 160), getVec2f(WIDTH, 20), NONE);

	//World_addDoorKey(world_p, getVec2f(100, 100), ALL);

	int normalLevelDistance = 70;

	int firstLevelPosX = 70;
	int firstLevelPosY = 165;

	World_addLevelDoor(world_p, getVec2f(firstLevelPosX, firstLevelPosY), "level-1");
	firstLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstLevelPosX, firstLevelPosY), "level-2");
	firstLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstLevelPosX, firstLevelPosY), "level-3");
	firstLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstLevelPosX, firstLevelPosY), "level-4");
	firstLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstLevelPosX, firstLevelPosY), "level-5");
	firstLevelPosX += normalLevelDistance;

}
