#ifndef GAME_H_
#define GAME_H_

#define SPECIAL_KEY_LEFT 81
#define SPECIAL_KEY_UP 82
#define SPECIAL_KEY_RIGHT 83
#define SPECIAL_KEY_DOWN 84

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

enum ScaleType{
	NONE,
	ALL,
	ALL_FROM_TOP,
	X_AXIS,
	Y_AXIS,
};

enum CollisionWeight{
	STATIC,
	MOVABLE,
};

enum SpriteColor{
	SPRITE_COLOR_BLACK,
	SPRITE_COLOR_BLUE,
	SPRITE_COLOR_BROWN,
	SPRITE_COLOR_GREY,
	SPRITE_COLOR_GREEN,
	SPRITE_COLOR_PURPLE,
	SPRITE_COLOR_RED,
	SPRITE_COLOR_WHITE,
	SPRITE_COLOR_YELLOW,
};

//structs

typedef struct Body{
	Vec2f pos;
	Vec2f size;
	enum ScaleType scaleType;
	enum CollisionWeight collisionWeight;
}Body;

typedef struct Physics{
	Vec2f velocity;
	Vec2f acceleration;
}Physics;

typedef struct Sprite{
	Body body;
	//Vec4f color;
	enum SpriteColor color;
	char *texture;
	float alpha;
	bool active;
}Sprite;

typedef struct TextSprite{
	EntityHeader entityHeader;
	Vec2f pos;
	Vec4f color;
	Texture texture;
	float alpha;
	unsigned int font;
	char text[32];
	//String text;
	//char *text;
}TextSprite;

typedef struct Button{
	EntityHeader entityHeader;
	size_t spriteIndex;
	size_t textSpriteID;
	enum ButtonType buttonType;
}Button;

typedef struct BodyPair{
	EntityHeader entityHeader;
	Body body;
	Body lastBody;
	Body originBody;
	Array bodies;
	Vec2f scaleForce;
	Vec2f scale;
	Vec2f lastScale;
	Vec2f origin;
	enum ScaleType originScaleType;
}BodyPair;

typedef struct Obstacle{
	EntityHeader entityHeader;
	Body originBody;
	Body body;
	Physics physics;
	size_t bodyPairIndex;
	size_t bodyPairID;
	size_t spriteIndex;
}Obstacle;

typedef struct Player{
	EntityHeader entityHeader;
	Body originBody;
	Body body;
	Physics physics;
	Vec2f resistance;
	size_t bodyPairIndex;
	size_t bodyPairID;
	size_t spriteIndex;
	float runAcceleration;
	float jumpSpeed;
	float gravity;
	bool onGround;
}Player;

typedef struct Point{
	EntityHeader entityHeader;
	Body originBody;
	Body body;
	Physics physics;
	size_t bodyPairIndex;
	size_t bodyPairID;
	size_t spriteIndex;
}Point;

typedef struct ScaleField{
	EntityHeader entityHeader;
	Body body;
	enum ScaleType scaleType;
	size_t spriteIndex;
}ScaleField;

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

	Font fonts[16];

	Array textures;

	Renderer renderer;

	bool quit;

	void (*currentState)(struct World *w);

	size_t currentLevel;

	Vec2f scale;
	Vec2f lastScale;
	Vec2f deltaScale;
	Vec2f origin;

	bool scaling;
	float scaleSpeed;

	Player player;

	Array buttons;
	Array points;
	Array obstacles;
	Array scaleFields;
	Array bodyPairs;
	Array textSprites;

	Sprite sprites[255];
	size_t spritesLength;
	size_t spritesGaps;

	size_t fpsTextID;

	float fadeTransitionAlpha;
	int fadeTransitionCounter;
	size_t currentFadeTransitionID;

}World;

//global variables

static int WIDTH = 320;
static int HEIGHT = 180;

static int windowWidth = 320 * 4;
static int windowHeight = 180 * 4;

//static int lastWindowWidth = 320 * 2;
//static int lastWindowHeight = 180 * 2;

static Vec4f COLOR_BLACK = { 0, 0, 0, 1 };
static Vec4f COLOR_WHITE = { 1, 1, 1, 1 };
static Vec4f COLOR_GREY = { 0.5, 0.5, 0.5, 1 };
static Vec4f COLOR_BROWN = { 0.6, 0.3, 0.2, 1 };
static Vec4f COLOR_GREEN = { 0, 1, 0, 1 };
static Vec4f COLOR_YELLOW = { 1, 1, 0, 1 };

