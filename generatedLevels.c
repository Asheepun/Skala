#include "engine/engine.h"
#include "math.h"
#include "stdio.h"
#include "game.h"
#include "levels.h"

void World_generateLevel1(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	World_initPlayer(world_p, getVec2f(270, 100), NONE);

	World_addPoint(world_p, getVec2f(1380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 100), getVec2f(40, 100), NONE);

	World_addObstacle(world_p, getVec2f(100, 100), getVec2f(40, 60), ALL);


	//World_addObstacle(world_p, getVec2f(300, 100), getVec2f(40, 80), ALL);

	World_addObstacle(world_p, getVec2f(400, 100), getVec2f(40, 100), NONE);

	World_addDoorKey(world_p, getVec2f(100, 100), ALL);

}

void World_generateLevel2(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

}

void World_generateLevel3(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 110), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(280, 190), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(world_p, getVec2f(320, 170), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(world_p, getVec2f(360, 150), getVec2f(WIDTH, 20), ALL);

}

void World_generateLevel4(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(210, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 210, 210), getVec2f(210, 60), ALL);

}

void World_generateLevel5(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(160, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 160, 210), getVec2f(160, 60), ALL);

	char text[255];
	sprintf(text, "%s key to scale", Engine_keyNames[world_p->actions[5].bindings[0]]);

	World_addTextSprite(world_p, getVec2f(140, 140), text, "times20", COLOR_WHITE, GAME_LAYER_TEXT);

}

void World_generateLevel6(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 180, 110), getVec2f(180, 100), ALL);

}

void World_generateLevel7(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL);

}

void World_generateLevel8(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

}

void World_generateLevel9(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(340, 140), getVec2f(80, 130), ALL);

}

void World_generateLevel10(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(420, 140), getVec2f(1.5, 130), ALL);

}

void World_generateLevel11(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20 + BIG_BLOCKING_SIZE, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

	World_addObstacle(world_p, getVec2f(370, -BIG_BLOCKING_SIZE), getVec2f(BIG_BLOCKING_SIZE, BIG_BLOCKING_SIZE), NONE);

	World_addObstacle(world_p, getVec2f(370, HEIGHT - 20), getVec2f(90, 20), NONE);

}

void World_generateLevel12(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 190), getVec2f(WIDTH - 130, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(20, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH - 130, 20), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20 + BIG_BLOCKING_SIZE, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(370, -BIG_BLOCKING_SIZE), getVec2f(BIG_BLOCKING_SIZE, BIG_BLOCKING_SIZE), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);
	
	World_addObstacle(world_p, getVec2f(370, HEIGHT - 20), getVec2f(90, 20), NONE);

}

void World_generateLevel13(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(150, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(110, 190), getVec2f(WIDTH - 240, 20), NONE);

	World_addObstacle(world_p, getVec2f(110, 0), getVec2f(WIDTH - 240, 20), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20 + BIG_BLOCKING_SIZE, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(0, -BIG_BLOCKING_SIZE), getVec2f(BIG_BLOCKING_SIZE, BIG_BLOCKING_SIZE), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

	World_addObstacle(world_p, getVec2f(370, HEIGHT - 20), getVec2f(90, 20), NONE);

	//World_addObstacle(world_p, getVec2f(110, 0), getVec2f(WIDTH - 240, 20), NONE);

	World_addObstacle(world_p, getVec2f(90, 0), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH - 110, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, 0), getVec2f(70, 20), NONE);

	//World_addObstacle(world_p, getVec2f(90, HEIGHT - 40), getVec2f(20, 20), NONE);

}

void World_generateLevel14(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 0), ALL);

	World_addPoint(world_p, getVec2f(400, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 70), getVec2f(150, 200), NONE);

	World_addObstacle(world_p, getVec2f(340, 0), getVec2f(20, 95), NONE);

	World_addObstacle(world_p, getVec2f(360, 0), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, 100), NONE);

	World_addObstacle(world_p, getVec2f(340, 100), getVec2f(140, 170), NONE);

}

