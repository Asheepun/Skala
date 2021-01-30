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

	printf("started generating level hub!\n");

	World_restore(world_p);

	world_p->playerHasLanded = false;

	World_initPlayer(world_p, world_p->saveData.playerPos, NONE);

	int normalLevelDistance = 70;
	int widerLevelDistance = 100;

	//make starting area
	int startingAreaX = 0;

	//make house
	int houseX = 1400;
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

	int xySwitchLevelsRoomX = 0;
	int xySwitchLevelsRoomWidth = 0;

	int playerPositionLevelsRoomX = 0;
	int playerPositionLevelsRoomWidth = 0;

	int *currentRoomX;
	int *currentRoomWidth;
	int *currentFloorY;

	houseWidth += 30;

	//add level doors

	//first room levels
	currentRoomX = &firstLevelsRoomX;
	currentRoomWidth = &firstLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth;
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

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "slow-fall-squeeze");
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

	//x y switch room levels

	currentRoomX = &xySwitchLevelsRoomX;
	currentRoomWidth = &xySwitchLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth - 80;
	*currentRoomWidth += 70;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "scale-field-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "scale-field-2");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "scale-field-3");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "get-over-the-field");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "layers-of-fields");
	*currentRoomWidth += normalLevelDistance;

	*currentRoomX -= *currentRoomWidth;

	//player position room levels

	currentRoomX = &playerPositionLevelsRoomX;
	currentRoomWidth = &playerPositionLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth + 1000;
	*currentRoomWidth += 40;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-1");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-2");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-3");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "slide-slide-slide");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-pos-key");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "airport-control");
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "grow-through-jumping");
	*currentRoomWidth += normalLevelDistance;

	//World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, -HEIGHT + 125), "shrinking-death-dive");
	//*currentRoomWidth += normalLevelDistance;

	houseWidth += 60;

	//add starting area obstacles
	World_addObstacle(world_p, getVec2f(startingAreaX, 50 - HEIGHT), getVec2f(200, 120), NONE);

	World_addObstacle(world_p, getVec2f(startingAreaX, 170 - HEIGHT), getVec2f(250, 130), NONE);

	World_addObstacle(world_p, getVec2f(startingAreaX, 300 - HEIGHT), getVec2f(350, 110), NONE);

	World_addObstacle(world_p, getVec2f(startingAreaX, 230), getVec2f(houseX, 40), NONE);

	World_addObstacle(world_p, getVec2f(startingAreaX + 700, 210), getVec2f(200, 20), NONE);

	World_addObstacle(world_p, getVec2f(startingAreaX + 60, 140), getVec2f(40, 90), NONE);

	World_addObstacle(world_p, getVec2f(startingAreaX + 120, 140), getVec2f(40, 90), NONE);

	World_addObstacle(world_p, getVec2f(startingAreaX + 180, 140), getVec2f(40, 90), NONE);

	World_addObstacle(world_p, getVec2f(startingAreaX + 240, 140), getVec2f(40, 90), NONE);

	//add house obstacles
	World_addObstacle(world_p, getVec2f(houseX, 120), getVec2f(30, 50), NONE);

	World_addObstacle(world_p, getVec2f(houseX, 0), getVec2f(30, 120), NONE);

	World_addObstacle(world_p, getVec2f(houseX, HEIGHT - 60), getVec2f(30, 60), NONE);

	//World_addObstacle(world_p, getVec2f(houseX - 100, HEIGHT - 160), getVec2f(30, 60), ALL);

	World_addObstacle(world_p, getVec2f(houseX - 80, 50), getVec2f(80, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX - 70, 40), getVec2f(70, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX - 60, 30), getVec2f(60, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX - 50, 20), getVec2f(50, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX - 40, 10), getVec2f(40, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX - 30, 0), getVec2f(30, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX - 20, -10), getVec2f(20, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX - 10, -20), getVec2f(10, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX, -20), getVec2f(xySwitchLevelsRoomX - houseX, 20), NONE);

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

	World_addObstacle(world_p, getVec2f(houseX + houseWidth, 210), getVec2f(playerPositionLevelsRoomX + playerPositionLevelsRoomWidth - houseX - houseWidth, 60), NONE);

	//second floor
	World_addObstacle(world_p, getVec2f(xySwitchLevelsRoomX, -100), getVec2f(xySwitchLevelsRoomWidth, 100), NONE);

	World_addObstacle(world_p, getVec2f(xySwitchLevelsRoomX, -HEIGHT + 80), getVec2f(40, 90), NONE);

	World_addObstacle(world_p, getVec2f(houseX + houseWidth - 60, -HEIGHT + 80), getVec2f(60, 90), NONE);

	World_addObstacle(world_p, getVec2f(houseX + houseWidth - 60, -100), getVec2f(60, 100), NONE);

	int roofWidth = houseX + houseWidth - xySwitchLevelsRoomX + 60 * 2;
	for(int i = 0; i < roofWidth / 10; i++){
		World_addObstacle(world_p, getVec2f(xySwitchLevelsRoomX - 60 + i * 10, -HEIGHT + 70 - i * 10), getVec2f(roofWidth - i * 20, 10), NONE);
	}

	World_addObstacle(world_p, getVec2f(playerPositionLevelsRoomX, -100), getVec2f(playerPositionLevelsRoomWidth, 100), NONE);

	//walls

	int greenWallX = firstLevelsRoomX;
	int greenWallWidth = firstLevelsRoomWidth + firstScalingLevelsRoomWidth + coolerScalingLevelsRoomWidth;

	int elevatorWallX = elevatorRoomX;
	int elevatorWallWidth = elevatorRoomWidth;

	int yellowWallX = doorKeyLevelsRoomX;
	int yellowWallWidth = doorKeyLevelsRoomWidth;

	int purpleWallX = allFromTopLevelsRoomX;
	int purpleWallWidth = allFromTopLevelsRoomWidth;

	//World_addSprite(world_p, getVec2f(greenWallX, 0), getVec2f(greenWallWidth, HEIGHT), COLOR_GREEN_BACKGROUND, "obstacle", 1, GAME_LAYER_WALLS);

	//World_addSprite(world_p, getVec2f(elevatorWallX, 0), getVec2f(elevatorWallWidth, HEIGHT), COLOR_GREY_BACKGROUND, "obstacle", 1, GAME_LAYER_WALLS);

	//World_addSprite(world_p, getVec2f(purpleWallX, 0), getVec2f(purpleWallWidth, HEIGHT), COLOR_PURPLE_BACKGROUND, "obstacle", 1, GAME_LAYER_WALLS);

	//World_addSprite(world_p, getVec2f(yellowWallX, 0), getVec2f(yellowWallWidth, HEIGHT / 2), COLOR_YELLOW_BACKGROUND, "obstacle", 1, GAME_LAYER_WALLS);

	//set level hub level size
	world_p->levelWidth = houseWidth;
	world_p->levelHeight = HEIGHT * 2;

	//World_addObstacle(world_p, getVec2f(houseX + houseWidth - 120, 150), getVec2f(40, 40), ALL);

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

	printf("done generating level hub!\n");

}
