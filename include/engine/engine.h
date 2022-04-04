#ifndef ENGINE_H_
#define ENGINE_H_

#include "stdlib.h"
#include "stdbool.h"
#include "engine/geometry.h"

//#define COLOR_BUFFER_SIZE 1920

/*
enum Engine_ColorEnum{
	COLOR_WHITE,
	COLOR_BLACK,
	COLOR_GREY,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	ENGINE_COLORS_LENGTH,
};
*/

enum Engine_KeyIdentifiers{

	ENGINE_KEY_0,
	ENGINE_KEY_1,
	ENGINE_KEY_2,
	ENGINE_KEY_3,
	ENGINE_KEY_4,
	ENGINE_KEY_5,
	ENGINE_KEY_6,
	ENGINE_KEY_7,
	ENGINE_KEY_8,
	ENGINE_KEY_9,

	ENGINE_KEY_A,
	ENGINE_KEY_B,
	ENGINE_KEY_C,
	ENGINE_KEY_D,
	ENGINE_KEY_E,
	ENGINE_KEY_F,
	ENGINE_KEY_G,
	ENGINE_KEY_H,
	ENGINE_KEY_I,
	ENGINE_KEY_J,
	ENGINE_KEY_K,
	ENGINE_KEY_L,
	ENGINE_KEY_M,
	ENGINE_KEY_N,
	ENGINE_KEY_O,
	ENGINE_KEY_P,
	ENGINE_KEY_Q,
	ENGINE_KEY_R,
	ENGINE_KEY_S,
	ENGINE_KEY_T,
	ENGINE_KEY_U,
	ENGINE_KEY_V,
	ENGINE_KEY_W,
	ENGINE_KEY_X,
	ENGINE_KEY_Y,
	ENGINE_KEY_Z,

	ENGINE_KEY_UP,
	ENGINE_KEY_DOWN,
	ENGINE_KEY_LEFT,
	ENGINE_KEY_RIGHT,

	ENGINE_KEY_SPACE,
	ENGINE_KEY_ESCAPE,
	ENGINE_KEY_ENTER,

	ENGINE_KEYS_LENGTH,

};

static char *Engine_keyNames[] = {

	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",

	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",

	"UP",
	"DOWN",
	"LEFT",
	"RIGHT",

	"SPACE",
	"ESCAPE",
	"ENTER",

};

enum Engine_ControllerKeyIdentifiers{

	ENGINE_CONTROLLER_BUTTON_Y,
	ENGINE_CONTROLLER_BUTTON_A,
	ENGINE_CONTROLLER_BUTTON_X,
	ENGINE_CONTROLLER_BUTTON_B,

	ENGINE_CONTROLLER_BUTTON_MIDDLE_LEFT,
	ENGINE_CONTROLLER_BUTTON_MIDDLE_RIGHT,

	ENGINE_CONTROLLER_BUTTON_LEFT_BUTTON,
	ENGINE_CONTROLLER_BUTTON_RIGHT_BUTTON,

	ENGINE_CONTROLLER_REAL_BUTTONS_LENGTH,

	ENGINE_CONTROLLER_BUTTON_UP,
	ENGINE_CONTROLLER_BUTTON_DOWN,
	ENGINE_CONTROLLER_BUTTON_LEFT,
	ENGINE_CONTROLLER_BUTTON_RIGHT,

	ENGINE_CONTROLLER_BUTTONS_LENGTH,

};

typedef struct Engine_Pixel{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}Engine_Pixel;

typedef struct Engine_Key{
	unsigned int OSIdentifier;
	char upperCaseString;
	char lowerCaseString;
	bool down;
	bool downed;
	bool upped;
}Engine_Key;

typedef struct Engine_Controller{
	Engine_Key buttons[ENGINE_CONTROLLER_BUTTONS_LENGTH];
	Vec2f leftStick;
	Vec2f lastLeftStick;
	Vec2f rightStick;
	Vec2f lastRightStick;
	float leftTrigger;
	float lastLeftTrigger;
	float rightTrigger;
	float lastRightTrigger;
}Engine_Controller;

/*
static const Engine_Pixel ENGINE_COLORS[ENGINE_COLORS_LENGTH] = {
	255, 255, 255,
	0, 0, 0,
	127, 127, 127,
	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
};
*/

//GLOBAL VARIABLE DECLARTIONS
extern Engine_Key ENGINE_KEYS[ENGINE_KEYS_LENGTH];

extern Engine_Controller Engine_controller;

static float ENGINE_CONTROLLER_DEAD_ZONE = 0.3;
static float ENGINE_CONTROLLER_ACTIVATION_ZONE = 0.7;
//extern Engine_Key Engine_ControllerKeys[ENGINE_CONTROLLER_KEYS_LENGTH];
//extern Engine_Pixel colorBuffers[ENGINE_COLORS_LENGTH][COLOR_BUFFER_SIZE];

//extern int screenWidth;
//extern int screenHeight;

//extern Engine_Pixel *screenPixels;

//extern int windowWidth;
//extern int windowHeight;

extern int clientWidth;
extern int clientHeight;
extern bool Engine_isFullscreen;

extern int Engine_elapsedFrames;

//ENGINE FUNCTIONS

void Engine_start();

void Engine_update(float);

void Engine_draw();

void Engine_finnish();

void Engine_quit();

//WINDOW FUNCTIONS

void Engine_setWindowTitle(char *);

void Engine_setWindowSize(int, int);

void Engine_centerWindow();

void Engine_toggleFullscreen();

/*
//DRAWING FUNCTIONS

unsigned int Engine_getScreenPixelIndex(int, int);

//void Engine_fillRect(int, int, int, int, enum Engine_ColorEnum);

//void Engine_drawLine(Vec2f, Vec2f, Engine_Pixel);

void Engine_drawTriangle(Vec2f *, Engine_Pixel);

void Engine_fillTriangle(Vec2f *, Engine_Pixel);
*/

#endif
