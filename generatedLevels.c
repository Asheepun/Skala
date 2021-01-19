#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "utils.h"
#include "stb_truetype.h"
#include "text.h"
#include "game.h"
#include "levels.h"

World_generateLevel1(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

}

World_generateLevel2(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 110), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(280, 190), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(world_p, getVec2f(320, 170), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(world_p, getVec2f(360, 150), getVec2f(WIDTH, 20), ALL);

}

World_generateLevel3(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(210, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 210, 210), getVec2f(210, 60), ALL);

}

World_generateLevel4(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(160, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 160, 210), getVec2f(160, 60), ALL);

	World_addTextSprite(world_p, getVec2f(140, 140), "Use the \"X\" key", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

}

World_generateLevel5(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 180, 110), getVec2f(180, 100), ALL);

}

World_generateLevel6(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL);


}

World_generateLevel7(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

}

World_generateLevel8(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(340, 140), getVec2f(80, 130), ALL);

}

World_generateLevel9(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(420, 140), getVec2f(1.5, 130), ALL);

}

World_generateLevel10(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

}

World_generateLevel11(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(400, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 100), getVec2f(WIDTH, HEIGHT - 160), NONE);

}

World_generateLevel12(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(400, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(300, 40), getVec2f(WIDTH, HEIGHT - 100), NONE);

}

World_generateLevel13(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL);

}

World_generateLevel14(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 100), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(240, 0 - 10000), getVec2f(60, HEIGHT - 70 + 10000), ALL);

}

World_generateLevel15(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(320, 0 - 2000), getVec2f(20, HEIGHT - 60 + 2000), ALL);

}

World_generateLevel16(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

}

World_generateLevel17(World *world_p){

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

}

World_generateLevel18(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 170), NONE);

}

World_generateLevel19(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 60), getVec2f(20, 90), NONE);

	World_addObstacle(world_p, getVec2f(260, 40), getVec2f(WIDTH, 20), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(420, 0), ALL);

}

World_generateLevel20(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	//World_addObstacle(world_p, getVec2f(240, 20), getVec2f(20, 35), NONE);

	World_addObstacle(world_p, getVec2f(0, 60), getVec2f(300, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(300, 20), NONE);

	World_addDoor(world_p, getVec2f(300, 0), getVec2f(20, HEIGHT - 60), NONE);

	World_addDoorKey(world_p, getVec2f(90, 20), ALL);

}

World_generateLevel21(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(240, 20), getVec2f(20, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 60), getVec2f(300, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(300, 20), NONE);

	World_addDoor(world_p, getVec2f(300, 0), getVec2f(20, HEIGHT - 60), NONE);

	World_addDoorKey(world_p, getVec2f(90, 20), ALL);

}

World_generateLevel22(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 120), getVec2f(210, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(220, 40), NONE);

	World_addObstacle(world_p, getVec2f(220, 120), getVec2f(260, 150), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(300, 60), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(100, 230), ALL);

}

World_generateLevel23(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 120), getVec2f(210, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(220, 40), NONE);

	World_addObstacle(world_p, getVec2f(220, 120), getVec2f(260, 150), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(300, 60), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(210, 0), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(100, 230), ALL);

}

World_generateLevel24(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 10), ALL);

	World_addDoor(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(100, 30), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 50, 90), getVec2f(50, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 110, 50), getVec2f(20, 135), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 30, 70), ALL);

}

World_generateLevel25(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(200, 150), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(150, 210), getVec2f(180, 20), NONE);

	World_addObstacle(world_p, getVec2f(150, 230), getVec2f(195, 40), NONE);

	World_addObstacle(world_p, getVec2f(150, 110), getVec2f(180, 40), NONE);

	World_addObstacle(world_p, getVec2f(150, 150), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(310, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(220, 50), NONE);

}

World_generateLevel26(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(30, 50), NONE);

	World_addPoint(world_p, getVec2f(420, 230), ALL);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(WIDTH - 130, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 260), getVec2f(WIDTH - 100, 10), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, 60), getVec2f(30, HEIGHT - 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 20), getVec2f(20, HEIGHT - 30), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 120, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

}

World_generateLevel27(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(30, 50), NONE);

	World_addPoint(world_p, getVec2f(420, 230), ALL);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(100, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 260), getVec2f(WIDTH - 100, 10), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, 60), getVec2f(30, HEIGHT - 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 20), getVec2f(20, HEIGHT - 30), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 120, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

}

World_generateLevel28(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(30, 50), NONE);

	World_addPoint(world_p, getVec2f(420, 230), ALL);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 260), getVec2f(WIDTH - 100, 10), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, 60), getVec2f(30, HEIGHT - 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 20), getVec2f(20, HEIGHT - 30), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 120, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);
}