void World_generateLevel15(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(400, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 100), getVec2f(WIDTH, HEIGHT - 160), NONE);

}

void World_generateLevel16(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(400, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(WIDTH, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(300, 40), getVec2f(WIDTH, HEIGHT - 110), NONE);

	World_addObstacle(world_p, getVec2f(50, 10), getVec2f(30, HEIGHT - 83), NONE);

}

void World_generateLevel17(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 100), ALL);

	World_addPoint(world_p, getVec2f(430, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(160, 70), NONE);

	World_addObstacle(world_p, getVec2f(160, 250), getVec2f(WIDTH - 300, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(100, 40), getVec2f(60, HEIGHT - 110), NONE);

	World_addObstacle(world_p, getVec2f(240, 10), getVec2f(30, 70), NONE);

	World_addObstacle(world_p, getVec2f(160, 200), getVec2f(120, 70), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 80, 40), getVec2f(80, 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 100), getVec2f(20, HEIGHT - 100), NONE);

}

void World_generateLevel18(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL);

}

void World_generateLevel19(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 100), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(240, 0 - 10000), getVec2f(60, HEIGHT - 70 + 10000), ALL);

}

void World_generateLevel20(World *world_p){

	World_restore(world_p);

	world_p->obstaclesCannotCollideWithEachOther = true;

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	int size = 2200;

	World_addObstacle(world_p, getVec2f(320, 0 - size - 100), getVec2f(20, HEIGHT + size + 100), ALL);

	World_addObstacle(world_p, getVec2f(0, 0 - size - BIG_BLOCKING_SIZE), getVec2f(340, BIG_BLOCKING_SIZE), ALL);

}

void World_generateLevel21(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

}

void World_generateLevel22(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

}

void World_generateLevel23(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 170), NONE);

}

void World_generateLevel24(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 0), ALL);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(120, 20), NONE);

}

void World_generateLevel25(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 0), ALL);

}

void World_generateLevel26(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 30), ALL);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(120, 20), NONE);

	World_addObstacle(world_p, getVec2f(110, 0), getVec2f(10, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, -HEIGHT), getVec2f(110, HEIGHT + 10), NONE);

	World_addObstacle(world_p, getVec2f(0, 10), getVec2f(10, 40), NONE);

}

void World_generateLevel27(World *world_p){
}

void World_generateLevel28(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 120), getVec2f(210, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(220, 40), NONE);

	World_addObstacle(world_p, getVec2f(220, 120), getVec2f(260 + BIG_BLOCKING_SIZE, 150), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(60, 210), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, HEIGHT), getVec2f(BIG_BLOCKING_SIZE, BIG_BLOCKING_SIZE), NONE);

	World_addDoor(world_p, getVec2f(300, 60), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(120, 210), ALL);

}

void World_generateLevel29(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(90, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 120), getVec2f(210, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(220, 40), NONE);

	World_addObstacle(world_p, getVec2f(220, 120), getVec2f(260 + BIG_BLOCKING_SIZE, 150), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(300, 60), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(60, 210), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, HEIGHT), getVec2f(BIG_BLOCKING_SIZE, BIG_BLOCKING_SIZE), NONE);

	World_addDoor(world_p, getVec2f(210, 0), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(120, 210), ALL);

	char text[255];
	sprintf(text, "%s key to restart level ", Engine_keyNames[world_p->actions[4].bindings[0]]);

	World_addTextSprite(world_p, getVec2f(25, 40), text, "times20", COLOR_WHITE, GAME_LAYER_TEXT);

}

void World_generateLevel30(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 20), ALL);

	World_addDoor(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(100, 40), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 60, 90), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 50), getVec2f(20, 135), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 10, 0), getVec2f(10, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 10, 50), getVec2f(10, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 10, 90), getVec2f(10, 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 40, 70), ALL);

}

