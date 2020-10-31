#ifndef LEVELS_H_
#define LEVELS_H_

typedef struct Level{
	void (*generate)(World *);
	int x;
	int y;
}Level;

void World_generateLevel1(World *);

void World_generateLevel2(World *);

void World_generateLevel3(World *);

void World_generateLevel4(World *);

void World_generateLevel5(World *);

void World_generateLevel6(World *);

void World_generateLevel7(World *);

void World_generateLevel8(World *);

void World_generateLevel9(World *);

void World_generateLevel10(World *);

void World_generateLevel11(World *);

void World_generateLevel12(World *);

void World_generateLevel13(World *);

void World_generateLevel14(World *);

void World_generateLevel15(World *);

void World_generateLevel16(World *);

void World_generateLevel17(World *);

void World_generateLevel18(World *);

void World_generateLevel19(World *);

void World_generateLevel20(World *);

void World_generateLevel21(World *);

void World_generateLevel22(World *);

void World_generateLevel23(World *);

void World_generateLevel24(World *);

void World_generateLevel25(World *);

void World_generateLevel26(World *);

void World_generateLevel27(World *);

void World_generateLevel28(World *);

static int levelsLength = 28;

static Level levels[255] = {
	World_generateLevel1, 15, 20,
	World_generateLevel2, 15, 19,
	World_generateLevel3, 15, 18,
	World_generateLevel4, 15, 17,
	World_generateLevel5, 15, 16,
	World_generateLevel6, 15, 15,
	World_generateLevel7, 14, 15,
	World_generateLevel8, 13, 15,
	World_generateLevel9, 15, 14,
	World_generateLevel10, 15, 13,
	World_generateLevel11, 16, 11,
	World_generateLevel12, 15, 12,
	World_generateLevel13, 15, 11,
	World_generateLevel14, 15, 10,
	World_generateLevel15, 15, 9,
	World_generateLevel16, 15, 8,
	World_generateLevel17, 16, 8,
	World_generateLevel18, 17, 8,
	World_generateLevel19, 18, 8,
	World_generateLevel20, 15, 7,
	World_generateLevel21, 15, 6,
	World_generateLevel22, 15, 5,
	World_generateLevel23, 15, 4,
	World_generateLevel24, 16, 5,
	World_generateLevel25, 14, 5,
	World_generateLevel26, 13, 5,
	World_generateLevel27, 12, 5,
	World_generateLevel28, 11, 5,
};

#endif