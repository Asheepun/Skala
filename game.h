#ifndef GAME_H_
#define GAME_H_

//#include "glad/glad.h"
//#define SDL_DISABLE_IMMINTRIN_H
//#include "SDL2/SDL.h"
//#include "openglUtils.h"
//#include "utils.h"
#include "engine/renderer2d.h"
#include "engine/array.h"
#include "engine/text.h"
#include "engine/geometry.h"

#include "stdbool.h"

//definitions

#define NUMBER_OF_SPRITE_LAYERS 20

#define NUMBER_OF_SCALES 1000
#define ORIGIN_SCALE_INDEX 900

//enums

//*temporary
enum ParticleType{
	LEVEL_COMPLETE_PARTICLE,
	FADE_IN_PARTICLE,
};
//*temporary

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
	GAME_LAYER_DOOR_KEYS,
	GAME_LAYER_BLOCKED_ENTITIES,
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
	CREDITS_STATE,
};

enum LevelHubRoom{
	FIRST_SCALE_ROOM,
	DOOR_KEY_ROOM,
	ALL_FROM_TOP_ROOM,
	SCALE_FIELD_ROOM,
	PLAYER_POSITION_ROOM,
};

enum ParticlePropertyType{
	PARTICLE_POS,
	PARTICLE_SIZE,
	PARTICLE_VELOCITY,
	PARTICLE_ACCELERATION,
	PARTICLE_COLOR,
	PARTICLE_ALPHA,
	PARTICLE_TEXTURE,
	PARTICLE_TEXT,
};

enum ParticleEventType{
	PARTICLE_SET_EVENT,
	PARTICLE_REMOVE_EVENT,
	PARTICLE_LINEAR_FADE_EVENT,
	PARTICLE_LERP_EVENT,
};

union ParticleProperty{
	Vec2f pos;
	Vec2f size;
	Vec2f velocity;
	Vec2f acceleration;
	Renderer2D_Color color;
	float alpha;
	char *texture;
	char *text;
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
	bool landed;
}Physics;

typedef struct Sprite{

	//common
	//EntityHeader entityHeader;
	Renderer2D_Color color;
	float alpha;
	Vec2f borderSize;
	enum SpriteType type;
	enum SpriteLayer currentLayer;
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
	//size_t spriteID;
	unsigned int spriteIndex;
	enum ButtonType buttonType;
}Button;

typedef struct BodyPair{
	EntityHeader entityHeader;

	Body body;
	Body lastBody;
	Body originBody;
	Physics physics;

	//Vec2f scaleForce;
	//Vec2f scale;
	//Vec2f lastScale;
	Vec2f playerPositionScale;
	Vec2f playerPositionLastScale;
	Vec2f scaleExponent;
	Vec2f lastScaleExponent;
	//Vec2f origin;
	//size_t scaleIndexX;
	//size_t scaleIndexY;
	//size_t lastScaleIndexX;
	//size_t lastScaleIndexY;

	enum ScaleType scaleType;
	enum ScaleType originScaleType;
	enum CollisionWeight collisionWeight;
	enum EntityType entityType;

	bool isStuckX;
	bool isStuckY;
	//bool isStuck;
}BodyPair;

typedef struct Obstacle{
	EntityHeader entityHeader;
	Physics physics;
	size_t bodyPairID;
	//size_t spriteID;
	unsigned int spriteIndex;
}Obstacle;

typedef struct Player{
	EntityHeader entityHeader;
	Physics physics;
	Vec2f resistance;
	size_t bodyPairID;
	//size_t spriteID;
	unsigned int spriteIndex;
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
	//size_t spriteID;
	unsigned int spriteIndex;
}Point;

typedef struct Door{
	EntityHeader entityHeader;
	size_t bodyPairIndex;
	size_t bodyPairID;
	//size_t spriteID;
	unsigned int spriteIndex;
}Door;

typedef struct DoorKey{
	EntityHeader entityHeader;
	Physics physics;
	size_t bodyPairID;
	//size_t spriteID;
	unsigned int spriteIndex;
	enum Facing facing;
}DoorKey;

typedef struct ScaleField{
	EntityHeader entityHeader;
	Body body;
	enum ScaleType scaleType;
	size_t bodyPairID;
	//size_t spriteID;
	unsigned int spriteIndex;
	int particleCounter;
}ScaleField;

typedef struct LevelDoor{
	EntityHeader entityHeader;
	Body body;
	char *levelName;
	enum LevelHubRoom levelHubRoom;
	//size_t spriteID;
	unsigned int spriteIndex;
	size_t hoverTextSpriteID;
	size_t hoverTextParticleID;
	bool hasPlayerBelow;
}LevelDoor;

typedef struct Particle{
	EntityHeader entityHeader;
	Body body;
	Physics physics;
	Array events;
	int counter;
	//size_t spriteID;
	unsigned int spriteIndex;

	//temp stuff
	Renderer2D_Color targetColor;
	bool targeting;
	int activationCounter;
	enum ParticleType type;

}Particle;

