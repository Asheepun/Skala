#ifndef LEVELS_H_
#define LEVELS_H_

void World_generateLevel1(World *);

void World_generateLevel2(World *);

static void (*levels[255])(World *w) = {
	World_generateLevel1,
	World_generateLevel2,
}

#endif