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

	int normalLevelDistance = 70;
	int widerLevelDistance = 100;

	int houseX = 0;
	int houseWidth = 0;
	int firstFloorY = 0;
	int secondFloorY = -HEIGHT;

	int firstLevelsRoomX = 0;
	int firstLevelsRoomWidth = 0;

	int firstScalingLevelsRoomX = 0;
	int firstScalingLevelsRoomWidth = 0;

	int coolerScalingLevelsRoomX = 0;
	int coolerScalingLevelsRoomWidth = 0;

	int makeItBiggerLevelsRoomX = 0;
	int makeItBiggerLevelsRoomWidth = 0;

	int elevatorRoomX = 0;
	int elevatorRoomWidth = 0;

	int doorKeyLevelsRoomX = 0;
	int doorKeyLevelsRoomWidth = 0;

	int allFromTopLevelsRoomX = 0;
	int allFromTopLevelsRoomWidth = 0;

	int *currentRoomX;
	int *currentRoomWidth;
	int *currentFloorY;

	//add level doors

	//first room levels
	currentRoomX = &firstLevelsRoomX;
	currentRoomWidth = &firstLevelsRoomWidth;

	*currentRoomX = houseX;
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "level-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "level-2");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "level-3");
	*currentRoomWidth += normalLevelDistance;

	*currentRoomWidth += 20;

	houseWidth += *currentRoomWidth;

	//first scaling room levels
	currentRoomX = &firstScalingLevelsRoomX;
	currentRoomWidth = &firstScalingLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth;
	*currentRoomWidth += 40;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "first-scaling-level-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "first-scaling-level-3");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "first-scaling-level-4");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-1");
	*currentRoomWidth += normalLevelDistance;

	*currentRoomWidth += 40;

	houseWidth += *currentRoomWidth;

	//cooler scaling levels
	currentRoomX = &coolerScalingLevelsRoomX;
	currentRoomWidth = &coolerScalingLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth;
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-2");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-3");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-4");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-5");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "high-jump-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "high-jump-2");
	*currentRoomWidth += normalLevelDistance;

	houseWidth += *currentRoomWidth;

	//make it bigger room levels
	currentRoomX = &makeItBiggerLevelsRoomX;
	currentRoomWidth = &makeItBiggerLevelsRoomWidth;

	*currentRoomX = firstScalingLevelsRoomX + firstScalingLevelsRoomWidth;
	*currentRoomWidth += 40;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 35), "make-it-bigger-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 35), "make-it-bigger-2");
	*currentRoomWidth += widerLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 35), "point-cage");
	*currentRoomWidth += normalLevelDistance;

	//elevator room
	currentRoomX = &elevatorRoomX;
	currentRoomWidth = &elevatorRoomWidth;

	*currentRoomX = houseX + houseWidth;
	*currentRoomWidth += 60;

	houseWidth += *currentRoomWidth;

	//door key room levels
	currentRoomX = &doorKeyLevelsRoomX;
	currentRoomWidth = &doorKeyLevelsRoomWidth;

	*currentRoomX = elevatorRoomX + elevatorRoomWidth;
	*currentRoomWidth += 40;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "door-key-level-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "door-key-level-2");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "door-key-level-3");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "floor-is-door");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "get-key-up-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "get-key-up-2");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "push-key-with-point");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "maybe-key-should-fly");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "flying-key-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "flying-key-2-trickshot-edition");
	*currentRoomWidth += normalLevelDistance;

	//all from top room levels
	currentRoomX = &allFromTopLevelsRoomX;
	currentRoomWidth = &allFromTopLevelsRoomWidth;

	*currentRoomX = elevatorRoomX + elevatorRoomWidth;
	*currentRoomWidth += 60 + 200;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "all-from-top-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "all-from-top-2");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "all-from-top-3");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "get-under-cup");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "point-pikaboo");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "key-obstacle-course");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "key-in-cage-all-from-top");
	*currentRoomWidth += normalLevelDistance;

	*currentRoomWidth += 200;

	houseWidth += *currentRoomWidth;

	houseWidth += 60;

	//obstacles
	World_addObstacle(world_p, getVec2f(firstLevelsRoomX, HEIGHT - 60), getVec2f(firstLevelsRoomWidth, 60), NONE);

	World_addObstacle(world_p, getVec2f(firstLevelsRoomX, 0), getVec2f(firstLevelsRoomWidth, 100), NONE);

	World_addObstacle(world_p, getVec2f(firstLevelsRoomX, 100), getVec2f(firstLevelsRoomWidth - 80, 20), NONE);

	World_addObstacle(world_p, getVec2f(firstLevelsRoomX + firstLevelsRoomWidth - 20, HEIGHT - 80), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(firstScalingLevelsRoomX, HEIGHT - 100), getVec2f(firstScalingLevelsRoomWidth, 100), NONE);

	World_addObstacle(world_p, getVec2f(firstScalingLevelsRoomX, 0), getVec2f(firstScalingLevelsRoomWidth - 50, 100), NONE);

	World_addObstacle(world_p, getVec2f(firstScalingLevelsRoomX + firstScalingLevelsRoomWidth - 50, 0), getVec2f(50, 10), NONE);

	World_addObstacle(world_p, getVec2f(makeItBiggerLevelsRoomX, 80), getVec2f(makeItBiggerLevelsRoomWidth, 20), NONE);

	World_addObstacle(world_p, getVec2f(makeItBiggerLevelsRoomX, 0), getVec2f(makeItBiggerLevelsRoomWidth, 10), NONE);

	World_addObstacle(world_p, getVec2f(makeItBiggerLevelsRoomX + makeItBiggerLevelsRoomWidth, 0), getVec2f(coolerScalingLevelsRoomWidth - makeItBiggerLevelsRoomWidth, 100), NONE);

	World_addObstacle(world_p, getVec2f(coolerScalingLevelsRoomX, HEIGHT - 100), getVec2f(coolerScalingLevelsRoomWidth, 100), NONE);

	World_addObstacle(world_p, getVec2f(elevatorRoomX, HEIGHT - 5), getVec2f(elevatorRoomWidth, 5), NONE);

	World_addObstacle(world_p, getVec2f(elevatorRoomX, 0), getVec2f(elevatorRoomWidth, 30), NONE);

	World_addObstacle(world_p, getVec2f(elevatorRoomX, HEIGHT - 100), getVec2f(elevatorRoomWidth, 50), ALL);

	World_addObstacle(world_p, getVec2f(doorKeyLevelsRoomX, 100), getVec2f(doorKeyLevelsRoomWidth, 80), NONE);

	World_addObstacle(world_p, getVec2f(doorKeyLevelsRoomX, 0), getVec2f(doorKeyLevelsRoomWidth, 30), NONE);

	World_addObstacle(world_p, getVec2f(allFromTopLevelsRoomX, HEIGHT - 30), getVec2f(allFromTopLevelsRoomWidth, 30), NONE);

	World_addObstacle(world_p, getVec2f(doorKeyLevelsRoomX + doorKeyLevelsRoomWidth, 0), getVec2f(allFromTopLevelsRoomWidth - doorKeyLevelsRoomWidth - 80, 180), NONE);

	World_addObstacle(world_p, getVec2f(houseX + houseWidth - 60, 0), getVec2f(60, HEIGHT), NONE);

	//set level hub level size
	world_p->levelWidth = houseWidth;
	world_p->levelHeight = HEIGHT * 2;

	//World_addObstacle(world_p, getVec2f(doorKeyLevelPosX, 150), getVec2f(40, 40), ALL);

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
