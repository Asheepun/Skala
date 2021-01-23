#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

size_t exitLevelButtonID;
size_t returnButtonID;
size_t quitButtonID;
size_t menuBackgroundSpriteID;

size_t activeButtonIDs[16];
unsigned int activeButtonIDsLength;

int currentButton;
bool pressingButton;

void World_initMenu(World *world_p){

	pressingButton = false;

	menuBackgroundSpriteID = World_addSprite(world_p, getVec2f(0, 0), getVec2f(WIDTH, HEIGHT), COLOR_BLACK, "menu-background", 1, MENU_LAYER_BACKGROUND);

	//add buttons
	activeButtonIDsLength = 0;
	int buttonsLeftOffset = 100;
	int buttonsTopOffset = 60;
	int buttonsMargin = 30;

	if(world_p->stateBeforeOpeningMenu == LEVEL_STATE){
		exitLevelButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Exit Level", MENU_LAYER_TEXT);
		activeButtonIDs[activeButtonIDsLength] = exitLevelButtonID;
		activeButtonIDsLength++;
		buttonsTopOffset += buttonsMargin;
	}

	returnButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Return", MENU_LAYER_TEXT);
	activeButtonIDs[activeButtonIDsLength] = returnButtonID;
	activeButtonIDsLength++;
	buttonsTopOffset += buttonsMargin;

	quitButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Quit", MENU_LAYER_TEXT);
	activeButtonIDs[activeButtonIDsLength] = quitButtonID;
	activeButtonIDsLength++;
	buttonsTopOffset += buttonsMargin;

	currentButton = activeButtonIDsLength - 2;

	world_p->renderer.offset.x = 0;
	world_p->renderer.offset.y = 0;
	
}

void World_menuState(World *world_p){

	printf("---\n");

	//handle input
	if(world_p->actions[DOWN_ACTION].downed){
		currentButton++;
	}
	if(world_p->actions[UP_ACTION].downed){
		currentButton--;
	}

	if(currentButton < 0){
		currentButton = activeButtonIDsLength - 1;
	}
	if(currentButton > activeButtonIDsLength - 1){
		currentButton = 0;
	}

	if(world_p->actions[DO_ACTION].downed){
		pressingButton = true;
	}else{
		pressingButton = false;
	}

	//check if or which button is pressed and handle button actions

	if(activeButtonIDs[currentButton] == exitLevelButtonID
	&& pressingButton){

		World_fadeTransitionToState(world_p, LEVEL_HUB_STATE);

		return;

	}

	if(activeButtonIDs[currentButton] == quitButtonID
	&& pressingButton){

		world_p->quit = true;

		return;

	}

	if(activeButtonIDs[currentButton] == returnButtonID
	&& pressingButton
	|| world_p->actions[BACK_ACTION].downed){

		//clean up menu sprites
		World_removeSpriteByID(world_p, menuBackgroundSpriteID);

		for(int i = 0; i < activeButtonIDsLength; i++){
			World_removeButtonByID(world_p, activeButtonIDs[i]);
		}

		world_p->currentState = world_p->stateBeforeOpeningMenu;

		return;

	}

	//set button colors
	for(int i = 0; i < activeButtonIDsLength; i++){

		Button *button_p = World_getButtonByID(world_p, activeButtonIDs[i]);
	
		if(button_p->buttonType == TEXT_BUTTON){

			Sprite *sprite_p = World_getSpriteByID(world_p, button_p->spriteID);

			sprite_p->color = COLOR_WHITE;

			if(i == currentButton){
				sprite_p->color = COLOR_YELLOW;
			}

		}
		
	}
	
}
