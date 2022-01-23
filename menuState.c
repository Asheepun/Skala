#include "engine/engine.h"

#include "game.h"
#include "math.h"
#include "stdio.h"
#include "levels.h"

int exitLevelButtonID;
int restartLevelButtonID;
int settingsButtonID;
int returnButtonID;
int quitButtonID;

int returnToMainButtonID;

size_t menuBackgroundSpriteIndex;

size_t activeButtonIDs[NUMBER_OF_MENU_STATES][16];
unsigned int activeButtonIDsLength[NUMBER_OF_MENU_STATES];

int currentButton;
bool pressingButton;

enum MenuState currentMenuState;

void World_initMenu(World *world_p){

	currentMenuState = MENU_STATE_MAIN;

	exitLevelButtonID = -1;
	returnButtonID = -1;
	restartLevelButtonID = -1;
	quitButtonID = -1;

	pressingButton = false;

	menuBackgroundSpriteIndex = World_addSprite(world_p, getVec2f(0, 0), getVec2f(WIDTH, HEIGHT), COLOR_BLACK, "menu-background", 1, MENU_LAYER_BACKGROUND);

	//add main menu buttons
	{

		activeButtonIDsLength[MENU_STATE_MAIN] = 0;
		int buttonsLeftOffset = 100;
		int buttonsTopOffset = 60;
		int buttonsMargin = 30;

		if(world_p->stateBeforeOpeningMenu == LEVEL_STATE){
			exitLevelButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Exit Level", MENU_LAYER_TEXT, MENU_STATE_MAIN);
			activeButtonIDs[MENU_STATE_MAIN][activeButtonIDsLength[MENU_STATE_MAIN]] = exitLevelButtonID;
			activeButtonIDsLength[MENU_STATE_MAIN]++;
			buttonsTopOffset += buttonsMargin;
		}

		restartLevelButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Restart Level", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		activeButtonIDs[MENU_STATE_MAIN][activeButtonIDsLength[MENU_STATE_MAIN]] = restartLevelButtonID;
		activeButtonIDsLength[MENU_STATE_MAIN]++;
		buttonsTopOffset += buttonsMargin;

		settingsButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Settings", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		activeButtonIDs[MENU_STATE_MAIN][activeButtonIDsLength[MENU_STATE_MAIN]] = settingsButtonID;
		activeButtonIDsLength[MENU_STATE_MAIN]++;
		buttonsTopOffset += buttonsMargin;

		returnButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Return", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		activeButtonIDs[MENU_STATE_MAIN][activeButtonIDsLength[MENU_STATE_MAIN]] = returnButtonID;
		activeButtonIDsLength[MENU_STATE_MAIN]++;
		buttonsTopOffset += buttonsMargin;

		quitButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Quit", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		activeButtonIDs[MENU_STATE_MAIN][activeButtonIDsLength[MENU_STATE_MAIN]] = quitButtonID;
		activeButtonIDsLength[MENU_STATE_MAIN]++;
		buttonsTopOffset += buttonsMargin;

		currentButton = activeButtonIDsLength[MENU_STATE_MAIN] - 2;
	
	}

	//add settings buttons
	{

		activeButtonIDsLength[MENU_STATE_SETTINGS] = 0;
		int buttonsLeftOffset = 100;
		int buttonsTopOffset = 60;
		int buttonsMargin = 30;

		returnToMainButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Return", MENU_LAYER_TEXT, MENU_STATE_SETTINGS);
		activeButtonIDs[MENU_STATE_SETTINGS][activeButtonIDsLength[MENU_STATE_SETTINGS]] = returnToMainButtonID;
		activeButtonIDsLength[MENU_STATE_SETTINGS]++;
		buttonsTopOffset += buttonsMargin;
	
	}

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
		currentButton = activeButtonIDsLength[currentMenuState] - 1;
	}
	if(currentButton > activeButtonIDsLength[currentMenuState] - 1){
		currentButton = 0;
	}

	if(world_p->actions[DO_ACTION].downed){
		pressingButton = true;
	}else{
		pressingButton = false;
	}

	//check if or which button is pressed and handle button actions

	if(activeButtonIDs[currentMenuState][currentButton] == exitLevelButtonID
	&& pressingButton){

		World_fadeTransitionToState(world_p, LEVEL_HUB_STATE);

		return;

	}

	if(activeButtonIDs[currentMenuState][currentButton] == restartLevelButtonID
	&& pressingButton){

		if(world_p->stateBeforeOpeningMenu == LEVEL_STATE){
			World_switchToAndInitState(world_p, LEVEL_STATE);
		}
		if(world_p->stateBeforeOpeningMenu == LEVEL_HUB_STATE){
			World_switchToAndInitState(world_p, LEVEL_HUB_STATE);
		}

		return;
	
	}

	if(activeButtonIDs[currentMenuState][currentButton] == settingsButtonID
	&& pressingButton){

		currentMenuState = MENU_STATE_SETTINGS;
		currentButton = activeButtonIDsLength[MENU_STATE_SETTINGS] - 1;

		return;

	}

	if(activeButtonIDs[currentMenuState][currentButton] == quitButtonID
	&& pressingButton){

		Engine_quit();
		//world_p->quit = true;

		return;

	}

	if(activeButtonIDs[currentMenuState][currentButton] == returnButtonID
	&& pressingButton
	|| world_p->actions[BACK_ACTION].downed){

		//clean up menu sprites
		World_removeSpriteByIndex(world_p, menuBackgroundSpriteIndex);

		for(int i = 0; i < NUMBER_OF_MENU_STATES; i++){
			for(int j = 0; j < activeButtonIDsLength[i]; j++){
				World_removeButtonByID(world_p, activeButtonIDs[i][j]);
			}
		}

		world_p->currentState = world_p->stateBeforeOpeningMenu;

		return;

	}

	if(activeButtonIDs[currentMenuState][currentButton] == returnToMainButtonID
	&& pressingButton){

		currentMenuState = MENU_STATE_MAIN;
		currentButton = activeButtonIDsLength[MENU_STATE_MAIN] - 3;

		return;
	
	}

	//set button colors and visibility
	for(int i = 0; i < NUMBER_OF_MENU_STATES; i++){
		for(int j = 0; j < activeButtonIDsLength[i]; j++){

			Button *button_p = World_getButtonByID(world_p, activeButtonIDs[i][j]);
			Sprite *sprite_p = World_getSpriteByIndex(world_p, button_p->spriteIndex);

			if(button_p->menuState == currentMenuState){
				sprite_p->alpha = 1.0;
			}else{
				sprite_p->alpha = 0.0;
			}
		
			if(button_p->buttonType == TEXT_BUTTON){

				sprite_p->color = COLOR_WHITE;

				if(j == currentButton){
					sprite_p->color = COLOR_YELLOW;
				}

			}

		}
	}
	
}
