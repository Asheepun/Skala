#ifndef LEVELS_H_
#define LEVELS_H_

typedef struct Level{
	char *name;
	void (*generate)(World *);
}Level;

World_generateLevel1(World *);
World_generateLevel2(World *);

static const size_t LEVELS_LENGTH = 2;

static Level levels[255] = {
	"level-1",
	World_generateLevel1,
	"level-2",
	World_generateLevel2,
};

#endif