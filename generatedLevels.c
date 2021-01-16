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

	World_initPlayer(world_p, getVec2f(50, 100), NONE);

	World_addPoint(world_p, getVec2f(270, 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 160), getVec2f(WIDTH, 20), NONE);

}

World_generateLevel2(World *world_p){

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 100), NONE);

	World_addPoint(world_p, getVec2f(270, 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 160), getVec2f(WIDTH, 20), ALL);

}
