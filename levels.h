#ifndef LEVELS_H_
#define LEVELS_H_

typedef struct Level{
	char *name;
	void (*generate)(World *);
}Level;

World_generateLevel1(World *);
World_generateLevel2(World *);
World_generateLevel3(World *);
World_generateLevel4(World *);
World_generateLevel5(World *);

static const size_t LEVELS_LENGTH = 5;

static Level levels[255] = {
	"level-1",
	World_generateLevel1,
	"level-2",
	World_generateLevel2,
	"level-3",
	World_generateLevel3,
	"level-4",
	World_generateLevel4,
	"level-5",
	World_generateLevel5,
};

#endif