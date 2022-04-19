#include "engine/engine.h"
#include "engine/audio.h"
#include "engine/files.h"
#include "engine/strings.h"

#include "game.h"
#include "math.h"
#include "stdio.h"
#include "levels.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

int NUMBER_OF_REBINDABLE_ACTIONS = 7;

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
		//Action *action_p = &world_p->actions[i];

		*ID_p = World_addTextButton(world_p, getVec2f(buttonsLeftOffset, buttonsTopOffset), ACTION_NAMES[i], MENU_LAYER_TEXT, MENU_STATE_MAIN);

		size_t *index_p = Array_addItem(&world_p->menuSpriteIndices);
		*index_p = World_addTextSprite(world_p, getVec2f(buttonsLeftOffset + 140, buttonsTopOffset), Engine_keyNames[world_p->settings.actionBindings[i]], "times20", COLOR_WHITE, MENU_LAYER_TEXT);

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

		//Action *action_p = &world_p->actions[actionToBindIndex];

		for(int i = 0; i < ENGINE_KEYS_LENGTH; i++){
			
			if(ENGINE_KEYS[i].downed){

				bindingAction = false;

				//action_p->bindingsLength = 0;
				//Action_addBinding(action_p, i);

				world_p->settings.actionBindings[actionToBindIndex] = i;

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

					world_p->settings.fullscreen = !world_p->settings.fullscreen;

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
			sprintf(sprite_p->text, "Music Volume: %i\% <-+>", (int)round(100.0 * world_p->settings.musicVolume));
		}
		if(strncmp(buttonText, "Sfx Volume", 10) == 0){
			String_set(sprite_p->text, "", SMALL_STRING_SIZE);
			sprintf(sprite_p->text, "Sfx Volume: %i\% <-+>", (int)round(100.0 * world_p->settings.sfxVolume));
		}
		if(strncmp(buttonText, "Fullscreen", 10) == 0){
			if(world_p->settings.fullscreen){
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

void Settings_init(Settings *settings_p){

	settings_p->fullscreen = true;
	settings_p->musicVolume = 0.5;
	settings_p->sfxVolume = 0.5;

	//settings_p->musicVolume = 0.0;
	//settings_p->sfxVolume = 0.0;

}

void World_Settings_updateWorld(World *world_p, Settings *settings_p){

	Audio_setVolume(settings_p->musicVolume * MUSIC_VOLUME_FACTOR, AUDIO_SOUND_TYPE_MUSIC);
	Audio_setVolume(settings_p->sfxVolume, AUDIO_SOUND_TYPE_SFX);

	if(Engine_isFullscreen != settings_p->fullscreen){
		Engine_toggleFullscreen();
	}

	for(int i = 0; i < NUMBER_OF_REBINDABLE_ACTIONS; i++){

		Action *action_p = &world_p->actions[i];

		action_p->bindingsLength = 0;
		Action_addBinding(action_p, settings_p->actionBindings[i]);
	
	}

}

void Settings_readFromFile(Settings *settings_p){

	long int fileSize;
	char *data = getFileData_mustFree("settings.txt", &fileSize);

	int numberOfLines = 1;

	for(int i = 0; i < fileSize; i++){
		if(data[i] == *"\n"){
			numberOfLines++;
		}
	}

	char *lines = malloc(numberOfLines * STRING_SIZE);
	//char lines[numberOfLines][STRING_SIZE];

	{
		memset(lines, 0, numberOfLines * STRING_SIZE);

		int currentLine = 0;
		int currentChar = 0;

		for(int i = 0; i < fileSize; i++){

			if(data[i] == *"\n"){
				currentLine++;
				currentChar = 0;
				continue;
			}

			if(currentChar >= STRING_SIZE){
				break;
			}

			*(lines + currentLine * STRING_SIZE + currentChar) = data[i];
			currentChar++;

		}
	}

	char *ptr;

	for(int i = 0; i < numberOfLines; i++){

		if(strcmp(lines + i * STRING_SIZE, ":music-volume") == 0){
			float status = strtof(lines + (i + 1) * STRING_SIZE, &ptr);
			settings_p->musicVolume = status;
		}

		if(strcmp(lines + i * STRING_SIZE, ":sfx-volume") == 0){
			float status = strtof(lines + (i + 1) * STRING_SIZE, &ptr);
			settings_p->sfxVolume = status;
		}

		if(strcmp(lines + i * STRING_SIZE, ":fullscreen") == 0){
			long status = strtol(lines + (i + 1) * STRING_SIZE, &ptr, 10);
			settings_p->fullscreen = (bool)status;
		}

		if(strcmp(lines + i * STRING_SIZE, ":action-bindings") == 0){
			for(int j = 0; j < NUMBER_OF_REBINDABLE_ACTIONS; j++){
				long status = strtol(lines + (i + 1 + j) * STRING_SIZE, &ptr, 10);
				settings_p->actionBindings[j] = (int)status;
			}
		}

	}

	free(data);
	free(lines);

}

void Settings_writeToFile(Settings *settings_p){

	int dataSize = 10 * STRING_SIZE;

	char *data = malloc(dataSize);
	memset(data, 0, dataSize);

	String_append(data, ":fullscreen\n");
	String_append_int(data, settings_p->fullscreen);
	String_append(data, "\n");

	String_append(data, ":music-volume\n");
	String_append_float(data, settings_p->musicVolume);
	String_append(data, "\n");

	String_append(data, ":sfx-volume\n");
	String_append_float(data, settings_p->sfxVolume);
	String_append(data, "\n");

	String_append(data, ":action-bindings\n");
	for(int i = 0; i < NUMBER_OF_REBINDABLE_ACTIONS; i++){
		String_append_int(data, settings_p->actionBindings[i]);
		String_append(data, "\n");
	}

	writeDataToFile("settings.txt", data, dataSize);

	free(data);

}
