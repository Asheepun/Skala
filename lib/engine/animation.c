#include "engine/animation.h"
#include "engine/strings.h"
#include "engine/array.h"

#include "stdio.h"
#include "math.h"
#include "string.h"

void Animation_init(Animation *animation_p, char *initialState){

	String_set(animation_p->currentState, initialState, STRING_SIZE);
	animation_p->currentFrame = 0;
	animation_p->currentFrameDurationCounter = 0;

	Array_init(&animation_p->states, sizeof(Animation_State));

}

void Animation_free(Animation *animation_p){
	
	while(animation_p->states.length > 0){

		Animation_State *state_p = Array_getItemPointerByIndex(&animation_p->states, 0);

		Array_free(&state_p->frames);

		Array_removeItemByIndex(&animation_p->states, 0);

	}

	Array_free(&animation_p->states);

}

void Animation_clear(Animation *animation_p){
	
	while(animation_p->states.length > 0){

		Animation_State *state_p = Array_getItemPointerByIndex(&animation_p->states, 0);

		Array_free(&state_p->frames);

		Array_removeItemByIndex(&animation_p->states, 0);

	}

}

void Animation_setState(Animation *animation_p, char *newState){

	if(!(strcmp(animation_p->currentState, newState) == 0)){

		String_set(animation_p->currentState, newState, STRING_SIZE);
		animation_p->currentFrame = 0;
		animation_p->currentFrameDurationCounter = 0;
	
	}

}

void Animation_updateFrame(Animation *animation_p){

	for(int i = 0; i < animation_p->states.length; i++){

		Animation_State *state_p = Array_getItemPointerByIndex(&animation_p->states, i);

		if(strcmp(state_p->name, animation_p->currentState) == 0){

			Animation_Frame *currentFrame_p = Array_getItemPointerByIndex(&state_p->frames, animation_p->currentFrame);

			if(animation_p->currentFrameDurationCounter >= currentFrame_p->duration){

				animation_p->currentFrame++;

				if(animation_p->currentFrame >= state_p->frames.length){
					animation_p->currentFrame = 0;
				}

				animation_p->currentFrameDurationCounter = 0;
				
			}else{

				animation_p->currentFrameDurationCounter++;
			
			}

		}

	}

}

Animation_Frame *Animation_getCurrentFramePointer(Animation *animation_p){

	for(int i = 0; i < animation_p->states.length; i++){

		Animation_State *state_p = Array_getItemPointerByIndex(&animation_p->states, i);

		if(strcmp(state_p->name, animation_p->currentState) == 0){

			Animation_Frame *frame_p = Array_getItemPointerByIndex(&state_p->frames, animation_p->currentFrame);

			return frame_p;
		
		}
	
	}

	printf("Could not get current frame!\n");
	
}
