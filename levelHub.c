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

	world_p->playerHasLanded = false;

	World_initPlayer(world_p, world_p->saveData.playerPos, NONE);

	//add level doors
	int normalLevelDistance = 70;
	int widerLevelDistance = 100;

	int firstLevelPosX = 70;
	int firstLevelPosY = 165;

	World_addLevelDoor(world_p, getVec2f(firstLevelPosX, firstLevelPosY), "level-1");
	firstLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstLevelPosX, firstLevelPosY), "level-2");
	firstLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstLevelPosX, firstLevelPosY), "level-3");
	firstLevelPosX += normalLevelDistance;

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(firstLevelPosX - 10, 60), NONE);

	int firstScalingLevelPosX = firstLevelPosX + 50;
	int firstScalingLevelPosY = firstLevelPosY - 40;

	World_addLevelDoor(world_p, getVec2f(firstScalingLevelPosX, firstScalingLevelPosY), "first-scaling-level-1");
	firstScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstScalingLevelPosX, firstScalingLevelPosY), "first-scaling-level-2");
	firstScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstScalingLevelPosX, firstScalingLevelPosY), "first-scaling-level-3");
	firstScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstScalingLevelPosX, firstScalingLevelPosY), "first-scaling-level-4");
	firstScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(firstScalingLevelPosX, firstScalingLevelPosY), "cooler-scaling-level-1");
	firstScalingLevelPosX += normalLevelDistance;

	int makeItBiggerLevelPosX = firstScalingLevelPosX + 50;
	int makeItBiggerLevelPosY = firstScalingLevelPosY - 80;
	int makeItBiggerLevelWidth = 0;

	World_addLevelDoor(world_p, getVec2f(makeItBiggerLevelPosX, makeItBiggerLevelPosY), "make-it-bigger-1");
	makeItBiggerLevelPosX += normalLevelDistance;
	makeItBiggerLevelWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(makeItBiggerLevelPosX, makeItBiggerLevelPosY), "make-it-bigger-2");
	makeItBiggerLevelPosX += widerLevelDistance;
	makeItBiggerLevelWidth += widerLevelDistance;

	World_addLevelDoor(world_p, getVec2f(makeItBiggerLevelPosX, makeItBiggerLevelPosY), "point-cage");
	makeItBiggerLevelPosX += widerLevelDistance;
	makeItBiggerLevelWidth += widerLevelDistance;

	int coolerScalingLevelPosX = firstScalingLevelPosX + normalLevelDistance;
	int coolerScalingLevelPosY = firstScalingLevelPosY;

	World_addLevelDoor(world_p, getVec2f(coolerScalingLevelPosX, coolerScalingLevelPosY), "cooler-scaling-level-2");
	coolerScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(coolerScalingLevelPosX, coolerScalingLevelPosY), "cooler-scaling-level-3");
	coolerScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(coolerScalingLevelPosX, coolerScalingLevelPosY), "cooler-scaling-level-4");
	coolerScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(coolerScalingLevelPosX, coolerScalingLevelPosY), "cooler-scaling-level-5");
	coolerScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(coolerScalingLevelPosX, coolerScalingLevelPosY), "high-jump-1");
	coolerScalingLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(coolerScalingLevelPosX, coolerScalingLevelPosY), "high-jump-2");
	coolerScalingLevelPosX += normalLevelDistance;

	int doorKeyLevelPosX = coolerScalingLevelPosX + 10 + 60 + 40;
	int doorKeyLevelPosY = coolerScalingLevelPosY - 70;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "door-key-level-1");
	doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "door-key-level-2");
	doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "door-key-level-3");
	doorKeyLevelPosX += normalLevelDistance;

	//World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "door-key-level-4");
	//doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "floor-is-door");
	doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "get-key-up-1");
	doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "get-key-up-2");
	doorKeyLevelPosX += normalLevelDistance;

	//World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "door-key-level-with-key");
	//doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "push-key-with-point");
	doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "maybe-key-should-fly");
	doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "flying-key-1");
	doorKeyLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(doorKeyLevelPosX, doorKeyLevelPosY), "flying-key-2-trickshot-edition");
	doorKeyLevelPosX += normalLevelDistance;

	int allFromTopLevelPosX = coolerScalingLevelPosX + 330;
	int allFromTopLevelPosY = 195;

	World_addLevelDoor(world_p, getVec2f(allFromTopLevelPosX, allFromTopLevelPosY), "all-from-top-1");
	allFromTopLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(allFromTopLevelPosX, allFromTopLevelPosY), "all-from-top-2");
	allFromTopLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(allFromTopLevelPosX, allFromTopLevelPosY), "all-from-top-3");
	allFromTopLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(allFromTopLevelPosX, allFromTopLevelPosY), "point-pikaboo");
	allFromTopLevelPosX += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(allFromTopLevelPosX, allFromTopLevelPosY), "get-under-cup");
	allFromTopLevelPosX += normalLevelDistance;


	//add obstacles

	World_addObstacle(world_p, getVec2f(firstLevelPosX + 10, 170), getVec2f(coolerScalingLevelPosX - firstLevelPosX, 100), NONE);

	World_addObstacle(world_p, getVec2f(firstLevelPosX - 10, 190), getVec2f(20, 80), NONE);

	World_addObstacle(world_p, getVec2f(coolerScalingLevelPosX + 10, 170), getVec2f(60, 50), ALL);

	World_addObstacle(world_p, getVec2f(coolerScalingLevelPosX + 10, 265), getVec2f(60, 5), NONE);

	World_addObstacle(world_p, getVec2f(coolerScalingLevelPosX + 10 + 60, 240), getVec2f(1000, 30), NONE);

	//World_addDoor(world_p, getVec2f(coolerScalingLevelPosX + 10 + 60 + 160, 180), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(coolerScalingLevelPosX + 10 + 60, 100), getVec2f(1000, 80), NONE);

	World_addObstacle(world_p, getVec2f(coolerScalingLevelPosX + 10, 0), getVec2f(1000, 30), NONE);

	World_addObstacle(world_p, getVec2f(firstScalingLevelPosX + 30, makeItBiggerLevelPosY + 40), getVec2f(coolerScalingLevelPosX - firstScalingLevelPosX - 20, 20), NONE);

	World_addObstacle(world_p, getVec2f(makeItBiggerLevelPosX, makeItBiggerLevelPosY - 50), getVec2f(coolerScalingLevelPosX - makeItBiggerLevelPosX + 10, 90), NONE);

	//mark completed levels and doors with keys
	for(int i = 0; i < world_p->levelDoors.length; i++){

		LevelDoor *levelDoor_p = Array_getItemPointerByIndex(&world_p->levelDoors, i);

		for(int j = 0; j < world_p->saveData.completedLevels.length; j++){
			char *completedLevelName = *((char **)Array_getItemPointerByIndex(&world_p->saveData.completedLevels, j));

			if(strcmp(levelDoor_p->levelName, completedLevelName) == 0){

				Sprite *sprite_p = World_getSpriteByID(world_p, levelDoor_p->spriteID);

				sprite_p->texture = "level-door-completed";

			}
		}

		for(int j = 0; j < world_p->saveData.levelsWithDoorKey.length; j++){
			char *levelWithDoorKeyName = *((char **)Array_getItemPointerByIndex(&world_p->saveData.levelsWithDoorKey, j));

			if(strcmp(levelDoor_p->levelName, levelWithDoorKeyName) == 0){

				Sprite *sprite_p = World_getSpriteByID(world_p, levelDoor_p->spriteID);

				sprite_p->texture = "level-door-with-key";

			}
		}

	}

	//add saved door keys
	for(int i = 0; i < world_p->saveData.doorKeys.length; i++){

		Vec2f *doorKeyPos_p = Array_getItemPointerByIndex(&world_p->saveData.doorKeys, i);

		World_addDoorKey(world_p, *doorKeyPos_p, NONE);

	}

	//add saved doors
	for(int i = 0; i < world_p->saveData.doors.length; i++){

		Body *doorBody_p = Array_getItemPointerByIndex(&world_p->saveData.doors, i);

		World_addDoor(world_p, doorBody_p->pos, doorBody_p->size, NONE);

	}

	SaveData_write(&world_p->saveData);

}
