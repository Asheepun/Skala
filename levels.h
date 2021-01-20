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
World_generateLevel15(World *);
World_generateLevel16(World *);
World_generateLevel17(World *);
World_generateLevel18(World *);
World_generateLevel19(World *);
World_generateLevel20(World *);
World_generateLevel21(World *);
World_generateLevel22(World *);
World_generateLevel23(World *);
World_generateLevel24(World *);
World_generateLevel25(World *);
World_generateLevel26(World *);
World_generateLevel27(World *);
World_generateLevel28(World *);
World_generateLevel29(World *);
World_generateLevel30(World *);
World_generateLevel31(World *);
World_generateLevel32(World *);
World_generateLevel33(World *);
World_generateLevel34(World *);
World_generateLevel35(World *);

static const size_t LEVELS_LENGTH = 35;

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
	"point-cage",
	World_generateLevel10,
	"high-jump-1",
	World_generateLevel11,
	"high-jump-2",
	World_generateLevel12,
	"cooler-scaling-level-1",
	World_generateLevel13,
	"cooler-scaling-level-2",
	World_generateLevel14,
	"cooler-scaling-level-3",
	World_generateLevel15,
	"cooler-scaling-level-4",
	World_generateLevel16,
	"cooler-scaling-level-5",
	World_generateLevel17,
	"door-key-level-1",
	World_generateLevel18,
	"door-key-level-2",
	World_generateLevel19,
	"",
	World_generateLevel20,
	"door-key-level-3",
	World_generateLevel21,
	"	//World_addDoorKey(world_p, getVec2f(90, 20), ALL);(20, HEIGHT - 60), NONE);",
	World_generateLevel22,
	"get-key-up-1",
	World_generateLevel23,
	"get-key-up-2",
	World_generateLevel24,
	"floor-is-door",
	World_generateLevel25,
	"push-key-with-point",
	World_generateLevel26,
	"maybe-key-should-fly",
	World_generateLevel27,
	"flying-key-1",
	World_generateLevel28,
	"flying-key-2-trickshot-edition",
	World_generateLevel29,
	"door-key-level-with-key",
	World_generateLevel30,
	"all-from-top-1",
	World_generateLevel31,
	"all-from-top-2",
	World_generateLevel32,
	"all-from-top-3",
	World_generateLevel33,
	"point-pikaboo",
	World_generateLevel34,
	"get-under-cup",
	World_generateLevel35,
};

#endif