void World_generateLevel31(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	World_initPlayer(world_p, getVec2f(200, 150), NONE);

	//World_addPoint(world_p, getVec2f(380, 170), NONE);
	World_addPoint(world_p, getVec2f(420, 170), NONE);

	World_addObstacle(world_p, getVec2f(150, 210), getVec2f(180, 20), NONE);

	World_addObstacle(world_p, getVec2f(150, 230), getVec2f(200, 40), NONE);

	World_addObstacle(world_p, getVec2f(150, 110), getVec2f(180, 40), NONE);

	World_addObstacle(world_p, getVec2f(150, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(250, 170), getVec2f(20, 10), ALL);

	World_addDoor(world_p, getVec2f(310, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(220, 50), NONE);

}

void World_generateLevel32(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 150), NONE);

	World_addPoint(world_p, getVec2f(445, 230), ALL);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 60), getVec2f(120, 60), NONE);

	World_addDoorKey(world_p, getVec2f(0, 100), ALL);

	World_addDoor(world_p, getVec2f(440, HEIGHT - 70), getVec2f(20, 20), NONE);

	//World_addObstacle(world_p, getVec2f(WIDTH - 60, HEIGHT - 20), getVec2f(60, 20), NONE);

	//World_addObstacle(world_p, getVec2f(WIDTH - 60, HEIGHT - 20), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 60, HEIGHT - 80), getVec2f(20, 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, HEIGHT - 80), getVec2f(20, 80), NONE);

	World_addObstacle(world_p, getVec2f(120, HEIGHT - 10), getVec2f(WIDTH - 180, 10), NONE);

}

void World_generateLevel33(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH - 100, 50), NONE);

	world_p->player.facing = 0;

	World_addPoint(world_p, getVec2f(40, 230), ALL);

	World_addObstacle(world_p, getVec2f(90, 200), getVec2f(WIDTH * 100, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 20), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, HEIGHT - 10), getVec2f(50, 10), NONE);

	World_addObstacle(world_p, getVec2f(70, 60), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 20), getVec2f(40, HEIGHT - 70 - 20), NONE);

	World_addDoor(world_p, getVec2f(70, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

}

void World_generateLevel34(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH - 100, 50), NONE);

	world_p->player.facing = 0;

	World_addPoint(world_p, getVec2f(40, 230), ALL);

	World_addObstacle(world_p, getVec2f(90, 250), getVec2f(WIDTH * 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 20), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, HEIGHT - 10), getVec2f(50, 10), NONE);

	World_addObstacle(world_p, getVec2f(70, 60), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 20), getVec2f(40, HEIGHT - 20 - 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 200), getVec2f(100, 50), NONE);

	World_addDoor(world_p, getVec2f(70, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

}

void World_generateLevel35(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH - 100, 50), NONE);

	world_p->player.facing = 0;

	World_addPoint(world_p, getVec2f(40, 230), ALL);

	World_addObstacle(world_p, getVec2f(90, 250), getVec2f(WIDTH * 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 20), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, HEIGHT - 10), getVec2f(50, 10), NONE);

	World_addObstacle(world_p, getVec2f(70, 60), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 20), getVec2f(40, HEIGHT - 20 - 20), NONE);

	World_addDoor(world_p, getVec2f(70, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

}

void World_generateLevel36(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 170), NONE);

	World_addPoint(world_p, getVec2f(420, 190), ALL);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 170), getVec2f(40, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 190), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(80, 20), NONE);

	World_addObstacle(world_p, getVec2f(360, 0), getVec2f(20, HEIGHT - 100), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(380, 0), getVec2f(80, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(380, 20), NONE);

	World_addDoor(world_p, getVec2f(360, HEIGHT - 100), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(200, 170), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(150, 150), getVec2f(80, 20), NONE);

	World_addDoorKey(world_p, getVec2f(90, 100), ALL);

}

void World_generateLevel37(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL_FROM_TOP);

}

void World_generateLevel38(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

}

void World_generateLevel39(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL_FROM_TOP);

	World_addPoint(world_p, getVec2f(420, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(380, 60), getVec2f(100, HEIGHT - 120), NONE);

}

