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
World_generateLevel36(World *);
World_generateLevel37(World *);
World_generateLevel38(World *);
World_generateLevel39(World *);
World_generateLevel40(World *);
World_generateLevel41(World *);
World_generateLevel42(World *);
World_generateLevel43(World *);
World_generateLevel44(World *);
World_generateLevel45(World *);
World_generateLevel46(World *);
World_generateLevel47(World *);
World_generateLevel48(World *);
World_generateLevel49(World *);
World_generateLevel50(World *);
World_generateLevel51(World *);
World_generateLevel52(World *);
World_generateLevel53(World *);
World_generateLevel54(World *);
World_generateLevel55(World *);
World_generateLevel56(World *);
World_generateLevel57(World *);
World_generateLevel58(World *);

static const size_t LEVELS_LENGTH = 58;

static Level levels[255] = {
	"bug-testing-level",
	World_generateLevel1,
	"level-1",
	World_generateLevel2,
	"level-2",
	World_generateLevel3,
	"level-3",
	World_generateLevel4,
	"first-scaling-level-1",
	World_generateLevel5,
	"first-scaling-level-2",
	World_generateLevel6,
	"first-scaling-level-3",
	World_generateLevel7,
	"first-scaling-level-4",
	World_generateLevel8,
	"make-it-bigger-1",
	World_generateLevel9,
	"make-it-bigger-2",
	World_generateLevel10,
	"point-cage",
	World_generateLevel11,
	"point-cage-2",
	World_generateLevel12,
	"point-cage-3",
	World_generateLevel13,
	"slow-fall-squeeze",
	World_generateLevel14,
	"high-jump-1",
	World_generateLevel15,
	"high-jump-2",
	World_generateLevel16,
	"high-jump-3",
	World_generateLevel17,
	"cooler-scaling-level-1",
	World_generateLevel18,
	"cooler-scaling-level-2",
	World_generateLevel19,
	"cooler-scaling-level-3",
	World_generateLevel20,
	"cooler-scaling-level-4",
	World_generateLevel21,
	"cooler-scaling-level-5",
	World_generateLevel22,
	"door-key-level-1",
	World_generateLevel23,
	"door-key-level-2",
	World_generateLevel24,
	"door-key-level-3",
	World_generateLevel25,
	"key-in-box",
	World_generateLevel26,
	"	//World_addDoorKey(world_p, getVec2f(90, 20), ALL);(20, HEIGHT - 60), NONE);",
	World_generateLevel27,
	"get-key-up-1",
	World_generateLevel28,
	"get-key-up-2",
	World_generateLevel29,
	"floor-is-door",
	World_generateLevel30,
	"push-key-with-point",
	World_generateLevel31,
	"throw-key",
	World_generateLevel32,
	"maybe-key-should-fly",
	World_generateLevel33,
	"flying-key-1",
	World_generateLevel34,
	"flying-key-2-trickshot-edition",
	World_generateLevel35,
	"door-key-level-with-key",
	World_generateLevel36,
	"all-from-top-1",
	World_generateLevel37,
	"all-from-top-2",
	World_generateLevel38,
	"all-from-top-3",
	World_generateLevel39,
	"point-pikaboo",
	World_generateLevel40,
	"get-under-cup",
	World_generateLevel41,
	"key-obstacle-course",
	World_generateLevel42,
	"key-in-cage-all-from-top",
	World_generateLevel43,
	"scale-field-1",
	World_generateLevel44,
	"scale-field-2",
	World_generateLevel45,
	"scale-field-3",
	World_generateLevel46,
	"get-over-the-field",
	World_generateLevel47,
	"layers-of-fields",
	World_generateLevel48,
	"player-position-1",
	World_generateLevel49,
	"player-position-2",
	World_generateLevel50,
	"player-position-3",
	World_generateLevel51,
	"slide-slide-slide",
	World_generateLevel52,
	"grow-through-jumping",
	World_generateLevel53,
	"player-pos-key",
	World_generateLevel54,
	"airport-control",
	World_generateLevel55,
	"player-position-jumping-key-1",
	World_generateLevel56,
	"player-position-jumping-key-2",
	World_generateLevel57,
	"player-position-jumping-key-3",
	World_generateLevel58,
};

#endif