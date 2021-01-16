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

	World_initPlayer(world_p, getVec2f(50, 100), NONE);

	World_addObstacle(world_p, getVec2f(0, 160), getVec2f(WIDTH, 20), NONE);

	World_addLevelDoor(world_p, getVec2f(100, 115), "level-1");

	World_addLevelDoor(world_p, getVec2f(200, 115), "level-2");

}