void World_generateLevel40(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(70, 210), ALL);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(WIDTH * 3, 10), ALL_FROM_TOP);

}

void World_generateLevel41(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH / 2 - 10, 50), ALL_FROM_TOP);

	World_addPoint(world_p, getVec2f(WIDTH / 2 - 5, 140), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 - 60, 100), getVec2f(120, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 - 60, 120), getVec2f(20, 50), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 + 60 - 20, 120), getVec2f(20, 50), NONE);

}

void World_generateLevel42(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(110, 100), NONE);

	World_addPoint(world_p, getVec2f(30, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 230), getVec2f(100, 40), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 130, 180), getVec2f(30, 90), NONE);

	World_addDoor(world_p, getVec2f(230, 120), getVec2f(30, 90), NONE);

	World_addObstacle(world_p, getVec2f(230, 0), getVec2f(30, 120), NONE);

	World_addObstacle(world_p, getVec2f(260, 0), getVec2f(200, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 50, 150), ALL_FROM_TOP);

}

void World_generateLevel43(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(110, 100), NONE);

	World_addPoint(world_p, getVec2f(30, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 230), getVec2f(120, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 0), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 120, 20), getVec2f(30, HEIGHT - 60), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 50, 150), ALL_FROM_TOP);


}

void World_generateLevel44(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 120), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addScaleField(world_p, getVec2f(280, 50), getVec2f(50, HEIGHT - 50), NONE);


}

void World_generateLevel45(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 10, 0), getVec2f(10, HEIGHT), NONE);

	World_addScaleField(world_p, getVec2f(330, 0), getVec2f(140, HEIGHT), ALL);

}

void World_generateLevel46(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(420, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 150, 70), getVec2f(150, HEIGHT - 130), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, -BIG_BLOCKING_SIZE), getVec2f(100, BIG_BLOCKING_SIZE + 40), NONE);

	World_addScaleField(world_p, getVec2f(220, 180), getVec2f(40, 30), ALL);

	World_addScaleField(world_p, getVec2f(0, 30), getVec2f(60, 40), ALL);

}

void World_generateLevel47(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 200), NONE);

	World_addPoint(world_p, getVec2f(420, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addScaleField(world_p, getVec2f(0, 230), getVec2f(WIDTH, 40), ALL);

}

void World_generateLevel48(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(30, 50), NONE);

	World_addPoint(world_p, getVec2f(440, 100), NONE);

	World_addObstacle(world_p, getVec2f(0, 70), getVec2f(100, 200), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 50, 190), getVec2f(50, 80), NONE);

	//World_addObstacle(world_p, getVec2f(50, 50), getVec2f(50, 50), NONE);

	//World_addObstacle(world_p, getVec2f(340, 210), getVec2f(20, 30), NONE);

	//World_addObstacle(world_p, getVec2f(WIDTH - 20, 210), getVec2f(20, 40), NONE);
	//
	World_addScaleField(world_p, getVec2f(100, 150), getVec2f(WIDTH - 150, HEIGHT - 150), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 150), getVec2f(50, 40), ALL_FROM_TOP);

	//World_addScaleField(world_p, getVec2f(50, 50), getVec2f(50, 160), ALL_FROM_TOP);

	/*
	World_addScaleField(world_p, getVec2f(360, 0), getVec2f(100, 50), ALL);

	World_addScaleField(world_p, getVec2f(360, 50), getVec2f(100, 50), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(360, 100), getVec2f(100, 50), ALL);

	World_addScaleField(world_p, getVec2f(360, 150), getVec2f(100, 50), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(360, 200), getVec2f(100, 50), ALL);
	*/

}

void World_generateLevel49(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 190), NONE);

	World_addPoint(world_p, getVec2f(250, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 105), NONE);

}

