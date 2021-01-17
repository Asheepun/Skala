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
	GAME_LAYER_FOREGROUND,
	GAME_LAYER_TEXT,
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
	float gravity;
	bool onGround;
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
	size_t spriteID;
}LevelDoor;

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

typedef struct World{

	Key keys[255];

	Action actions[16];

	//Font fonts[16];
	Array fonts;

	Array textures;
	Array shaderPrograms;

	OpenglUtils_Renderer renderer;

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

	Player player;

	Array bodyPairs;
	Array buttons;
	Array obstacles;
	Array points;
	Array doors;
	Array doorKeys;
	Array scaleFields;
	Array levelDoors;

	Array spriteLayers[NUMBER_OF_SPRITE_LAYERS];

	size_t fpsTextID;

}World;

//global variables

//static int WIDTH = 320 * 1.5;
//static int HEIGHT = 180 * 1.5;
static int WIDTH = 480;
static int HEIGHT = 270;

static int windowWidth = 480 * 3;
static int windowHeight = 270 * 3;

//static int windowWidth = 1366;
//static int windowHeight = 768;

//static int windowWidth = 802;
//static int windowHeight = 802 * 9 / 16;

//static int lastWindowWidth = 320 * 2;
//static int lastWindowHeight = 180 * 2;

static const Vec4f COLOR_BLACK 		= { 0.05, 		0.04, 		0.02, 		1 };
static const Vec4f COLOR_WHITE 		= { 0.9, 		0.85, 		0.75, 		1 };
static const Vec4f COLOR_GREY 		= { 0.5, 	0.5, 	0.5, 	1 };
static const Vec4f COLOR_BROWN 		= { 0.6, 	0.3, 	0.2, 	1 };
static const Vec4f COLOR_GREEN 		= { 0.3, 		0.90, 		0.2, 		1 };
static const Vec4f COLOR_PURPLE 	= { 0.80, 		0.1, 		0.6, 		1 };
static const Vec4f COLOR_BLUE 		= { 0, 		0, 		1, 		1 };
static const Vec4f COLOR_YELLOW 	= { 1, 		1, 		0, 		1 };

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
size_t World_addLevelDoor(World *, Vec2f, char *);

void World_removeSpriteByID(World *, size_t);
void World_removeButtonByID(World *, size_t);
void World_removePointByID(World *, size_t);
void World_removeDoorByID(World *, size_t);
void World_removeDoorKeyByID(World *, size_t);

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

#endif
