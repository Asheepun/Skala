#ifndef LEVELS_H_
#define LEVELS_H_

#include "game.h"

typedef struct Level{
	char *name;
	char *screenName;
	void (*generate)(World *);
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
void World_generateLevel29(World *);
void World_generateLevel30(World *);
void World_generateLevel31(World *);
void World_generateLevel32(World *);
void World_generateLevel33(World *);
void World_generateLevel34(World *);
void World_generateLevel35(World *);
void World_generateLevel36(World *);
void World_generateLevel37(World *);
void World_generateLevel38(World *);
void World_generateLevel39(World *);
void World_generateLevel40(World *);
void World_generateLevel41(World *);
void World_generateLevel42(World *);
void World_generateLevel43(World *);
void World_generateLevel44(World *);
void World_generateLevel45(World *);
void World_generateLevel46(World *);
void World_generateLevel47(World *);
void World_generateLevel48(World *);
void World_generateLevel49(World *);
void World_generateLevel50(World *);
void World_generateLevel51(World *);
void World_generateLevel52(World *);
void World_generateLevel53(World *);
void World_generateLevel54(World *);
void World_generateLevel55(World *);
void World_generateLevel56(World *);
void World_generateLevel57(World *);
void World_generateLevel58(World *);
void World_generateLevel59(World *);
void World_generateLevel60(World *);
void World_generateLevel61(World *);
void World_generateLevel62(World *);
void World_generateLevel63(World *);
void World_generateLevel64(World *);
void World_generateLevel65(World *);
void World_generateLevel66(World *);
void World_generateLevel67(World *);
void World_generateLevel68(World *);
void World_generateLevel69(World *);
void World_generateLevel70(World *);
void World_generateLevel71(World *);
void World_generateLevel72(World *);
void World_generateLevel73(World *);
void World_generateLevel74(World *);
void World_generateLevel75(World *);
void World_generateLevel76(World *);
void World_generateLevel77(World *);
void World_generateLevel78(World *);
void World_generateLevel79(World *);
void World_generateLevel80(World *);
void World_generateLevel81(World *);
void World_generateLevel82(World *);
void World_generateLevel83(World *);
void World_generateLevel84(World *);
void World_generateLevel85(World *);
void World_generateLevel86(World *);
void World_generateLevel87(World *);
void World_generateLevel88(World *);
void World_generateLevel89(World *);

static const size_t LEVELS_LENGTH = 89;

static Level levels[255] = {
	"bug-testing-level",
	"bug-testing-level",
	World_generateLevel1,
	"level-1",
	"Star",
	World_generateLevel2,
	"level-2",
	"Steps",
	World_generateLevel3,
	"level-3",
	"Pit",
	World_generateLevel4,
	"first-scaling-level-1",
	"Gap",
	World_generateLevel5,
	"first-scaling-level-2",
	"first-scaling-level-2",
	World_generateLevel6,
	"first-scaling-level-3",
	"Green Ledge",
	World_generateLevel7,
	"first-scaling-level-4",
	"Green Star",
	World_generateLevel8,
	"make-it-bigger-1",
	"Platform",
	World_generateLevel9,
	"make-it-bigger-2",
	"Bridge",
	World_generateLevel10,
	"point-cage",
	"Filter",
	World_generateLevel11,
	"point-cage-2",
	"Filter 2",
	World_generateLevel12,
	"point-cage-3",
	"Filter 3",
	World_generateLevel13,
	"slow-fall-squeeze",
	"Dive",
	World_generateLevel14,
	"high-jump-1",
	"Doorstep",
	World_generateLevel15,
	"high-jump-2",
	"Cliff Tunnel",
	World_generateLevel16,
	"high-jump-3",
	"Cliff Tunnel 2",
	World_generateLevel17,
	"cooler-scaling-level-1",
	"Green Pair",
	World_generateLevel18,
	"cooler-scaling-level-2",
	"Mousehole",
	World_generateLevel19,
	"cooler-scaling-level-3",
	"Hedge",
	World_generateLevel20,
	"cooler-scaling-level-4",
	"Green suit",
	World_generateLevel21,
	"cooler-scaling-level-5",
	"Green Couple",
	World_generateLevel22,
	"door-key-level-1",
	"Door",
	World_generateLevel23,
	"door-key-level-2",
	"Shelf",
	World_generateLevel24,
	"door-key-level-3",
	"door-key-level-3",
	World_generateLevel25,
	"key-in-box",
	"Box",
	World_generateLevel26,
	"",
	"",
	World_generateLevel27,
	"get-key-up-1",
	"Key Hole",
	World_generateLevel28,
	"get-key-up-2",
	"Key Hole 2",
	World_generateLevel29,
	"floor-is-door",
	"Trapdoor",
	World_generateLevel30,
	"push-key-with-point",
	"Cell",
	World_generateLevel31,
	"throw-key",
	"throw-key",
	World_generateLevel32,
	"maybe-key-should-fly",
	"Locker",
	World_generateLevel33,
	"flying-key-1",
	"Locker",
	World_generateLevel34,
	"flying-key-2-trickshot-edition",
	"Locker 3",
	World_generateLevel35,
	"door-key-level-with-key",
	"door-key-level-with-key",
	World_generateLevel36,
	"all-from-top-1",
	"Purple Ledge",
	World_generateLevel37,
	"all-from-top-2",
	"Purple Star",
	World_generateLevel38,
	"all-from-top-3",
	"Cancellation",
	World_generateLevel39,
	"point-pikaboo",
	"Faith",
	World_generateLevel40,
	"get-under-cup",
	"Cup",
	World_generateLevel41,
	"key-obstacle-course",
	"Opening",
	World_generateLevel42,
	"key-in-cage-all-from-top",
	"Lock",
	World_generateLevel43,
	"scale-field-1",
	"Cold",
	World_generateLevel44,
	"scale-field-2",
	"Warm",
	World_generateLevel45,
	"scale-field-3",
	"Spots",
	World_generateLevel46,
	"get-over-the-field",
	"Swamp",
	World_generateLevel47,
	"layers-of-fields",
	"Sea",
	World_generateLevel48,
	"player-position-1",
	"Coordination",
	World_generateLevel49,
	"player-position-2",
	"Mirror",
	World_generateLevel50,
	"player-position-3",
	"Acceleration",
	World_generateLevel51,
	"slide-slide-slide",
	"slide-slide-slide",
	World_generateLevel52,
	"grow-through-jumping",
	"Magic Bean",
	World_generateLevel53,
	"player-pos-key",
	"player-pos-key",
	World_generateLevel54,
	"airport-control",
	"Tunnel",
	World_generateLevel55,
	"player-position-jumping-key-1",
	"Puppet",
	World_generateLevel56,
	"player-position-jumping-key-2",
	"Puppet 2",
	World_generateLevel57,
	"player-position-jumping-key-3",
	"Puppet 3",
	World_generateLevel58,
	"point-field-cage",
	"Tangible",
	World_generateLevel59,
	"no-legs",
	"Depart",
	World_generateLevel60,
	"no-legs-2",
	"No hurdle",
	World_generateLevel61,
	"no-legs-3",
	"No dead end",
	World_generateLevel62,
	"no-legs-4",
	"No gate",
	World_generateLevel63,
	"no-legs-scalable-point",
	"Lost",
	World_generateLevel64,
	"no-legs-scalable-point-first",
	"Offset",
	World_generateLevel65,
	"no-legs-scalable-point-scale-field",
	"Offsetter",
	World_generateLevel66,
	"no-legs-scalable-point-scale-field-2",
	"Lost",
	World_generateLevel67,
	"no-legs-scalable-point-2",
	"Island",
	World_generateLevel68,
	"no-legs-key-block",
	"Pick",
	World_generateLevel69,
	"no-legs-point-hole",
	"Hurdle",
	World_generateLevel70,
	"no-legs-scale-field-key",
	"Mold",
	World_generateLevel71,
	"no-legs-drag-key",
	"Force",
	World_generateLevel72,
	"no-legs-key-first",
	"Key and lock",
	World_generateLevel73,
	"scale-position-block",
	"Rider",
	World_generateLevel74,
	"scale-position-block-2",
	"Kick flip",
	World_generateLevel75,
	"two-scale-fields",
	"Boost",
	World_generateLevel76,
	"scale-position-block-3",
	"block",
	World_generateLevel77,
	"scale-position-block-4",
	"block",
	World_generateLevel78,
	"scale-position-block-5",
	"Diver",
	World_generateLevel79,
	"scale-position-block-6",
	"Conger",
	World_generateLevel80,
	"scale-position-block-7",
	"block",
	World_generateLevel81,
	"scale-position-block-5.2",
	"Ascent",
	World_generateLevel82,
	"circle-scale-fields-escape",
	"Dime",
	World_generateLevel83,
	"climb-with-point",
	"Ladder",
	World_generateLevel84,
	"throw-key-1",
	"Locker",
	World_generateLevel85,
	"throw-key-2",
	"Locker 2",
	World_generateLevel86,
	"key-fall-through",
	"Barrier",
	World_generateLevel87,
	"no-legs-no-scale",
	"Stuck",
	World_generateLevel88,
	"no-legs-no-scale-2",
	"Stuck",
	World_generateLevel89,
};

#endif