void World_generateLevel50(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(100, 100), NONE);

	World_addPoint(world_p, getVec2f(350, 200), NONE);

	World_addObstacle(world_p, getVec2f(0, 120), getVec2f(WIDTH - 150, 10), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 120), getVec2f(100, 10), NONE);

	World_addObstacle(world_p, getVec2f(80, 150), getVec2f(40, 40), ALL_FROM_TOP);

	//World_addObstacle(world_p, getVec2f(0, 0), getVec2f(40, 120), NONE);

}

void World_generateLevel51(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 190), ALL);

	World_addPoint(world_p, getVec2f(WIDTH / 2 + 100, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, -BIG_BLOCKING_SIZE), getVec2f(WIDTH, BIG_BLOCKING_SIZE + HEIGHT - 60), NONE);

}

void World_generateLevel52(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(200, 30), ALL_FROM_TOP);

	World_addPoint(world_p, getVec2f(210, 240), NONE);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(100, 150), getVec2f(150, 20), NONE);

	World_addObstacle(world_p, getVec2f(230, 170), getVec2f(20, 200), NONE);

}

void World_generateLevel53(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(200, 190), NONE);

	World_addPoint(world_p, getVec2f(400, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 150, 90), getVec2f(150, 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, HEIGHT), NONE);

	World_addScaleField(world_p, getVec2f(100, 190), getVec2f(50, 20), ALL);

}

void World_generateLevel54(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 190), NONE);

	World_addPoint(world_p, getVec2f(400, 170), NONE);

	World_addDoor(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addDoor(world_p, getVec2f(350, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(100, 190), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(120, 170), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(140, 150), getVec2f(20, 20), NONE);

	World_addDoorKey(world_p, getVec2f(400, 0), ALL);

	World_addObstacle(world_p, getVec2f(350, 50), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(430, 30), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(350, 30), getVec2f(20, 20), NONE);

}

void World_generateLevel55(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(1, 150), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 20, 150), NONE);

	World_addObstacle(world_p, getVec2f(70, 170), getVec2f(190, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(260, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 190), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(40, 20), NONE);

	//World_addObstacle(world_p, getVec2f(240, 190), getVec2f(20, 20), NONE);

	//World_addObstacle(world_p, getVec2f(220, 210), getVec2f(40, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 190), getVec2f(40, 100), NONE);

	World_addScaleField(world_p, getVec2f(130, 150), getVec2f(40, 20), ALL);

	World_addObstacle(world_p, getVec2f(130, 130), getVec2f(40, 20), NONE);

	//World_addScaleField(world_p, getVec2f(100, 210), getVec2f(20, 20), ALL);

}

void World_generateLevel56(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 0), NONE);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(100, 40), NONE);

	World_addPoint(world_p, getVec2f(10, 190), NONE);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(30, 60), NONE);

	World_addDoor(world_p, getVec2f(40, 170), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(400, 150), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 40), getVec2f(WIDTH, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 60), getVec2f(20, HEIGHT - 100), NONE);

}

void World_generateLevel57(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 0), NONE);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(100, 40), NONE);

	World_addPoint(world_p, getVec2f(10, 190), NONE);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(30, 60), NONE);

	World_addDoor(world_p, getVec2f(40, 170), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(400, 150), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 40), getVec2f(WIDTH, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 300, 0), getVec2f(20, 180), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 140, 110), getVec2f(20, 120), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 70), getVec2f(20, 40), NONE);

}

void World_generateLevel58(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 0), NONE);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(100, 40), NONE);

	World_addPoint(world_p, getVec2f(10, 190), NONE);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(30, 60), NONE);

	World_addDoor(world_p, getVec2f(40, 170), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(400, 150), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 40), getVec2f(WIDTH, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	//World_addDoor(world_p, getVec2f(WIDTH - 300, 0), getVec2f(20, 180), NONE);

	//World_addDoor(world_p, getVec2f(WIDTH - 140, 110), getVec2f(20, 120), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 70), getVec2f(20, HEIGHT - 110), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 170, 0), getVec2f(10, 150), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 240, 120), getVec2f(20, HEIGHT - 160), NONE);

}

