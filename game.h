#ifndef GAME_H_
#define GAME_H_

#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "openglUtils.h"

//definitions

#define NUMBER_OF_SPRITE_LAYERS 20

//enums

enum Actions{
	UP_ACTION,
	DOWN_ACTION,
	LEFT_ACTION,
	RIGHT_ACTION,
	JUMP_ACTION,
	SCALE_ACTION,
	DO_ACTION,
	BACK_ACTION,
	MENU_ACTION,
	RESTART_ACTION,
};

enum ButtonType{
	SPRITE_BUTTON,
	TEXT_BUTTON,
};

enum EntityType{
	PLAYER,
	OBSTACLE,
	POINT,
	DOOR_KEY,
	DOOR,
	SCALE_FIELD,
};

enum ScaleType{
	NONE,
	ALL,
	ALL_FROM_TOP,
	ALL_SWITCH_X_Y,
	//X_AXIS,
	//Y_AXIS,
};

enum CollisionWeight{
	STATIC,
	MOVABLE,
};

enum Facing{
	LEFT,
	RIGHT,
};

enum SpriteType{
	REGULAR_SPRITE,
	TEXT_SPRITE,
};

enum SpriteLayer{
	GAME_LAYER_BACKGROUND,
	GAME_LAYER_WALLS,
	GAME_LAYER_FURNITURE,
	GAME_LAYER_FOREGROUND,
	GAME_LAYER_OBSTACLES,
	GAME_LAYER_SHADOWS,
	GAME_LAYER_TEXT,
	GAME_LAYER_PARTICLES,
	MENU_LAYER_BACKGROUND,
	MENU_LAYER_FOREGROUND,
	MENU_LAYER_TEXT,
};

enum WorldState{
	LEVEL_STATE,
	LEVEL_SELECT_STATE,
	LEVEL_HUB_STATE,
	MENU_STATE,
};

enum LevelHubRoom{
	FIRST_SCALE_ROOM,
	DOOR_KEY_ROOM,
	ALL_FROM_TOP_ROOM,
	SCALE_FIELD_ROOM,
	PLAYER_POSITION_ROOM,
};

//structs

typedef struct Body{
	Vec2f pos;
	Vec2f size;
}Body;

typedef struct Physics{
	Vec2f velocity;
	Vec2f acceleration;
	Vec2f resistance;
	float gravity;
	bool onGround;
}Physics;

typedef struct Sprite{

	//common
	EntityHeader entityHeader;
	enum SpriteType type;
	Vec4f color;
	float alpha;
	enum Facing facing;
	Vec2f borderSize;

	//regular sprite
	Body body;
	char *texture;

	//text sprite
	Vec2f pos;
	//unsigned int font;
	char *fontName;
	char text[32];

}Sprite;

typedef struct Button{
	EntityHeader entityHeader;
	size_t spriteID;
	enum ButtonType buttonType;
}Button;

typedef struct BodyPair{
	EntityHeader entityHeader;

	Body body;
	Body lastBody;
	Body originBody;
	Physics physics;

	Vec2f scaleForce;
	Vec2f scale;
	Vec2f lastScale;
	Vec2f origin;

	enum ScaleType scaleType;
	enum ScaleType originScaleType;
	enum CollisionWeight collisionWeight;
	enum EntityType entityType;
}BodyPair;

typedef struct Obstacle{
	EntityHeader entityHeader;
	Physics physics;
	size_t bodyPairID;
	size_t spriteID;
}Obstacle;

typedef struct Player{
	EntityHeader entityHeader;
	Physics physics;
	Vec2f resistance;
	size_t bodyPairID;
	size_t spriteID;
	float runAcceleration;
	float jumpSpeed;
	bool holdingKey;
	enum Facing facing;
}Player;

typedef struct Point{
	EntityHeader entityHeader;
	Body originBody;
	Body body;
	Physics physics;
	size_t bodyPairID;
	size_t spriteID;
}Point;

typedef struct Door{
	EntityHeader entityHeader;
	size_t bodyPairIndex;
	size_t bodyPairID;
	size_t spriteID;
}Door;

typedef struct DoorKey{
	EntityHeader entityHeader;
	Physics physics;
	size_t bodyPairID;
	size_t spriteID;
	enum Facing facing;
}DoorKey;

typedef struct ScaleField{
	EntityHeader entityHeader;
	Body body;
	enum ScaleType scaleType;
	size_t bodyPairID;
	size_t spriteID;
}ScaleField;

typedef struct LevelDoor{
	EntityHeader entityHeader;
	Body body;
	char *levelName;
	enum LevelHubRoom levelHubRoom;
	size_t spriteID;
	size_t hoverTextSpriteID;
}LevelDoor;

