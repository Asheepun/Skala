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
World_generateLevel6(World *);
World_generateLevel7(World *);
World_generateLevel8(World *);
World_generateLevel9(World *);
World_generateLevel10(World *);
World_generateLevel11(World *);
World_generateLevel12(World *);
World_generateLevel13(World *);
World_generateLevel14(World *);

static const size_t LEVELS_LENGTH = 14;

static Level levels[255] = {
	"level-1",
	World_generateLevel1,
	"level-2",
	World_generateLevel2,
	"level-3",
	World_generateLevel3,
	"first-scaling-level-1",
	World_generateLevel4,
	"first-scaling-level-2",
	World_generateLevel5,
	"first-scaling-level-3",
	World_generateLevel6,
	"first-scaling-level-4",
	World_generateLevel7,
	"make-it-bigger-1",
	World_generateLevel8,
	"make-it-bigger-2",
	World_generateLevel9,
	"cooler-scaling-level-1",
	World_generateLevel10,
	"cooler-scaling-level-2",
	World_generateLevel11,
	"cooler-scaling-level-3",
	World_generateLevel12,
	"cooler-scaling-level-4",
	World_generateLevel13,
	"cooler-scaling-level-5",
	World_generateLevel14,
};

#endif