typedef struct ParticleEvent{
	enum ParticlePropertyType propertyType;
	enum ParticleEventType type;
	union ParticleProperty startValue;
	union ParticleProperty targetValue;
	int activationTime;
	int duration;
	float a;
	float b;
	float c;
}ParticleEvent;

typedef struct Key{
	bool down;
	bool downed;
	bool downedNoRepeat;
	bool upped;
	int downCounter;
}Key;

typedef struct Action{
	bool down;
	bool downed;
	bool downedNoRepeat;
	bool upped;
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
	//Font timesFont;

	Array textures;
	Array shaderPrograms;

	Renderer2D_Renderer renderer;
	//OpenglUtils_Renderer renderer;
	Vec2f cameraPos;
	Vec2f cameraTarget;
	bool snapCamera;

	float levelWidth;
	float levelHeight;

	bool quit;

	enum WorldState currentState;
	enum WorldState nextStateAfterTransition;
	enum WorldState stateBeforeOpeningMenu;
	int fadeTransitionCounter;
	bool initCurrentState;

	float endingFlashAlpha;

	//size_t currentLevel;
	char *currentLevel;

	Vec2f scaleDirection;
	//Vec2f scale;
	//Vec2f lastScale;
	//Vec2f deltaScale;
	Vec2f origin;

	//float scalesX[NUMBER_OF_SCALES];
	//float scalesY[NUMBER_OF_SCALES];

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

	IndexSafeArray spriteLayers[NUMBER_OF_SPRITE_LAYERS];

	size_t fpsTextID;

	float deltaTime;
	long time;

	bool playerHasLanded;

	size_t starBackgroundSpriteIndex;

	size_t titleTextParticleID;
	size_t movementKeysTextParticleID;
	size_t menuKeyTextParticleID;

}World;

//global variables

//static int WIDTH = 320 * 1.5;
//static int HEIGHT = 180 * 1.5;
static const int WIDTH = 480;
static const int HEIGHT = 270;

//static int windowWidth = WIDTH * 3;
//static int windowHeight = HEIGHT * 3;

//static int windowWidth = 480 * 2.5;
//static int windowHeight = 270 * 2.5;

//static int windowWidth = 1366;
//static int windowHeight = 768;

//static int windowWidth = 802;
//static int windowHeight = 802 * 9 / 16;

//static int lastWindowWidth = 320 * 2;
//static int lastWindowHeight = 180 * 2;

static const Renderer2D_Color COLOR_BLACK 				= { 0.00, 		0.00, 		0.00 };
static const Renderer2D_Color COLOR_WHITE 				= { 1.00, 		1.00, 		1.00 };
static const Renderer2D_Color COLOR_GREY 				= { 0.50, 		0.50, 		0.50 };
static const Renderer2D_Color COLOR_BROWN 				= { 0.60, 		0.30, 		0.20 };
static const Renderer2D_Color COLOR_RED 				= { 1.00, 		0.00, 		0.00 };
static const Renderer2D_Color COLOR_GREEN 				= { 0.00, 		1.00, 		0.00 };
static const Renderer2D_Color COLOR_PURPLE 				= { 1.00, 		0.00, 		1.00 };
static const Renderer2D_Color COLOR_BLUE 				= { 0.00, 		0.00, 		1.00 };
static const Renderer2D_Color COLOR_YELLOW 				= { 1.00, 		1.00, 		0.00 };

static const Renderer2D_Color COLOR_GREY_BACKGROUND 	= { 0.00, 		0.00, 		0.00 };
static const Renderer2D_Color COLOR_GREEN_BACKGROUND 	= { 0.00, 		0.5, 		0.00 };
static const Renderer2D_Color COLOR_YELLOW_BACKGROUND 	= { 0.5, 		0.5, 		0.00 };
static const Renderer2D_Color COLOR_PURPLE_BACKGROUND 	= { 0.5, 		0.00, 		0.5 };

static const Renderer2D_Color COLOR_BLACK_WALL 			= { 0.05, 		0.05, 		0.05 };
static const Renderer2D_Color COLOR_RED_WALL 			= { 0.15, 		0.00, 		0.00 };
static const Renderer2D_Color COLOR_GREEN_WALL 			= { 0.03, 		0.10, 		0.00 };
static const Renderer2D_Color COLOR_BLUE_WALL 			= { 0.02, 		0.04, 		0.10 };
static const Renderer2D_Color COLOR_PURPLE_WALL 		= { 0.07, 		0.00, 		0.07 };
static const Renderer2D_Color COLOR_YELLOW_WALL 		= { 0.20, 		0.20, 		0.00 };

static const Renderer2D_Color COLOR_HOUSE 				= { 0.90, 		0.90, 		0.90 };

static const Renderer2D_Color COLOR_DARK_GREY 			= { 0.10, 		0.10, 		0.15 };

