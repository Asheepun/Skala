#include "engine/engine.h"
#include "engine/audio.h"
#include "engine/files.h"

#include "game.h"
#include "math.h"
#include "stdio.h"
#include "levels.h"
#include "string.h"

int NUMBER_OF_REBINDABLE_ACTIONS = 6;

size_t menuBackgroundSpriteIndex;

enum MenuState currentMenuState;
int currentButton;

bool pressingButton = false;

bool bindingAction = false;
int actionToBindIndex;

void clearMenuButtonsAndSprites(World *world_p){

	for(int i = 0; i < world_p->menuButtonIDs.length; i++){

		size_t *ID_p = Array_getItemPointerByIndex(&world_p->menuButtonIDs, i);
		
		World_removeButtonByID(world_p, *ID_p);

	}

	Array_clear(&world_p->menuButtonIDs);

	for(int i = 0; i < world_p->menuSpriteIndices.length; i++){

		size_t *index_p = Array_getItemPointerByIndex(&world_p->menuSpriteIndices, i);
		
		World_removeSpriteByIndex(world_p, *index_p);

	}

	Array_clear(&world_p->menuSpriteIndices);


}

void addMainMenuButtons(World *world_p){

	clearMenuButtonsAndSprites(world_p);

	int buttonsLeftOffset = 100;
	int buttonsTopOffset = 60;
	int buttonsMargin = 30;

	if(world_p->stateBeforeOpeningMenu == LEVEL_STATE){
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Exit Level", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Restart Level", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Delete Save Data", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Settings", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Return", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Quit", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}

	currentMenuState = MENU_STATE_MAIN;

}

void addSettingsMenuButtons(World *world_p){

	clearMenuButtonsAndSprites(world_p);

	int buttonsLeftOffset = 100;
	int buttonsTopOffset = 60;
	int buttonsMargin = 30;

	{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Music Volume", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Sfx Volume", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Controls", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Fullscreen", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Return", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}

	currentMenuState = MENU_STATE_SETTINGS;

}

void addControlMenuButtons(World *world_p){

	clearMenuButtonsAndSprites(world_p);

	int buttonsLeftOffset = 100;
	int buttonsTopOffset = 60;
	int buttonsMargin = 30;

	{
		size_t *index_p = Array_addItem(&world_p->menuSpriteIndices);
		*index_p = World_addTextSprite(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset - 40), "Action", "times30", COLOR_WHITE, MENU_LAYER_TEXT);
	}{
		size_t *index_p = Array_addItem(&world_p->menuSpriteIndices);
		*index_p = World_addTextSprite(world_p, getVec2f(buttonsLeftOffset + 140, buttonsTopOffset - 40), "Key", "times30", COLOR_WHITE, MENU_LAYER_TEXT);
	}

	for(int i = 0; i < NUMBER_OF_REBINDABLE_ACTIONS; i++){

		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		Action *action_p = &world_p->actions[i];

		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), ACTION_NAMES[i], MENU_LAYER_TEXT, MENU_STATE_MAIN);

		size_t *index_p = Array_addItem(&world_p->menuSpriteIndices);
		*index_p = World_addTextSprite(world_p, getVec2f(buttonsLeftOffset + 140, buttonsTopOffset), Engine_keyNames[action_p->bindings[0]], "times20", COLOR_WHITE, MENU_LAYER_TEXT);

		buttonsTopOffset += 20;

	}

	buttonsTopOffset += 10;

	{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Return", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}

	currentMenuState = MENU_STATE_CONTROLS;

}

void addYesNoMenuButtons(World *world_p){

	clearMenuButtonsAndSprites(world_p);

	int buttonsLeftOffset = 100;
	int buttonsTopOffset = 60;
	int buttonsMargin = 30;

	{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Yes", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}{
		size_t *ID_p = Array_addItem(&world_p->menuButtonIDs);
		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "No", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		buttonsTopOffset += buttonsMargin;
	}

	currentButton = 1;

	currentMenuState = MENU_STATE_YES_NO;

}