void World_generateLevel59(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 100), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 180), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

	World_addScaleField(world_p, getVec2f(370, 60), getVec2f(90, HEIGHT - 60), ALL);

	World_addScaleField(world_p, getVec2f(240, 60), getVec2f(90, HEIGHT - 60), ALL);


}

void World_generateLevel60(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

}

void World_generateLevel61(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 200, 130), getVec2f(200, 80), NONE);

}

void World_generateLevel62(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(100, 60), NONE);

}

void World_generateLevel63(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 200, 130), getVec2f(200, 80), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(40, 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 270, 0), getVec2f(40, 170), NONE);

	World_addObstacle(world_p, getVec2f(40, 0), getVec2f(170, 20), NONE);

}

void World_generateLevel64(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH * 100, 60), NONE);

}

void World_generateLevel65(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH * 100, 60), NONE);

	World_addObstacle(world_p, getVec2f(200, 0), getVec2f(40, 60), NONE);

}

void World_generateLevel66(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 170), ALL);

	//World_addDoorKey(world_p, getVec2f(70, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH - 200, 60), NONE);

	World_addScaleField(world_p, getVec2f(200, 40), getVec2f(60, 170), NONE);

}

void World_generateLevel67(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 170), ALL);

	//World_addDoorKey(world_p, getVec2f(70, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH - 200, 60), NONE);

	World_addScaleField(world_p, getVec2f(200, 0), getVec2f(60, 40), NONE);

}

void World_generateLevel68(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 70), ALL);

	//World_addDoorKey(world_p, getVec2f(70, 90), NONE);

	World_addObstacle(world_p, getVec2f(30, 200), getVec2f(WIDTH - 330, 70), NONE);

}

void World_generateLevel69(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(20, 170), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 150, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH * 100, 60), NONE);

	World_addObstacle(world_p, getVec2f(50, 90), getVec2f(20, 20), ALL);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, -BIG_BLOCKING_SIZE), getVec2f(20, HEIGHT + BIG_BLOCKING_SIZE), NONE);

}

void World_generateLevel70(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(50, 100), ALL);

	World_addPoint(world_p, getVec2f(WIDTH - 50, 230), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(100, 70), NONE);

	World_addObstacle(world_p, getVec2f(200, 200), getVec2f(60, 70), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 200), getVec2f(60, 70), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 30, -HEIGHT), getVec2f(30, 2 * HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

}

void World_generateLevel71(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(30, 170), NONE);

	World_addDoorKey(world_p, getVec2f(200, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addScaleField(world_p, getVec2f(250, 130), getVec2f(80, 80), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, -BIG_BLOCKING_SIZE), getVec2f(20, 210 + BIG_BLOCKING_SIZE), NONE);

}

void World_generateLevel72(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(10, 170), NONE);

	World_addDoorKey(world_p, getVec2f(200, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, -BIG_BLOCKING_SIZE), getVec2f(20, 210 + BIG_BLOCKING_SIZE), NONE);

}

void World_generateLevel73(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(WIDTH - 60, 170), NONE);

	World_addDoorKey(world_p, getVec2f(50, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(200, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 200, 210), getVec2f(200, 60), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 100, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 130), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 150), getVec2f(20, 60), NONE);

}

void World_generateLevel74(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 190), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 70, 50), NONE);

	World_addObstacle(world_p, getVec2f(20, 210), getVec2f(80, 20), ALL);

}

void World_generateLevel75(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 130), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 60, 130), NONE);

	World_addObstacle(world_p, getVec2f(50, 170), getVec2f(15, 20), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(100, 150), getVec2f(20, 20), NONE);

	//World_addObstacle(world_p, getVec2f(200, 130), getVec2f(20, 40), NONE);

	World_addScaleField(world_p, getVec2f(300, 150), getVec2f(20, 20), NONE);

}