static const Renderer2D_Color SCALE_TYPE_COLORS[] = {
	1.0, 1.0, 1.0,
	0.0, 1.0, 0.0,
	1.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	//COLOR_WHITE, 	//none scalable
	//COLOR_GREEN, 	//scalable all
	//COLOR_PURPLE, 	//scalable origin top all
	//COLOR_BLUE, 	//scalable x y switch
};

static const Renderer2D_Color SCALING_SCALE_TYPE_COLORS[] = {
	1.0, 1.0, 1.0,
	0.5, 1.0, 0.5,
	1.0, 0.5, 1.0,
	0.5, 0.5, 1.0,
	//COLOR_WHITE, 	//none scalable
	//COLOR_GREEN, 	//scalable all
	//COLOR_PURPLE, 	//scalable origin top all
	//COLOR_BLUE, 	//scalable x y switch
};

static int FADE_TRANSITION_TIME = 60;

//functions

//FILE: world.c

void World_init(World *);

void World_restore(World *);

//size_t World_fadeTransition(World *);

Vec2f World_getOriginFromScaleType(World *w, enum ScaleType);

//Vec2f World_getScaleFromScaleType(World *w, enum ScaleType);

//Vec2f World_getLastScaleFromScaleType(World *w, enum ScaleType);

void World_initPlayer(World *, Vec2f, enum ScaleType);

size_t World_addSprite(World *, Vec2f, Vec2f, Renderer2D_Color, char *, float, enum SpriteLayer);
size_t World_addTextSprite(World *, Vec2f, char *, char *, Renderer2D_Color, enum SpriteLayer);
size_t World_addButton(World *, Vec2f, Vec2f, char *, enum SpriteLayer);
size_t World_addTextButton(World *, Vec2f, char *, enum SpriteLayer);
size_t World_addObstacle(World *, Vec2f, Vec2f, enum ScaleType);
size_t World_addBodyPair(World *, Body, enum ScaleType, enum CollisionWeight, enum EntityType);
size_t World_addPoint(World *, Vec2f, enum ScaleType);
size_t World_addDoor(World *, Vec2f, Vec2f, enum ScaleType);
size_t World_addDoorKey(World *, Vec2f, enum ScaleType);
size_t World_addScaleField(World *, Vec2f, Vec2f, enum ScaleType);
size_t World_addLevelDoor(World *, Vec2f, char *, enum LevelHubRoom);
//size_t World_addParticle(World *, Vec2f, Vec2f, char *, int, Renderer2D_Color, Renderer2D_Color);
size_t World_addShadow(World *, Vec2f, Vec2f);

Particle *World_addParticle(World *, unsigned int);
size_t World_addFadeInTextParticle(World *, Vec2f, char *, char *, Renderer2D_Color, int, int);

void World_removeSpriteByIndex(World *, unsigned);
void World_removeButtonByID(World *, size_t);
void World_removePointByID(World *, size_t);
void World_removeDoorByID(World *, size_t);
void World_removeDoorKeyByID(World *, size_t);
void World_removeParticleByID(World *, size_t);

Body World_TextSprite_getBody(World *, Sprite *);

BodyPair *World_getBodyPairByID(World *, size_t);
//Sprite *World_getSpriteByID(World *, size_t);
Sprite *World_getSpriteByIndex(World *, unsigned int);
Button *World_getButtonByID(World *, size_t);
Particle *World_getParticleByID(World *, size_t);

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

void Particle_addEvent(Particle *, enum ParticleEventType, enum ParticlePropertyType, union ParticleProperty, int, int);
void Particle_addRemoveEvent(Particle *, int);

Sprite *World_Sprite_setToLayer_returnsNewPointerAndUpdatesIndex(World *, Sprite *, unsigned int *, enum SpriteLayer);

bool BodyPair_isScalable(BodyPair *);

void BodyPair_World_setBodyFromScaleX(BodyPair *, World *);
void BodyPair_World_setBodyFromScaleY(BodyPair *, World *);

float BodyPair_getScaleFromBodyX(BodyPair *);
float BodyPair_getScaleFromBodyY(BodyPair *);

Vec2f World_BodyPair_getScaleFromExponent(World *, BodyPair *);
Vec2f World_BodyPair_getLastScaleFromExponent(World *, BodyPair *);

//FILE: components.c

void Body_init(Body *, Vec2f, Vec2f);

Vec2f Body_getCenter(Body);

void Body_scale(Body *, Vec2f, Vec2f);

void Body_unScale(Body *, Vec2f, Vec2f);

void Body_scaleX(Body *, float, float);

void Body_scaleY(Body *, float, float);

void Body_unScaleX(Body *, float, float);

void Body_unScaleY(Body *, float, float);

bool Body_checkOub(Body);

bool checkBodyToBodyColRoundFloats(Body, Body);

bool checkBodyToBodyColCastToInt(Body, Body);

bool checkBodyToBodyColRoundTo2Dec(Body, Body);

bool checkBodyToBodyCol(Body, Body);

void Physics_init(Physics *);

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

//FILE: credits.c

void World_initCredits(World *);

void World_creditsState(World *);

#endif