void World_initMenu(World *world_p){

	menuBackgroundSpriteIndex = World_addSprite(world_p, getVec2f(0, 0), getVec2f(WIDTH, HEIGHT), COLOR_BLACK, "menu-background", 1, MENU_LAYER_BACKGROUND);

	addMainMenuButtons(world_p);

	currentButton = world_p->menuButtonIDs.length - 2;

	world_p->renderer.offset.x = 0;
	world_p->renderer.offset.y = 0;

}

void World_menuState(World *world_p){

	if(bindingAction){

		Action *action_p = &world_p->actions[actionToBindIndex];

		for(int i = 0; i < ENGINE_KEYS_LENGTH; i++){
			
			if(ENGINE_KEYS[i].downed){

				bindingAction = false;

				action_p->bindingsLength = 0;
				Action_addBinding(action_p, i);

				addControlMenuButtons(world_p);

				return;
			
			}
			
		}

		return;
	
	}

	//handle input
	if(world_p->actions[DOWN_ACTION].downed){
		currentButton++;
	}
	if(world_p->actions[UP_ACTION].downed){
		currentButton--;
	}

	if(currentButton < 0){
		currentButton = world_p->menuButtonIDs.length - 1;
	}
	if(currentButton > world_p->menuButtonIDs.length - 1){
		currentButton = 0;
	}

	if(world_p->actions[DO_ACTION].downed){
		pressingButton = true;
	}else{
		pressingButton = false;
	}

	//handle buttons
	for(int i = 0; i < world_p->menuButtonIDs.length; i++){

		size_t *ID_p = Array_getItemPointerByIndex(&world_p->menuButtonIDs, i);
		Button *button_p = World_getButtonByID(world_p, *ID_p);
		Sprite *sprite_p = World_getSpriteByIndex(world_p, button_p->spriteIndex);
		char *buttonText = sprite_p->text;


		if(i == currentButton){
			if(currentMenuState == MENU_STATE_MAIN){

				if(strcmp(buttonText, "Exit Level") == 0
				&& pressingButton){

					World_fadeTransitionToState(world_p, LEVEL_HUB_STATE);

					return;

				}

				if(strcmp(buttonText, "Restart Level") == 0
				&& pressingButton){

					World_removeSpriteByIndex(world_p, menuBackgroundSpriteIndex);
					clearMenuButtonsAndSprites(world_p);

					if(world_p->stateBeforeOpeningMenu == LEVEL_STATE){
						World_switchToAndInitState(world_p, LEVEL_STATE);
					}
					if(world_p->stateBeforeOpeningMenu == LEVEL_HUB_STATE){
						World_switchToAndInitState(world_p, LEVEL_HUB_STATE);
					}

					world_p->drawCallSkips += 1;

					return;
					
				}

				if(strcmp(buttonText, "Delete Save Data") == 0
				&& pressingButton){

					addYesNoMenuButtons(world_p);

					return;

				}

				if(strcmp(buttonText, "Settings") == 0
				&& pressingButton){

					addSettingsMenuButtons(world_p);

					currentButton = world_p->menuButtonIDs.length - 1;

					return;

				}

				if(strcmp(buttonText, "Return") == 0
				&& pressingButton
				|| world_p->actions[BACK_ACTION].downed){

					World_removeSpriteByIndex(world_p, menuBackgroundSpriteIndex);

					clearMenuButtonsAndSprites(world_p);

					world_p->currentState = world_p->stateBeforeOpeningMenu;

					world_p->drawCallSkips += 1;

					return;

				}

				if(strcmp(buttonText, "Quit") == 0
				&& pressingButton){

					Engine_quit();

					return;

				}
			
			}

			if(currentMenuState == MENU_STATE_SETTINGS){

				if(strncmp(buttonText, "Music Volume", 12) == 0){

					if(world_p->actions[RIGHT_ACTION].downed){
						world_p->settings.musicVolume += 0.05;
					}
					if(world_p->actions[LEFT_ACTION].downed){
						world_p->settings.musicVolume -= 0.05;
					}

					if(world_p->settings.musicVolume < 0){
						world_p->settings.musicVolume = 0;
					}
					if(world_p->settings.musicVolume > 1){
						world_p->settings.musicVolume = 1;
					}
				
				}
				
				if(strncmp(buttonText, "Sfx Volume", 10) == 0){

					if(world_p->actions[RIGHT_ACTION].downed){
						world_p->settings.sfxVolume += 0.05;
					}
					if(world_p->actions[LEFT_ACTION].downed){
						world_p->settings.sfxVolume -= 0.05;
					}

					if(world_p->settings.sfxVolume < 0){
						world_p->settings.sfxVolume = 0;
					}
					if(world_p->settings.sfxVolume > 1){
						world_p->settings.sfxVolume = 1;
					}
				
				}

				if(strcmp(buttonText, "Controls") == 0
				&& pressingButton){

					addControlMenuButtons(world_p);

					currentButton = world_p->menuButtonIDs.length - 1;

					return;

				}
				
				if(strncmp(buttonText, "Fullscreen", 10) == 0
				&& pressingButton){

					Engine_toggleFullscreen();

					return;

				}

				if(strcmp(buttonText, "Return") == 0
				&& pressingButton
				|| world_p->actions[BACK_ACTION].downed){

					addMainMenuButtons(world_p);

					currentButton = world_p->menuButtonIDs.length - 3;

					return;

				}
			
			}

			if(currentMenuState == MENU_STATE_CONTROLS){

				for(int i = 0; i < NUMBER_OF_REBINDABLE_ACTIONS; i++){

					if(strcmp(buttonText, ACTION_NAMES[i]) == 0
					&& pressingButton){

						Action *action_p = &world_p->actions[i];

						clearMenuButtonsAndSprites(world_p);

						char text[STRING_SIZE];
						String_set(text, "Press a key to bind the \"", STRING_SIZE);
						String_append(text, ACTION_NAMES[i]);
						String_append(text, "\" action.");

						size_t *index_p = Array_addItem(&world_p->menuSpriteIndices);
						*index_p = World_addTextSprite(world_p, getVec2f(80, 120), text, "times20", COLOR_WHITE, MENU_LAYER_TEXT);

						bindingAction = true;
						actionToBindIndex = i;
					
					}
				
				}

				if(strcmp(buttonText, "Return") == 0
				&& pressingButton
				|| world_p->actions[BACK_ACTION].downed){

					addSettingsMenuButtons(world_p);

					currentButton = world_p->menuButtonIDs.length - 3;

					return;

				}
			
			}

			if(currentMenuState == MENU_STATE_YES_NO){
				
				if(strcmp(buttonText, "Yes") == 0
				&& pressingButton){

					long int size;
					char *data_p = getFileData_mustFree("saveData-origin.txt", &size);

					writeDataToFile("saveData.txt", data_p, size);

					free(data_p);

					SaveData_init(&world_p->saveData);
					SaveData_read(&world_p->saveData);

					World_switchToAndInitState(world_p, LEVEL_HUB_STATE);

					return;
				
				}

				if(strcmp(buttonText, "No") == 0
				&& pressingButton
				|| world_p->actions[BACK_ACTION].downed){

					addMainMenuButtons(world_p);

					currentButton = world_p->menuButtonIDs.length - 4;

					return;
				
				}
				

			}
		
		}

		//set texts depending on current state
		if(strncmp(buttonText, "Music Volume", 12) == 0){
			String_set(sprite_p->text, "", SMALL_STRING_SIZE);
			sprintf(sprite_p->text, "Music Volume: %i\% <-+>", (int)round(100.0 * Audio_getVolume(AUDIO_SOUND_TYPE_MUSIC) / MUSIC_VOLUME_FACTOR));
		}
		if(strncmp(buttonText, "Sfx Volume", 10) == 0){
			String_set(sprite_p->text, "", SMALL_STRING_SIZE);
			sprintf(sprite_p->text, "Sfx Volume: %i\% <-+>", (int)round(100.0 * Audio_getVolume(AUDIO_SOUND_TYPE_SFX)));
		}
		if(strncmp(buttonText, "Fullscreen", 10) == 0){
			if(Engine_isFullscreen){
				String_set(sprite_p->text, "Fullscreen: On", STRING_SIZE);
			}else{
				String_set(sprite_p->text, "Fullscreen: Off", STRING_SIZE);
			}
		
		}

	}

	//set button colors and visibility
	for(int i = 0; i < world_p->menuButtonIDs.length; i++){

		size_t *ID_p = Array_getItemPointerByIndex(&world_p->menuButtonIDs, i);
		Button *button_p = World_getButtonByID(world_p, *ID_p);
		Sprite *sprite_p = World_getSpriteByIndex(world_p, button_p->spriteIndex);

		sprite_p->color = COLOR_WHITE;

		if(i == currentButton){
			sprite_p->color = COLOR_YELLOW;
		}

	}

}


