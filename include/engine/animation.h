#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "engine/strings.h"
#include "engine/geometry.h"
#include "engine/array.h"

typedef struct Animation_Frame{
	Vec2f textureCoordOffset;
	int duration;
}Animation_Frame;

typedef struct Animation_State{
	char name[STRING_SIZE];
	Array frames;
}Animation_State;

typedef struct Animation{
	int currentFrame;
	int currentFrameDurationCounter;
	char currentState[STRING_SIZE];
	Array states;
}Animation;

//INIT FUNCTIONS

void Animation_init(Animation *, char *);

//OTHER FUNCTIONS

void Animation_setState(Animation *, char *);

void Animation_updateFrame(Animation *);

Animation_Frame *Animation_getCurrentFramePointer(Animation *);

#endif
