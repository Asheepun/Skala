#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

size_t levelSelectButtonID;
size_t returnButtonID;
size_t quitButtonID;
size_t menuBackgroundSpriteID;

int currentButton;
bool pressingButton;

void World_initMenuState(World *w){
	pressingButton = false;

	menuBackgroundSpriteID = World_addSprite(w, getVec2f(0, 0), getVec2f(WIDTH, HEIGHT), COLOR_BLACK, "menu-background", 1, MENU_LAYER_BACKGROUND);



	levelSelectButtonID = World_addTextButton(w, getVec2f(100, 50), "Level Select", MENU_LAYER_TEXT);

	returnButtonID = World_addTextButton(w, getVec2f(100, 100), "Return", MENU_LAYER_TEXT);

	quitButtonID = World_addTextButton(w, getVec2f(100, 150), "Quit", MENU_LAYER_TEXT);

	currentButton = 1;

	//w->currentState = World_menuState;
	
}

void World_menuState(World *w){

	printf("---\n");

	if(w->actions[DOWN_ACTION].downed){
		currentButton++;
	}
	if(w->actions[UP_ACTION].downed){
		currentButton--;
	}

	if(currentButton < 0){
		currentButton = w->buttons.length - 1;
	}
	if(currentButton > w->buttons.length - 1){
		currentButton = 0;
	}

	if(w->actions[DO_ACTION].downed){
		pressingButton = true;
	}else{
		pressingButton = false;
	}

	if(currentButton == Array_getItemIndexByID(&w->buttons, levelSelectButtonID)
	&& pressingButton){
		World_switchToAndInitState(w, LEVEL_SELECT_STATE);
	}

	if(currentButton == Array_getItemIndexByID(&w->buttons, quitButtonID)
	&& pressingButton){
		w->quit = true;
	}

	if(currentButton == Array_getItemIndexByID(&w->buttons, returnButtonID)
	&& pressingButton
	|| w->actions[BACK_ACTION].downed){

		//funkar så här för att det som fanns inte ska försvinna
		World_removeButtonByID(w, levelSelectButtonID);
		World_removeButtonByID(w, quitButtonID);
		World_removeButtonByID(w, returnButtonID);

		World_removeSpriteByID(w, menuBackgroundSpriteID);

		w->currentState = LEVEL_STATE;
		return;
	}

	for(int i = 0; i < w->buttons.length; i++){

		Button *button_p = Array_getItemPointerByIndex(&w->buttons, i);
	
		if(button_p->buttonType == TEXT_BUTTON){

			//Sprite *sprite_p = Array_getItemPointerByID(&w->sprites, button_p->spriteID);
			Sprite *sprite_p = World_getSpriteByID(w, button_p->spriteID);

			sprite_p->color = COLOR_WHITE;

			if(i == currentButton){
				sprite_p->color = COLOR_YELLOW;
			}

		}
		
	}
	
}