/*
int exitLevelButtonID;
int restartLevelButtonID;
int settingsButtonID;
int returnButtonID;
int quitButtonID;
int deleteSaveDataButtonID;

int yesButtonID;
int noButtonID;

int returnToMainButtonID;
int fullscreenButtonID;
int controlsButtonID;
int musicVolumeButtonID;
int sfxVolumeButtonID;

int returnToSettingsButtonID;
int actionButtonIDs[NUMBER_OF_ACTIONS];
int controlsStateSpriteIndices[NUMBER_OF_ACTIONS + 2];
int numberOfControlsStateSprites = 0;
bool settingBinding = false;
bool allUpped = false;
int actionToSet;
int settingBindingSpriteIndex;

size_t menuBackgroundSpriteIndex;

size_t activeButtonIDs[NUMBER_OF_MENU_STATES][16];
unsigned int activeButtonIDsLength[NUMBER_OF_MENU_STATES];

int currentButton;
bool pressingButton;

enum MenuState currentMenuState;

void World_initMenu(World *world_p){

	currentMenuState = MENU_STATE_MAIN;

	currentMenuState = MENU_STATE_CONTROLS;

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

		deleteSaveDataButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Delete Save Data", MENU_LAYER_TEXT, MENU_STATE_MAIN);
		activeButtonIDs[MENU_STATE_MAIN][activeButtonIDsLength[MENU_STATE_MAIN]] = deleteSaveDataButtonID;
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

		musicVolumeButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Music Volume: 100% <- +>", MENU_LAYER_TEXT, MENU_STATE_SETTINGS);
		activeButtonIDs[MENU_STATE_SETTINGS][activeButtonIDsLength[MENU_STATE_SETTINGS]] = musicVolumeButtonID;
		activeButtonIDsLength[MENU_STATE_SETTINGS]++;
		buttonsTopOffset += buttonsMargin;

		sfxVolumeButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Sfx Volume: 100% <- +>", MENU_LAYER_TEXT, MENU_STATE_SETTINGS);
		activeButtonIDs[MENU_STATE_SETTINGS][activeButtonIDsLength[MENU_STATE_SETTINGS]] = sfxVolumeButtonID;
		activeButtonIDsLength[MENU_STATE_SETTINGS]++;
		buttonsTopOffset += buttonsMargin;

		controlsButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Controls", MENU_LAYER_TEXT, MENU_STATE_SETTINGS);
		activeButtonIDs[MENU_STATE_SETTINGS][activeButtonIDsLength[MENU_STATE_SETTINGS]] = controlsButtonID;
		activeButtonIDsLength[MENU_STATE_SETTINGS]++;
		buttonsTopOffset += buttonsMargin;

		fullscreenButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Fullscreen", MENU_LAYER_TEXT, MENU_STATE_SETTINGS);
		activeButtonIDs[MENU_STATE_SETTINGS][activeButtonIDsLength[MENU_STATE_SETTINGS]] = fullscreenButtonID;
		activeButtonIDsLength[MENU_STATE_SETTINGS]++;
		buttonsTopOffset += buttonsMargin;

		returnToMainButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Return", MENU_LAYER_TEXT, MENU_STATE_SETTINGS);
		activeButtonIDs[MENU_STATE_SETTINGS][activeButtonIDsLength[MENU_STATE_SETTINGS]] = returnToMainButtonID;
		activeButtonIDsLength[MENU_STATE_SETTINGS]++;
		buttonsTopOffset += buttonsMargin;
	
	}

	//add controls buttons
	{
		
		activeButtonIDsLength[MENU_STATE_CONTROLS] = 0;
		int buttonsLeftOffset = 100;
		int buttonsTopOffset = 60;
		int buttonsMargin = 20;

		numberOfControlsStateSprites = 0;

		controlsStateSpriteIndices[numberOfControlsStateSprites] = World_addTextSprite(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset - 40), "Action", "times30", COLOR_WHITE, MENU_LAYER_TEXT);
		numberOfControlsStateSprites++;
		controlsStateSpriteIndices[numberOfControlsStateSprites] = World_addTextSprite(world_p, getVec2f(buttonsLeftOffset + 140, buttonsTopOffset - 40), "Key", "times30", COLOR_WHITE, MENU_LAYER_TEXT);
		numberOfControlsStateSprites++;

		for(int i = 0; i < 6; i++){

			Action *action_p = &world_p->actions[i];

			actionButtonIDs[i] = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), ACTION_NAMES[i], MENU_LAYER_TEXT, MENU_STATE_CONTROLS);
			activeButtonIDs[MENU_STATE_CONTROLS][activeButtonIDsLength[MENU_STATE_CONTROLS]] = actionButtonIDs[i];
			activeButtonIDsLength[MENU_STATE_CONTROLS]++;

			controlsStateSpriteIndices[numberOfControlsStateSprites] = World_addTextSprite(world_p, getVec2f(buttonsLeftOffset + 140, buttonsTopOffset), Engine_keyNames[action_p->bindings[0]], "times20", COLOR_WHITE, MENU_LAYER_TEXT);
			numberOfControlsStateSprites++;

			buttonsTopOffset += buttonsMargin;

		}

		buttonsTopOffset += 10;

		returnToSettingsButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Return", MENU_LAYER_TEXT, MENU_STATE_CONTROLS);
		activeButtonIDs[MENU_STATE_CONTROLS][activeButtonIDsLength[MENU_STATE_CONTROLS]] = returnToSettingsButtonID;
		activeButtonIDsLength[MENU_STATE_CONTROLS]++;
		buttonsTopOffset += buttonsMargin;

	}

	//delete save data buttons
	{

		activeButtonIDsLength[MENU_STATE_DELETE_SAVE_DATA] = 0;
		int buttonsLeftOffset = 100;
		int buttonsTopOffset = 60;
		int buttonsMargin = 30;

		yesButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "Yes", MENU_LAYER_TEXT, MENU_STATE_DELETE_SAVE_DATA);
		activeButtonIDs[MENU_STATE_DELETE_SAVE_DATA][activeButtonIDsLength[MENU_STATE_DELETE_SAVE_DATA]] = yesButtonID;
		activeButtonIDsLength[MENU_STATE_DELETE_SAVE_DATA]++;
		buttonsTopOffset += buttonsMargin;

		noButtonID = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), "No", MENU_LAYER_TEXT, MENU_STATE_DELETE_SAVE_DATA);
		activeButtonIDs[MENU_STATE_DELETE_SAVE_DATA][activeButtonIDsLength[MENU_STATE_DELETE_SAVE_DATA]] = noButtonID;
		activeButtonIDsLength[MENU_STATE_DELETE_SAVE_DATA]++;
		buttonsTopOffset += buttonsMargin;
	
	}

	world_p->renderer.offset.x = 0;
	world_p->renderer.offset.y = 0;
	
}

void World_menuState(World *world_p){

	printf("---\n");

	//handle set control binding
	if(settingBinding){

		int uppedKeys = 0;

		for(int i = 0; i < ENGINE_KEYS_LENGTH; i++){

			if(!ENGINE_KEYS[i].down){
				uppedKeys++;
			}

			if(ENGINE_KEYS[i].down
			&& allUpped){

				settingBinding = false;

				World_removeSpriteByIndex(world_p, settingBindingSpriteIndex);

				return;
			
			}
		
		}

		if(uppedKeys == ENGINE_KEYS_LENGTH){
			allUpped = true;
		}

		return;
	
	}

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

	//handle main buttons

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

	if(activeButtonIDs[currentMenuState][currentButton] == deleteSaveDataButtonID
	&& pressingButton){

		currentMenuState = MENU_STATE_DELETE_SAVE_DATA;
		currentButton = activeButtonIDsLength[MENU_STATE_DELETE_SAVE_DATA] - 1;

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
	|| (world_p->actions[BACK_ACTION].downed
	&& currentMenuState == MENU_STATE_MAIN)){

		//clean up menu sprites
		World_removeSpriteByIndex(world_p, menuBackgroundSpriteIndex);
		for(int i = 0; i < numberOfControlsStateSprites; i++){
			World_removeSpriteByIndex(world_p, controlsStateSpriteIndices[i]);
		}

		for(int i = 0; i < NUMBER_OF_MENU_STATES; i++){
			for(int j = 0; j < activeButtonIDsLength[i]; j++){
				World_removeButtonByID(world_p, activeButtonIDs[i][j]);
			}
		}

		world_p->currentState = world_p->stateBeforeOpeningMenu;

		world_p->drawCallSkips += 1;

		return;

	}

	//handle settings buttons

	if(activeButtonIDs[currentMenuState][currentButton] == musicVolumeButtonID){

		if(world_p->actions[RIGHT_ACTION].downed){
			world_p->settings.musicVolume += 0.05;
		}
		if(world_p->actions[LEFT_ACTION].downed){
			world_p->settings.musicVolume -= 0.05;
		}

		if(world_p->settings.musicVolume < 0){
			world_p->settings.musicVolume = 0;
		}
		if(world_p->settings.musicVolume > 1){
			world_p->settings.musicVolume = 1;
		}
	
	}
	
	if(activeButtonIDs[currentMenuState][currentButton] == sfxVolumeButtonID){

		if(world_p->actions[RIGHT_ACTION].downed){
			world_p->settings.sfxVolume += 0.05;
		}
		if(world_p->actions[LEFT_ACTION].downed){
			world_p->settings.sfxVolume -= 0.05;
		}

		if(world_p->settings.sfxVolume < 0){
			world_p->settings.sfxVolume = 0;
		}
		if(world_p->settings.sfxVolume > 1){
			world_p->settings.sfxVolume = 1;
		}
	
	}

	if(activeButtonIDs[currentMenuState][currentButton] == controlsButtonID
	&& pressingButton){

		currentMenuState = MENU_STATE_CONTROLS;
		currentButton = activeButtonIDsLength[MENU_STATE_CONTROLS] - 1;

		return;

	}

	if(activeButtonIDs[currentMenuState][currentButton] == fullscreenButtonID
	&& pressingButton){

		Engine_toggleFullscreen();
		return;

	}

	if(activeButtonIDs[currentMenuState][currentButton] == returnToMainButtonID
	&& pressingButton
	|| (world_p->actions[BACK_ACTION].downed
	&& currentMenuState == MENU_STATE_SETTINGS)){

		currentMenuState = MENU_STATE_MAIN;
		currentButton = activeButtonIDsLength[MENU_STATE_MAIN] - 3;

		return;
	
	}

	//handle controls buttons

	for(int i = 0; i < 6; i++){
		
		if(activeButtonIDs[currentMenuState][currentButton] == actionButtonIDs[i]
		&& pressingButton){

			Action *action_p = &world_p->actions[i];

			settingBinding = true;
			allUpped = false;
			actionToSet = i;

			char text[STRING_SIZE];
			String_set(text, "Press a key to bind the \"", STRING_SIZE);
			String_append(text, ACTION_NAMES[i]);
			String_append(text, "\" action.");

			settingBindingSpriteIndex  = World_addTextSprite(world_p, getVec2f(80, 120), text, "times20", COLOR_WHITE, MENU_LAYER_TEXT);

			//hide stuff
			for(int i = 0; i < numberOfControlsStateSprites; i++){
				Sprite *sprite_p = World_getSpriteByIndex(world_p, controlsStateSpriteIndices[i]);
				sprite_p->alpha = 0.0;
			}

			for(int i = 0; i < NUMBER_OF_MENU_STATES; i++){
				for(int j = 0; j < activeButtonIDsLength[i]; j++){

					Button *button_p = World_getButtonByID(world_p, activeButtonIDs[i][j]);
					Sprite *sprite_p = World_getSpriteByIndex(world_p, button_p->spriteIndex);

					sprite_p->alpha = 0.0;
				}
			}

			return;

		}

	}

	if(activeButtonIDs[currentMenuState][currentButton] == returnToSettingsButtonID
	&& pressingButton
	|| (world_p->actions[BACK_ACTION].downed
	&& currentMenuState == MENU_STATE_CONTROLS)){

		currentMenuState = MENU_STATE_SETTINGS;
		currentButton = activeButtonIDsLength[MENU_STATE_SETTINGS] - 3;

		return;
	
	}


	//delete save data button actions
	if(activeButtonIDs[currentMenuState][currentButton] == yesButtonID
	&& pressingButton){

		//FILE *saveDataOriginFile = fread("saveData.txt");

		long int size;
		char *data_p = getFileData_mustFree("saveData-origin.txt", &size);

		writeDataToFile("saveData.txt", data_p, size);

		free(data_p);

		SaveData_init(&world_p->saveData);
		SaveData_read(&world_p->saveData);

		World_switchToAndInitState(world_p, LEVEL_HUB_STATE);

		//FILE *saveDataFile = fread("saveData.txt");

		//fclose(saveDataOriginFile);
		//fclose(saveDataFile);

		return;

	}

	if(activeButtonIDs[currentMenuState][currentButton] == noButtonID
	&& pressingButton
	|| (world_p->actions[BACK_ACTION].downed
	&& currentMenuState == MENU_STATE_DELETE_SAVE_DATA)){

		currentMenuState = MENU_STATE_MAIN;
		currentButton = 1;//activeButtonIDsLength[MENU_STATE_MAIN] - 2;

		return;

	}

	//update volume button texts
	{
		char text[SMALL_STRING_SIZE];
		String_set(text, "", SMALL_STRING_SIZE);

		sprintf(text, "Music Volume: %i\% <-+>", (int)round(100.0 * Audio_getVolume(AUDIO_SOUND_TYPE_MUSIC) / MUSIC_VOLUME_FACTOR));

		World_setButtonTextByID(world_p, musicVolumeButtonID,text);
	}
	{
		char text[SMALL_STRING_SIZE];
		String_set(text, "", SMALL_STRING_SIZE);

		sprintf(text, "Sfx Volume: %i\% <-+>", (int)round(100.0 * Audio_getVolume(AUDIO_SOUND_TYPE_SFX)));

		World_setButtonTextByID(world_p, sfxVolumeButtonID,text);
	}

	//update fullscreen button text
	if(Engine_isFullscreen){
		World_setButtonTextByID(world_p, fullscreenButtonID, "Fullscreen: On");
	}else{
		World_setButtonTextByID(world_p, fullscreenButtonID, "Fullscreen: Off");
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

	for(int i = 0; i < numberOfControlsStateSprites; i++){

		Sprite *sprite_p = World_getSpriteByIndex(world_p, controlsStateSpriteIndices[i]);

		if(currentMenuState == MENU_STATE_CONTROLS){
			sprite_p->alpha = 1.0;
		}else{
			sprite_p->alpha = 0.0;
		}
	
	}
	
}
*/

void Settings_init(Settings *settings_p){

	settings_p->fullscreenOn = true;
	settings_p->musicVolume = 0.5;
	settings_p->sfxVolume = 0.5;

	//settings_p->musicVolume = 0.0;
	//settings_p->sfxVolume = 0.0;

}

void World_Settings_updateWorld(World *world_p, Settings *settings_p){

	Audio_setVolume(settings_p->musicVolume * MUSIC_VOLUME_FACTOR, AUDIO_SOUND_TYPE_MUSIC);
	Audio_setVolume(settings_p->sfxVolume, AUDIO_SOUND_TYPE_SFX);

}