typedef struct Particle{
	EntityHeader entityHeader;
	Body body;
	Physics physics;
	bool targeting;
	int activationCounter;
	Vec4f targetColor;
	size_t spriteID;
}Particle;

typedef struct Key{
	bool down;
	bool downed;
	bool downedNoRepeat;
	int downCounter;
}Key;

typedef struct Action{
	bool down;
	bool downed;
	bool downedNoRepeat;
	int bindings[16];
	int bindingsLength;
}Action;

typedef struct SaveData{
	Vec2f playerPos;
	Array flags;
	Array completedLevels;
	Array levelsWithDoorKey;
	Array doorKeys;
	Array doors;
}SaveData;

typedef struct World{

	Key keys[255];

	Action actions[16];

	SaveData saveData;
	Array roomLevels[5];
	bool addedRoomLevels;

	//Font fonts[16];
	Array fonts;

	Array textures;
	Array shaderPrograms;

	OpenglUtils_Renderer renderer;
	Vec2f cameraPos;
	Vec2f cameraTarget;

	float levelWidth;
	float levelHeight;

	bool quit;

	enum WorldState currentState;
	enum WorldState nextStateAfterTransition;
	enum WorldState stateBeforeOpeningMenu;
	int fadeTransitionCounter;
	bool initCurrentState;

	//size_t currentLevel;
	char *currentLevel;

	Vec2f scale;
	Vec2f lastScale;
	Vec2f deltaScale;
	Vec2f origin;

	bool scaling;
	float scaleSpeed;
	bool scalingByPlayerPosition;

	Player player;

	Array bodyPairs;
	Array buttons;
	Array obstacles;
	Array points;
	Array doors;
	Array doorKeys;
	Array scaleFields;
	Array levelDoors;
	Array particles;

	Array spriteLayers[NUMBER_OF_SPRITE_LAYERS];

	size_t fpsTextID;

	bool playerHasLanded;

	unsigned int starBackgroundSpriteID;

}World;

//global variables

//static int WIDTH = 320 * 1.5;
//static int HEIGHT = 180 * 1.5;
static const int WIDTH = 480;
static const int HEIGHT = 270;

//static int windowWidth = WIDTH * 3;
//static int windowHeight = HEIGHT * 3;

static int windowWidth = WIDTH * 2.5;
static int windowHeight = HEIGHT * 2.5;

//static int windowWidth = 1366;
//static int windowHeight = 768;

//static int windowWidth = 802;
//static int windowHeight = 802 * 9 / 16;

//static int lastWindowWidth = 320 * 2;
//static int lastWindowHeight = 180 * 2;

static const Vec4f COLOR_BLACK 				= { 0.00, 		0.00, 		0.00, 		1 };
static const Vec4f COLOR_WHITE 				= { 1.00, 		1.00, 		1.00, 		1 };
static const Vec4f COLOR_GREY 				= { 0.50, 		0.50, 		0.50, 		1 };
static const Vec4f COLOR_BROWN 				= { 0.60, 		0.30, 		0.20, 		1 };
static const Vec4f COLOR_RED 				= { 1.00, 		0.00, 		0.00, 		1 };
static const Vec4f COLOR_GREEN 				= { 0.00, 		1.00, 		0.00, 		1 };
static const Vec4f COLOR_PURPLE 			= { 1.00, 		0.00, 		1.00, 		1 };
static const Vec4f COLOR_BLUE 				= { 0.00, 		0.00, 		1.00, 		1 };
static const Vec4f COLOR_YELLOW 			= { 1.00, 		1.00, 		0.00, 		1 };

static const Vec4f COLOR_GREY_BACKGROUND 	= { 0.00, 		0.00, 		0.00, 		1 };
static const Vec4f COLOR_GREEN_BACKGROUND 	= { 0.00, 		0.5, 		0.00, 		1 };
static const Vec4f COLOR_YELLOW_BACKGROUND 	= { 0.5, 		0.5, 		0.00, 		1 };
static const Vec4f COLOR_PURPLE_BACKGROUND 	= { 0.5, 		0.00, 		0.5, 		1 };

static const Vec4f COLOR_BLACK_WALL 		= { 0.05, 		0.05, 		0.05, 		1 };
static const Vec4f COLOR_RED_WALL 		= { 0.15, 		0.00, 		0.00, 		1 };
static const Vec4f COLOR_GREEN_WALL 		= { 0.03, 		0.10, 		0.00, 		1 };
static const Vec4f COLOR_BLUE_WALL 		= { 0.02, 		0.04, 		0.10, 		1 };
static const Vec4f COLOR_PURPLE_WALL 		= { 0.07, 		0.00, 		0.07, 		1 };
static const Vec4f COLOR_YELLOW_WALL 		= { 0.20, 		0.20, 		0.00, 		1 };