void World_generateLevel76(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(20, 190), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 70 , 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 50), getVec2f(100, HEIGHT - 70), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 20), getVec2f(20, 30), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, -HEIGHT), getVec2f(100, HEIGHT + 20), NONE);

	World_addScaleField(world_p, getVec2f(50, 0), getVec2f(140, HEIGHT - 20), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(190, 0), getVec2f(140, HEIGHT - 20), ALL);

}

void World_generateLevel77(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 190), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 60, 130), NONE);

	World_addObstacle(world_p, getVec2f(50, 210), getVec2f(60, 30), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(0, 00), getVec2f(50, HEIGHT), ALL);

	//World_addObstacle(world_p, getVec2f(200, 60), getVec2f(60, 210), NONE);

}

void World_generateLevel78(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 190), NONE);

	World_addPoint(world_p, getVec2f(50, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 150, 60), getVec2f(60, 10), ALL);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 00), getVec2f(50, HEIGHT - 60), ALL_FROM_TOP);

	//World_addDoorKey(world_p, getVec2f(70, 190), ALL);

}

void World_generateLevel79(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 30), NONE);

	World_addPoint(world_p, getVec2f(70, 190), NONE);

	World_addObstacle(world_p, getVec2f(40, 50), getVec2f(80, 20), ALL);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, HEIGHT), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 0), getVec2f(50, HEIGHT), ALL_FROM_TOP);

}

void World_generateLevel80(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(20, 100), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 50, 250), NONE);

	World_addObstacle(world_p, getVec2f(20, 120), getVec2f(15, 40), ALL);

	World_addScaleField(world_p, getVec2f(200, 60), getVec2f(50, 100), ALL_FROM_TOP);

	//World_addScaleField(world_p, getVec2f(WIDTH - 200, 0), getVec2f(50, HEIGHT), NONE);

	//World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 210), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, -BIG_BLOCKING_SIZE), getVec2f(10, BIG_BLOCKING_SIZE + HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(200, 190), getVec2f(WIDTH - 200, 20), NONE);

	World_addScaleField(world_p, getVec2f(220, 210), getVec2f(WIDTH - 220, 60), NONE);

}

void World_generateLevel81(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 50, 250-1000), NONE);

	World_addObstacle(world_p, getVec2f(50, 70), getVec2f(80, 20), NONE);

	World_addObstacle(world_p, getVec2f(190, 70), getVec2f(80, 20), NONE);

	World_addObstacle(world_p, getVec2f(20, 200), getVec2f(80, 20), ALL);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 100), getVec2f(50, 110), ALL_FROM_TOP);

}

void World_generateLevel82(World *world_p){

	World_restore(world_p);

	world_p->obstaclesNeedArrows = true;

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 30), NONE);

	World_addPoint(world_p, getVec2f(30, 130), NONE);

	World_addObstacle(world_p, getVec2f(40, 50), getVec2f(80, 20), ALL);

	World_addObstacle(world_p, getVec2f(0, 90), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(80, 110), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, 100), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 0), getVec2f(50, HEIGHT), ALL_FROM_TOP);

}

void World_generateLevel83(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 30), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 80, 150), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 200, 0), getVec2f(20, HEIGHT), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 130, 120), getVec2f(100, 100), ALL);

	World_addScaleField(world_p, getVec2f(WIDTH - 260, 120), getVec2f(130, 100), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(WIDTH - 230, 0), getVec2f(100, 40), NONE);

}

void World_generateLevel84(World *world_p){

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(100, 30), NONE);

	World_addPoint(world_p, getVec2f(230, 210), ALL);

	World_addScaleField(world_p, getVec2f(WIDTH - 100, 0), getVec2f(100, HEIGHT), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, 100), getVec2f(200, HEIGHT - 100), NONE);

}

