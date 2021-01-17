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

	//World_addObstacle(world_p, getVec2f(0, 210), getVec2f(140, 20), ALL);

	//World_addObstacle(world_p, getVec2f(200, 210), getVec2f(WIDTH, 20), ALL);

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