static const Vec4f COLOR_HOUSE 				= { 0.90, 		0.90, 		0.90, 		1 };

static const Vec4f SCALE_TYPE_COLORS[] = {
	COLOR_WHITE, 	//none scalable
	COLOR_GREEN, 	//scalable all
	COLOR_PURPLE, 	//scalable origin top all
	COLOR_BLUE, 	//scalable x y switch
};

static int FADE_TRANSITION_TIME = 60;

//functions

//FILE: world.c

void World_init(World *);

void World_restore(World *);

//size_t World_fadeTransition(World *);

Vec2f World_getOriginFromScaleType(World *w, enum ScaleType);

Vec2f World_getScaleFromScaleType(World *w, enum ScaleType);

Vec2f World_getLastScaleFromScaleType(World *w, enum ScaleType);

void World_initPlayer(World *, Vec2f, enum ScaleType);

size_t World_addSprite(World *, Vec2f, Vec2f, Vec4f, char *, float, enum SpriteLayer);
size_t World_addTextSprite(World *, Vec2f, char *, char *, Vec4f, enum SpriteLayer);
size_t World_addButton(World *w, Vec2f, Vec2f, char *, enum SpriteLayer);
size_t World_addObstacle(World *, Vec2f, Vec2f, enum ScaleType);
size_t World_addBodyPair(World *, Body, enum ScaleType, enum CollisionWeight, enum EntityType);
size_t World_addPoint(World *, Vec2f, enum ScaleType);
size_t World_addDoor(World *, Vec2f, Vec2f, enum ScaleType);
size_t World_addDoorKey(World *, Vec2f, enum ScaleType);
size_t World_addScaleField(World *, Vec2f, Vec2f, enum ScaleType);
size_t World_addLevelDoor(World *, Vec2f, char *, enum LevelHubRoom);
size_t World_addParticle(World *, Vec2f, Vec2f, char *, int, Vec4f, Vec4f);
size_t World_addShadow(World *, Vec2f, Vec2f);

void World_removeSpriteByID(World *, size_t);
void World_removeButtonByID(World *, size_t);
void World_removePointByID(World *, size_t);
void World_removeDoorByID(World *, size_t);
void World_removeDoorKeyByID(World *, size_t);
void World_removeParticleByID(World *, size_t);

Body World_TextSprite_getBody(World *, Sprite *);

BodyPair *World_getBodyPairByID(World *, size_t);
Sprite *World_getSpriteByID(World *, size_t);
Button *World_getButtonByID(World *, size_t);

void Action_init(Action *);

void Action_addBinding(Action *, int);

Body BodyPair_getDeltaBody(BodyPair);

bool checkBodyPairToBodyPairCollision(BodyPair, BodyPair);

bool checkIfBodyPairsCanCollide(BodyPair, BodyPair);

void World_fadeTransitionToState(World *, enum WorldState);

void World_switchToAndInitState(World *, enum WorldState);

void World_checkAndHandleBodyPairCollisionsX(World *, enum CollisionWeight, enum ScaleType, enum CollisionWeight, enum ScaleType);
void World_checkAndHandleBodyPairCollisionsY(World *, enum CollisionWeight, enum ScaleType, enum CollisionWeight, enum ScaleType);

Vec2f BodyPair_getPhysicsScale(BodyPair *);

//FILE: components.c

void Body_init(Body *, Vec2f, Vec2f);

Vec2f Body_getCenter(Body);

void Body_scale(Body *, Vec2f, Vec2f);

void Body_unScale(Body *, Vec2f, Vec2f);

void Body_scaleX(Body *, Vec2f, Vec2f);

void Body_scaleY(Body *, Vec2f, Vec2f);

void Body_unScaleX(Body *, Vec2f, Vec2f);

void Body_unScaleY(Body *, Vec2f, Vec2f);

bool Body_checkOub(Body);

bool checkBodyToBodyColRoundFloats(Body, Body);

bool checkBodyToBodyColCastToInt(Body, Body);

bool checkBodyToBodyCol(Body, Body);

//FILE: levelState.c

void World_initLevel(World *);

void World_levelState(World *);

//FILE: levelHub.c

void World_initLevelHub(World *);

//FILE: menuState.c

void World_initMenu(World *);

void World_menuState(World *);

//FILE saving.c

void SaveData_init(SaveData *);

void SaveData_read(SaveData *);

void SaveData_write(SaveData *);

bool SaveData_hasFlag(SaveData *, char *);

void SaveData_addFlag(SaveData *, char *);

#endif