void World_generateLevel85(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(200, HEIGHT - 40), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 65, 210), ALL);

	World_addDoorKey(world_p, getVec2f(250, HEIGHT - 30), ALL);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH - 140, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH - 20, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 80, HEIGHT - 20), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 0), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 80), getVec2f(20, HEIGHT - 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 80), getVec2f(20, HEIGHT - 80), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 120, 80), getVec2f(20, HEIGHT - 80), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 60), getVec2f(60, 20), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 100, 20), getVec2f(20, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 50), getVec2f(120, 30), NONE);

}

void World_generateLevel86(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 30), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 65, 210), ALL);

	World_addDoorKey(world_p, getVec2f(200, HEIGHT - 30), ALL);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH - 140, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH - 20, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 80, HEIGHT - 20), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 0), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 80), getVec2f(20, HEIGHT - 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 80), getVec2f(20, HEIGHT - 80), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 120, 80), getVec2f(20, HEIGHT - 80), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 60), getVec2f(60, 20), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 100, 20), getVec2f(20, 40), NONE);

}

void World_generateLevel87(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(150, 190), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 95, 195), NONE);

	World_addObstacle(world_p, getVec2f(70, HEIGHT - 40), getVec2f(WIDTH - 90, 40), NONE);

	World_addScaleField(world_p, getVec2f(0, 90), getVec2f(WIDTH - 20, 30), NONE);

	World_addObstacle(world_p, getVec2f(80, 120), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 80), getVec2f(80, 10), NONE);

	World_addObstacle(world_p, getVec2f(70, 120), getVec2f(10, HEIGHT - 120), NONE);

	World_addScaleField(world_p, getVec2f(0, 120), getVec2f(70, HEIGHT - 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, 90), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 20, 90), getVec2f(20, HEIGHT - 90), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 60, 120), getVec2f(40, 110), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(100, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(BIG_BLOCKING_SIZE, 20), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 140, HEIGHT - 100), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(40, 50), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 140), getVec2f(80, 30), NONE);


}

void World_generateLevel88(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(200, 60), ALL);

}

void World_generateLevel89(World *world_p){

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(90, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addDoorKey(world_p, getVec2f(90, 100), NONE);

	World_addObstacle(world_p, getVec2f(50, 210), getVec2f(100, 60), ALL);

}

void World_generateLevel90(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(150, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(110, 190), getVec2f(WIDTH - 240, 20), NONE);

	World_addScaleField(world_p, getVec2f(90, 210), getVec2f(WIDTH - 220, 10), NONE);

	World_addScaleField(world_p, getVec2f(110, 20), getVec2f(WIDTH - 240, 10), NONE);

	World_addObstacle(world_p, getVec2f(110, 0), getVec2f(WIDTH - 240, 20), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20 + BIG_BLOCKING_SIZE, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(0, -BIG_BLOCKING_SIZE), getVec2f(BIG_BLOCKING_SIZE, BIG_BLOCKING_SIZE), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

	World_addObstacle(world_p, getVec2f(370, HEIGHT - 20), getVec2f(90, 20), NONE);

	//World_addObstacle(world_p, getVec2f(110, 0), getVec2f(WIDTH - 240, 20), NONE);

	World_addObstacle(world_p, getVec2f(90, 0), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH - 110, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, 0), getVec2f(70, 20), NONE);

}

void World_generateLevel91(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(110, 210 - 20), NONE);

	World_addPoint(world_p, getVec2f(250, 50), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 100), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(0, -BIG_BLOCKING_SIZE), getVec2f(0, BIG_BLOCKING_SIZE), NONE);

	World_addScaleField(world_p, getVec2f(0, 140), getVec2f(50, 50), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(WIDTH - 70, 120), getVec2f(50, 90), NONE);

	World_addScaleField(world_p, getVec2f(0, 20), getVec2f(100, 80), NONE);

}

void World_generateLevel92(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(110, 210 - 20), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, 0), getVec2f(130, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, -BIG_BLOCKING_SIZE), getVec2f(130, BIG_BLOCKING_SIZE), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 110, 210), getVec2f(90, 60), NONE);

	World_addScaleField(world_p, getVec2f(0, 0), getVec2f(100, 210), ALL_FROM_TOP);

}
