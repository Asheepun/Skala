//#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
//#include "geometry.h"
//#include "stb_truetype.h"
//#include "text.h"
//#include "utils.h"
#include "game.h"
#include "levels.h"

void World_initLevelHub(World *world_p){

	World_restore(world_p);

	//World_addObstacle(world_p, getVec2f(3500, -250), getVec2f(50, 50), ALL);

	world_p->starBackgroundSpriteIndex = World_addSprite(world_p, getVec2f(0, 0), getVec2f(5000, HEIGHT * 8), COLOR_WHITE, "star-background", 1, GAME_LAYER_BACKGROUND);

	world_p->playerHasLanded = false;

	World_initPlayer(world_p, world_p->saveData.playerPos, NONE);
	world_p->snapCamera = true;

	//BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, world_p->player.bodyPairID);
	//world_p->cameraPos.x = WIDTH / 2 - playerBodyPair_p->body.pos.x;
	//world_p->cameraPos.y = HEIGHT / 2 - playerBodyPair_p->body.pos.y;

	int normalLevelDistance = 70;
	int widerLevelDistance = 100;

	int cloudY = -HEIGHT * 6;

	//make starting area
	int startingAreaX = 300;

	//make house
	int houseX = startingAreaX + 1400;
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
	*currentRoomWidth += 30;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 160), getVec2f(33, 11), COLOR_WHITE, "furniture/hat-shelf", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 30, 210 - 31), getVec2f(15, 31), COLOR_WHITE, "furniture/coat-hanger", 1, GAME_LAYER_FURNITURE);

	*currentRoomWidth += 90;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth - 40, 120), getVec2f(11, 11), COLOR_WHITE, "furniture/lamp-1", 1, GAME_LAYER_FURNITURE);

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "level-1", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "level-2", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "level-3", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	*currentRoomWidth += 20;

	houseWidth += *currentRoomWidth;

	//first scaling room levels
	currentRoomX = &firstScalingLevelsRoomX;
	currentRoomWidth = &firstScalingLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth;
	*currentRoomWidth += 40;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "first-scaling-level-1", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "first-scaling-level-3", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "first-scaling-level-4", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-1", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	*currentRoomWidth -= 0;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 170 - 43), getVec2f(11, 43), COLOR_WHITE, "furniture/living-room-lamp", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 25, 170 - 18), getVec2f(43, 18), COLOR_WHITE, "furniture/sofa", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 25 + 60, 170 - 44), getVec2f(28, 44), COLOR_WHITE, "furniture/book-shelf", 1, GAME_LAYER_FURNITURE);

	*currentRoomWidth += 50 + 20;

	houseWidth += *currentRoomWidth;

	//cooler scaling levels
	currentRoomX = &coolerScalingLevelsRoomX;
	currentRoomWidth = &coolerScalingLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth;
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-2", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-3", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-4", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "cooler-scaling-level-5", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "high-jump-1", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "slow-fall-squeeze", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "high-jump-2", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 125), "high-jump-3", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	houseWidth += *currentRoomWidth;

	//make it bigger room levels
	currentRoomX = &makeItBiggerLevelsRoomX;
	currentRoomWidth = &makeItBiggerLevelsRoomWidth;

	*currentRoomX = firstScalingLevelsRoomX + firstScalingLevelsRoomWidth;
	*currentRoomWidth += 40;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 35), "make-it-bigger-1", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 35), "make-it-bigger-2", FIRST_SCALE_ROOM);
	//*currentRoomWidth += widerLevelDistance;
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 35), "point-cage", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 35), "point-cage-2", FIRST_SCALE_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 35), "point-cage-3", FIRST_SCALE_ROOM);
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

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "door-key-level-1", DOOR_KEY_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "door-key-level-2", DOOR_KEY_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "floor-is-door", DOOR_KEY_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "get-key-up-1", DOOR_KEY_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "get-key-up-2", DOOR_KEY_ROOM);
	//*currentRoomWidth += normalLevelDistance;

	//World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "throw-key", DOOR_KEY_ROOM);
	//*currentRoomWidth += normalLevelDistance * 2 + 20;

	*currentRoomWidth += 70;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 100 - 24), getVec2f(26, 24), COLOR_WHITE, "furniture/stove", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 10, 60 - 16), getVec2f(33, 16), COLOR_WHITE, "furniture/kitchen-shelf", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 60, 100 - 32), getVec2f(51, 32), COLOR_WHITE, "furniture/kitchen-table", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 70, 30), getVec2f(9, 13), COLOR_WHITE, "furniture/lamp-2", 1, GAME_LAYER_FURNITURE);

	*currentRoomWidth += 150;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "push-key-with-point", DOOR_KEY_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "key-in-box", DOOR_KEY_ROOM);
	//*currentRoomWidth += normalLevelDistance;

	*currentRoomWidth += 70;

	World_addObstacle(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 30), getVec2f(20, 30), NONE);

	*currentRoomWidth += 70;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "maybe-key-should-fly", DOOR_KEY_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "flying-key-1", DOOR_KEY_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 55), "flying-key-2-trickshot-edition", DOOR_KEY_ROOM);

	*currentRoomWidth += 50;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 10, 100 - 19), getVec2f(13, 19), COLOR_WHITE, "furniture/bedside-table", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 42, 100 - 17), getVec2f(53, 17), COLOR_WHITE, "furniture/bed", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 50, 30), getVec2f(9, 15), COLOR_WHITE, "furniture/lamp-3", 1, GAME_LAYER_FURNITURE);

	*currentRoomWidth += 100;

	//all from top room levels
	currentRoomX = &allFromTopLevelsRoomX;
	currentRoomWidth = &allFromTopLevelsRoomWidth;

	*currentRoomX = elevatorRoomX + elevatorRoomWidth;
	*currentRoomWidth += 60 + 200 + 10;

	//World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth - 120, 180), getVec2f(11, 11), COLOR_WHITE, "furniture/lamp-1", 1, GAME_LAYER_FURNITURE);

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "all-from-top-1", ALL_FROM_TOP_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "all-from-top-2", ALL_FROM_TOP_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "all-from-top-3", ALL_FROM_TOP_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "get-under-cup", ALL_FROM_TOP_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "point-pikaboo", ALL_FROM_TOP_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "key-obstacle-course", ALL_FROM_TOP_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 195), "key-in-cage-all-from-top", ALL_FROM_TOP_ROOM);
	//*currentRoomWidth += normalLevelDistance;
	
	*currentRoomWidth += 60;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 240 - 13), getVec2f(13, 13), COLOR_WHITE, "furniture/wash-basket", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 25, 240 - 30), getVec2f(21, 30), COLOR_WHITE, "furniture/washing-machine", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 50, 180), getVec2f(11, 11), COLOR_WHITE, "furniture/lamp-1", 1, GAME_LAYER_FURNITURE);

	//World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth + 430, 180), getVec2f(11, 11), COLOR_WHITE, "furniture/lamp-1", 1, GAME_LAYER_FURNITURE);


	*currentRoomWidth += 550;

	houseWidth += *currentRoomWidth;

	//x y switch room levels

	currentRoomX = &xySwitchLevelsRoomX;
	currentRoomWidth = &xySwitchLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth - 80;
	*currentRoomWidth += 70;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "scale-field-1", SCALE_FIELD_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "scale-field-2", SCALE_FIELD_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "scale-field-3", SCALE_FIELD_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "get-over-the-field", SCALE_FIELD_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "layers-of-fields", SCALE_FIELD_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX - *currentRoomWidth, -HEIGHT + 125), "point-field-cage", SCALE_FIELD_ROOM);
	*currentRoomWidth += normalLevelDistance;

	*currentRoomWidth += 20;

	*currentRoomX -= *currentRoomWidth;

	//player position room levels

	currentRoomX = &playerPositionLevelsRoomX;
	currentRoomWidth = &playerPositionLevelsRoomWidth;

	*currentRoomX = houseX + houseWidth + 1000;
	*currentRoomWidth += 40;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth, HEIGHT - 60 - 73), getVec2f(14, 73), COLOR_WHITE, "furniture/lamp-post", 1, GAME_LAYER_FURNITURE);
	*currentRoomWidth += 50;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-1", PLAYER_POSITION_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-2", PLAYER_POSITION_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-3", PLAYER_POSITION_ROOM);
	*currentRoomWidth += normalLevelDistance;

	//World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "slide-slide-slide", PLAYER_POSITION_ROOM);
	//*currentRoomWidth += normalLevelDistance;

	//World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-pos-key", PLAYER_POSITION_ROOM);
	//*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "airport-control", PLAYER_POSITION_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "grow-through-jumping", PLAYER_POSITION_ROOM);
	//*currentRoomWidth += normalLevelDistance;
	*currentRoomWidth += 50;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth, HEIGHT - 60 - 16), getVec2f(36, 16), COLOR_WHITE, "furniture/bench", 1, GAME_LAYER_FURNITURE);
	*currentRoomWidth += 50;

	World_addSprite(world_p, getVec2f(*currentRoomX + *currentRoomWidth, HEIGHT - 60 - 73), getVec2f(14, 73), COLOR_WHITE, "furniture/lamp-post", 1, GAME_LAYER_FURNITURE);
	*currentRoomWidth += 40;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-jumping-key-1", PLAYER_POSITION_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-jumping-key-2", PLAYER_POSITION_ROOM);
	*currentRoomWidth += normalLevelDistance;

	World_addLevelDoor(world_p, getVec2f(*currentRoomX + *currentRoomWidth, 165), "player-position-jumping-key-3", PLAYER_POSITION_ROOM);
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

	//World_addObstacle(world_p, getVec2f(startingAreaX + 200, -HEIGHT - 50), getVec2f(40, 40), ALL);

	World_addObstacle(world_p, getVec2f(startingAreaX, - HEIGHT - 300), getVec2f(200, 50), NONE);

	World_addSprite(world_p, getVec2f(startingAreaX + 125, -HEIGHT - 300 - 16), getVec2f(36, 16), COLOR_WHITE, "furniture/bench", 1, GAME_LAYER_FURNITURE);

	World_addSprite(world_p, getVec2f(startingAreaX + 170, -HEIGHT - 300 - 73), getVec2f(14, 73), COLOR_WHITE, "furniture/lamp-post", 1, GAME_LAYER_FURNITURE);

	World_addTextSprite(world_p, getVec2f(startingAreaX + 20, -HEIGHT - 460), "Wings made from wax", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

	World_addTextSprite(world_p, getVec2f(startingAreaX + 20, -HEIGHT - 435), "and curiousity", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

	World_addTextSprite(world_p, getVec2f(startingAreaX + 20, -HEIGHT - 400), "May you not suffer", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

	World_addTextSprite(world_p, getVec2f(startingAreaX + 20, -HEIGHT - 375), "from hubris", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

	if(!SaveData_hasFlag(&world_p->saveData, "removed-title-text")){

		int activationTime = 4000 / 60;
		int secondActivationTime = 4000 / 60;
		int duration = 5000 / 60;

		world_p->titleTextParticleID = World_addFadeInTextParticle(world_p, getVec2f(startingAreaX + 250, -HEIGHT - 50), "Skala ", "times80", COLOR_WHITE, activationTime, duration);

		world_p->movementKeysTextParticleID = World_addFadeInTextParticle(world_p, getVec2f(startingAreaX + 260, -HEIGHT + 30), "Arrow keys to move ", "times20", COLOR_WHITE, activationTime + secondActivationTime, duration);

		world_p->menuKeyTextParticleID = World_addFadeInTextParticle(world_p, getVec2f(startingAreaX + 260, -HEIGHT + 50), "Esc key to open menu ", "times20", COLOR_WHITE, activationTime + secondActivationTime, duration);
	
	}

	//elevator to ending
	
	World_addObstacle(world_p, getVec2f(0, cloudY - HEIGHT), getVec2f(100, -cloudY + 2 * HEIGHT - 40), NONE);

	World_addObstacle(world_p, getVec2f(200, cloudY), getVec2f(100, -cloudY + HEIGHT - 130), NONE);

	World_addObstacle(world_p, getVec2f(100, cloudY - HEIGHT), getVec2f(200, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(200, cloudY), getVec2f(100, -cloudY + HEIGHT - 130), NONE);

	World_addScaleField(world_p, getVec2f(200, cloudY - 60), getVec2f(80, 60), NONE);

	//World_addObstacle(world_p, getVec2f(200, cloudY), getVec2f(100, -cloudY + HEIGHT - 130), NONE);

	//ending

	World_addObstacle(world_p, getVec2f(340, cloudY - 20), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(420, cloudY - 20), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(460, cloudY - 40), getVec2f(20, 10), NONE);

	World_addObstacle(world_p, getVec2f(540, cloudY - 30), getVec2f(60, 10), NONE);

	World_addObstacle(world_p, getVec2f(740, cloudY - 30), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(940, cloudY - 50), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(1160, cloudY - 20), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(1360, cloudY - 20), getVec2f(300, 20), NONE);

	World_addScaleField(world_p, getVec2f(1360 + 130, cloudY - 50), getVec2f(40, 30), ALL);

	World_addTextSprite(world_p, getVec2f(1360 + 105, cloudY - 150), "Ascend", "times30", COLOR_WHITE, GAME_LAYER_TEXT);

	//add obstacles house 
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
	World_addObstacle(world_p, getVec2f(houseX - 20, -10), getVec2f(xySwitchLevelsRoomX - houseX + 20, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX - 10, -20), getVec2f(xySwitchLevelsRoomX - houseX + 10, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX, -30), getVec2f(xySwitchLevelsRoomX - houseX, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX + 10, -40), getVec2f(xySwitchLevelsRoomX - houseX - 10, 10), NONE);
	World_addObstacle(world_p, getVec2f(houseX + 20, -50), getVec2f(xySwitchLevelsRoomX - houseX - 20, 10), NONE);
	//World_addObstacle(world_p, getVec2f(houseX + 30, -60), getVec2f(xySwitchLevelsRoomX - houseX - 30, 10), NONE);

	//World_addObstacle(world_p, getVec2f(houseX, -20), getVec2f(xySwitchLevelsRoomX - houseX, 20), NONE);

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

	World_addObstacle(world_p, getVec2f(doorKeyLevelsRoomX, 100), getVec2f(doorKeyLevelsRoomWidth, 70), NONE);

	World_addObstacle(world_p, getVec2f(doorKeyLevelsRoomX, 0), getVec2f(doorKeyLevelsRoomWidth, 30), NONE);

	World_addObstacle(world_p, getVec2f(allFromTopLevelsRoomX, HEIGHT - 30), getVec2f(allFromTopLevelsRoomWidth, 30), NONE);

	World_addObstacle(world_p, getVec2f(allFromTopLevelsRoomX, 170), getVec2f(220, 10), NONE);

	World_addObstacle(world_p, getVec2f(allFromTopLevelsRoomX + doorKeyLevelsRoomWidth - 280, 170), getVec2f(280, 10), NONE);

	World_addObstacle(world_p, getVec2f(doorKeyLevelsRoomX + doorKeyLevelsRoomWidth, 0), getVec2f(allFromTopLevelsRoomWidth - doorKeyLevelsRoomWidth - 80, 180), NONE);

	World_addObstacle(world_p, getVec2f(houseX + houseWidth - 60, 0), getVec2f(60, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(houseX + houseWidth, 210), getVec2f(playerPositionLevelsRoomX + playerPositionLevelsRoomWidth - houseX - houseWidth, 60), NONE);

	World_addSprite(world_p, getVec2f(houseX + houseWidth + 140, HEIGHT - 60 - 73), getVec2f(14, 73), COLOR_WHITE, "lamp-post", 1, GAME_LAYER_FURNITURE);

	//top of door
	//World_addObstacle(world_p, getVec2f(3250, 30), getVec2f(20, 10), NONE);

	//add house shadows
	//World_addShadow(world_p, getVec2f(houseX + 20, 30), getVec2f(20, HEIGHT - 20));

	//World_addShadow(world_p, getVec2f(houseX + 40, 10), getVec2f(20, HEIGHT - 10));

	//World_addShadow(world_p, getVec2f(houseX + 60, 0), getVec2f(houseWidth - 60 - 20, HEIGHT));

	//second floor
	World_addObstacle(world_p, getVec2f(xySwitchLevelsRoomX, -100), getVec2f(xySwitchLevelsRoomWidth, 100), NONE);

	World_addObstacle(world_p, getVec2f(xySwitchLevelsRoomX, -HEIGHT + 80), getVec2f(40, 90), NONE);

	World_addObstacle(world_p, getVec2f(houseX + houseWidth - 60, -HEIGHT + 80), getVec2f(60, 90), NONE);

	World_addObstacle(world_p, getVec2f(houseX + houseWidth - 60, -100), getVec2f(60, 100), NONE);

	int roofWidth = houseX + houseWidth - xySwitchLevelsRoomX + 60 * 2;
	for(int i = 0; i < roofWidth / 10; i++){
		World_addObstacle(world_p, getVec2f(xySwitchLevelsRoomX - 60 + i * 10, -HEIGHT + 70 - i * 10), getVec2f(roofWidth - i * 20, 10), NONE);
	}

	//player position levels
	//World_addObstacle(world_p, getVec2f(playerPositionLevelsRoomX, -100), getVec2f(playerPositionLevelsRoomWidth, 100), NONE);

	World_addObstacle(world_p, getVec2f(playerPositionLevelsRoomX + playerPositionLevelsRoomWidth, HEIGHT - 160), getVec2f(40, 100), NONE);

	World_addObstacle(world_p, getVec2f(playerPositionLevelsRoomX + playerPositionLevelsRoomWidth + 40, HEIGHT - 160), getVec2f(100, 100), ALL);

	World_addObstacle(world_p, getVec2f(playerPositionLevelsRoomX + playerPositionLevelsRoomWidth, HEIGHT - 60), getVec2f(140, 60), NONE);

	//add boundries
	World_addScaleField(world_p, getVec2f(startingAreaX, cloudY), getVec2f(playerPositionLevelsRoomX + playerPositionLevelsRoomWidth + 140, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(playerPositionLevelsRoomX + playerPositionLevelsRoomWidth + 40 + 100, -HEIGHT * 6), getVec2f(500, HEIGHT * 7), NONE);

	//walls

	int greenWallX = houseX;
	int greenWallWidth = firstLevelsRoomWidth + firstScalingLevelsRoomWidth + coolerScalingLevelsRoomWidth + 40;

	int elevatorWallX = elevatorRoomX;
	int elevatorWallWidth = elevatorRoomWidth;

	int yellowWallX = doorKeyLevelsRoomX;
	int yellowWallWidth = doorKeyLevelsRoomWidth;

	int purpleWallX = allFromTopLevelsRoomX;
	int purpleWallWidth = allFromTopLevelsRoomWidth;

	int scaleFieldWallX = xySwitchLevelsRoomX;
	int scaleFieldWallWidth = xySwitchLevelsRoomWidth;

	World_addSprite(world_p, getVec2f(greenWallX, 0), getVec2f(greenWallWidth, HEIGHT), COLOR_GREEN_WALL, "obstacle", 1, GAME_LAYER_WALLS);

	World_addSprite(world_p, getVec2f(elevatorWallX, 0), getVec2f(elevatorWallWidth, HEIGHT), COLOR_RED_WALL, "obstacle", 1, GAME_LAYER_WALLS);

	World_addSprite(world_p, getVec2f(purpleWallX, 0), getVec2f(purpleWallWidth, HEIGHT), COLOR_PURPLE_WALL, "obstacle", 1, GAME_LAYER_WALLS);

	World_addSprite(world_p, getVec2f(yellowWallX, 0), getVec2f(yellowWallWidth, HEIGHT / 2), COLOR_RED_WALL, "obstacle", 1, GAME_LAYER_WALLS);

	World_addSprite(world_p, getVec2f(scaleFieldWallX, -HEIGHT / 2 - 110), getVec2f(scaleFieldWallWidth + 100, HEIGHT), COLOR_BLUE_WALL, "obstacle", 1, GAME_LAYER_WALLS);

	//set level hub level size
	world_p->levelWidth = playerPositionLevelsRoomX + playerPositionLevelsRoomWidth;
	world_p->levelHeight = HEIGHT * 4;

	//World_addObstacle(world_p, getVec2f(houseX + houseWidth - 120, 150), getVec2f(40, 40), ALL);

	bool doOpenGateParticleEffect = false;
	enum LevelHubRoom openGateParticleEffectRoom;

	//check if rooms are totally completed
	for(int i = 0; i < 5; i++){

		int completedLevelsInRoom = 0;
		
		for(int j = 0; j < world_p->roomLevels[i].length; j++){
			for(int k = 0; k < world_p->saveData.completedLevels.length; k++){
				
				char **roomLevelName_p = Array_getItemPointerByIndex(&world_p->roomLevels[i], j);
				char **completedLevelName_p = Array_getItemPointerByIndex(&world_p->saveData.completedLevels, k);


				if(strcmp(*roomLevelName_p, *completedLevelName_p) == 0){
					completedLevelsInRoom++;
				}

			}
		}

		if(completedLevelsInRoom == world_p->roomLevels[i].length){

			if(i == FIRST_SCALE_ROOM){

				if(!SaveData_hasFlag(&world_p->saveData, "completed-first-scale-levels")){
					doOpenGateParticleEffect = true;
					openGateParticleEffectRoom = FIRST_SCALE_ROOM;
				}

				SaveData_addFlag(&world_p->saveData, "completed-first-scale-levels");

			}
			if(i == DOOR_KEY_ROOM){

				if(!SaveData_hasFlag(&world_p->saveData, "completed-door-key-levels")){
					doOpenGateParticleEffect = true;
					openGateParticleEffectRoom = DOOR_KEY_ROOM;
				}

				SaveData_addFlag(&world_p->saveData, "completed-door-key-levels");
			}
			if(i == ALL_FROM_TOP_ROOM){

				if(!SaveData_hasFlag(&world_p->saveData, "completed-all-from-top-levels")){
					doOpenGateParticleEffect = true;
					openGateParticleEffectRoom = ALL_FROM_TOP_ROOM;
				}

				SaveData_addFlag(&world_p->saveData, "completed-all-from-top-levels");
			}
			if(i == SCALE_FIELD_ROOM){

				if(!SaveData_hasFlag(&world_p->saveData, "completed-scale-field-levels")){
					doOpenGateParticleEffect = true;
					openGateParticleEffectRoom = SCALE_FIELD_ROOM;
				}

				SaveData_addFlag(&world_p->saveData, "completed-scale-field-levels");
			}
			if(i == PLAYER_POSITION_ROOM){

				if(!SaveData_hasFlag(&world_p->saveData, "completed-player-position-levels")){

					//doOpenGateParticleEffect = true;
					//openGateParticleEffectRoom = FIRST_SCALE_ROOM;

					Vec2f *doorKeyPos_p = Array_addItem(&world_p->saveData.doorKeys);
					*doorKeyPos_p = world_p->saveData.playerPos;

				}

				SaveData_addFlag(&world_p->saveData, "completed-player-position-levels");

			}

		}

	}

	//mark completed levels and doors with keys
	for(int i = 0; i < world_p->levelDoors.length; i++){

		LevelDoor *levelDoor_p = Array_getItemPointerByIndex(&world_p->levelDoors, i);
		Sprite *sprite_p = World_getSpriteByIndex(world_p, levelDoor_p->spriteIndex);

		for(int j = 0; j < world_p->saveData.completedLevels.length; j++){
			char *completedLevelName = *((char **)Array_getItemPointerByIndex(&world_p->saveData.completedLevels, j));

			if(strcmp(levelDoor_p->levelName, completedLevelName) == 0){
				sprite_p->texture = "level-door-completed";
			}
		}

		for(int j = 0; j < world_p->saveData.levelsWithDoorKey.length; j++){
			char *levelWithDoorKeyName = *((char **)Array_getItemPointerByIndex(&world_p->saveData.levelsWithDoorKey, j));

			if(strcmp(levelDoor_p->levelName, levelWithDoorKeyName) == 0){
				sprite_p->texture = "level-door-with-key";
			}
		}

		if(levelDoor_p->levelHubRoom == FIRST_SCALE_ROOM
		&& SaveData_hasFlag(&world_p->saveData, "completed-first-scale-levels")
		|| levelDoor_p->levelHubRoom == DOOR_KEY_ROOM
		&& SaveData_hasFlag(&world_p->saveData, "completed-door-key-levels")
		|| levelDoor_p->levelHubRoom == ALL_FROM_TOP_ROOM
		&& SaveData_hasFlag(&world_p->saveData, "completed-all-from-top-levels")
		|| levelDoor_p->levelHubRoom == SCALE_FIELD_ROOM
		&& SaveData_hasFlag(&world_p->saveData, "completed-scale-field-levels")
		|| levelDoor_p->levelHubRoom == PLAYER_POSITION_ROOM
		&& SaveData_hasFlag(&world_p->saveData, "completed-player-position-levels")){
			sprite_p->texture = "level-door";
			sprite_p->color = COLOR_GREY;
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

	//add gate
	if(SaveData_hasFlag(&world_p->saveData, "unlocked-gate-door")){
		//!add nothing!
	}else if(SaveData_hasFlag(&world_p->saveData, "completed-door-key-levels")){
		World_addDoor(world_p, getVec2f(startingAreaX + 60, 140), getVec2f(40, 90), NONE);
	}else{
		World_addObstacle(world_p, getVec2f(startingAreaX + 60, 140), getVec2f(40, 90), NONE);
	}

	if(SaveData_hasFlag(&world_p->saveData, "completed-scale-field-levels")){
		World_addScaleField(world_p, getVec2f(startingAreaX + 120, 140), getVec2f(40, 90), ALL);
	}else{
		World_addObstacle(world_p, getVec2f(startingAreaX + 120, 140), getVec2f(40, 90), NONE);
	}

	if(SaveData_hasFlag(&world_p->saveData, "completed-all-from-top-levels")){
		World_addObstacle(world_p, getVec2f(startingAreaX + 180, 140), getVec2f(40, 90), ALL_FROM_TOP);
	}else{
		World_addObstacle(world_p, getVec2f(startingAreaX + 180, 140), getVec2f(40, 90), NONE);
	}

	if(SaveData_hasFlag(&world_p->saveData, "completed-first-scale-levels")){
		World_addObstacle(world_p, getVec2f(startingAreaX + 240, 140), getVec2f(40, 90), ALL);
	}else{
		World_addObstacle(world_p, getVec2f(startingAreaX + 240, 140), getVec2f(40, 90), NONE);
	}

	SaveData_write(&world_p->saveData);

	world_p->addedRoomLevels = true;

	//doOpenGateParticleEffect = true;
	//openGateParticleEffectRoom = DOOR_KEY_ROOM;

	//open gate particle effect
	if(doOpenGateParticleEffect){

		int counter = 0;

		for(int i = 0; i < world_p->levelDoors.length; i++){

			LevelDoor *levelDoor_p = Array_getItemPointerByIndex(&world_p->levelDoors, i);

			if(levelDoor_p->levelHubRoom != openGateParticleEffectRoom){
				continue;
			}

			Renderer2D_Color targetColor;
			if(openGateParticleEffectRoom == FIRST_SCALE_ROOM){
				targetColor = COLOR_GREEN;
			}
			if(openGateParticleEffectRoom == DOOR_KEY_ROOM){
				targetColor = COLOR_RED;
			}
			if(openGateParticleEffectRoom == ALL_FROM_TOP_ROOM){
				targetColor = COLOR_PURPLE;
			}
			if(openGateParticleEffectRoom == SCALE_FIELD_ROOM){
				targetColor = COLOR_BLUE;
			}
			if(openGateParticleEffectRoom == PLAYER_POSITION_ROOM){
				targetColor = COLOR_BLUE;
			}

			World_getSpriteByIndex(world_p, levelDoor_p->spriteIndex)->texture = "level-door";
			World_getSpriteByIndex(world_p, levelDoor_p->spriteIndex)->color = COLOR_GREY;

			Vec2f pos = levelDoor_p->body.pos;
			//pos.x += 5;
			//pos.y += 3;

			//World_addParticle(world_p, pos, getVec2f(20, 15), "level-door-completed", counter * 10, COLOR_WHITE, targetColor);

			counter++;
			
		}
	
	}

}