static Vec4f SPRITE_COLORS[] = {
	0, 0, 0, 1, //black
	0, 0, 1, 1, //blue
	0.6, 0.3, 0.2, 1,  //brown
	0.5, 0.5, 0.5, 1, //grey
	0, 1, 0, 1, //green
	1, 0, 1, 1, //purple
	1, 0, 0, 1, //red
	1, 1, 1, 1, //white
	1, 1, 0, 1, //yellow
};

static enum SpriteColor SCALE_TYPE_COLORS[] = {
	SPRITE_COLOR_GREEN, //non scalable
	SPRITE_COLOR_WHITE, //scalable all
	SPRITE_COLOR_PURPLE, //scalable origin top all
	//SPRITE_COLOR_RED,
	//SPRITE_COLOR_BLUE,
	/*
	0, 1, 0, 1, //green
	1, 1, 1, 1, //white
	1, 0, 1, 1, //purple
	1, 0, 0, 1, //red
	0, 0, 1, 1, //blue
	*/
};

static int FADE_TRANSITION_TIME = 60;

//functions

/*
//FILE: utils.c

void Array_init(Array *, unsigned int);

void *Array_addItem(Array *);

void *Array_getItemPointerByIndex(Array *, unsigned int);

void *Array_getItemPointerByID(Array *, size_t);

unsigned int Array_getItemIndexByID(Array *, size_t);

void Array_removeItemByIndex(Array *, unsigned int);

void Array_removeItemByID(Array *, size_t);
*/

//FILE: world.c

void World_init(World *);

void World_restore(World *);

size_t World_fadeTransition(World *);

Vec2f World_getOriginFromScaleType(World *w, enum ScaleType);

Vec2f World_getScaleFromScaleType(World *w, enum ScaleType);

Vec2f World_getLastScaleFromScaleType(World *w, enum ScaleType);

//Obstacle *World_Body_checkBodyToObstaclesCol(World *, Body *);

//void World_EntityHeader_init(World *, EntityHeader *);

void World_initPlayer(World *, Vec2f, enum ScaleType);

size_t World_addSprite(World *, Vec2f, Vec2f, enum SpriteColor, char *, float);
size_t World_addTextSprite(World *, Vec2f, char *, unsigned int, Vec4f);
size_t World_addButton(World *w, Vec2f, Vec2f, char *);
size_t World_addObstacle(World *, Vec2f, Vec2f, enum ScaleType);
size_t World_addBodyPair(World *, Body);
size_t World_addPoint(World *, Vec2f, enum ScaleType);
size_t World_addScaleField(World *, Vec2f, Vec2f, enum ScaleType);

//void World_deinitSpriteByID(World *, size_t);
//void World_deinitTextSpriteByID(World *w, size_t);

void World_removeButtonByID(World *, size_t);
void World_removePointByID(World *, size_t);
//void World_deinitButtonByID(World *, size_t);

//void World_removeBodyPair(World *, size_t);
//void World_deinitBodyPairByID(World *, size_t);

BodyPair *World_getBodyPairByID(World *, size_t);
TextSprite *World_getTextSpriteByID(World *, size_t);

void World_TextSprite_updateText(World *, TextSprite *, char *);

//unsigned int World_getBodyPairIndexByID(World *, size_t);

//void World_removeObstacle(World *, size_t);
//void World_deinitObstacleByID(World *, size_t);

//void World_clearObstacles(World *);

//void World_deinitPointByID(World *, size_t);

//void World_clearPoints(World *);

//void World_deinitPlayer(World *);
void Action_init(Action *);

void Action_addBinding(Action *, int);

Body BodyPair_getDeltaBody(BodyPair);

bool checkBodyPairToBodyPairCollision(BodyPair, BodyPair);

//FILE: components.c

void Body_init(Body *, Vec2f, Vec2f, enum ScaleType, int);

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

//FILE: levelSelectState.c

void World_initLevelSelect(World *);

void World_levelSelectState(World *);

void unlockNearbyLevels();

void setupLevelGrid();

//FILE: levelState.c

void World_initLevelState(World *);

void World_levelState(World *);

//FILE: menuState.c

void World_initMenuState(World *);

void World_menuState(World *);

//FILE: 

#endif
