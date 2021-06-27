//#include "stdbool.h"
#include "game.h"

#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
//#include "geometry.h"
//#include "stb_truetype.h"
//#include "text.h"
//#include "utils.h"
//#include "levels.h"

enum CurrentReadMode{
	SEARCHING,
	FLAGS,
	PLAYER_POS,
	COMPLETED_LEVELS,
	DOORS,
	DOOR_KEYS,
	LEVELS_WITH_DOOR_KEY,
};

void SaveData_init(SaveData *saveData_p){

	//saveData_p->playerHubPos = getVec2f(0, 0);

	saveData_p->playerPos = getVec2f(1850, 50);
	//saveData_p->playerHubPos = getVec2f(100, 50);

	Array_init(&saveData_p->flags, sizeof(char *));
	Array_init(&saveData_p->completedLevels, sizeof(char *));
	Array_init(&saveData_p->levelsWithDoorKey, sizeof(char *));
	Array_init(&saveData_p->doorKeys, sizeof(Vec2f));
	Array_init(&saveData_p->doors, sizeof(Body));

	//char **levelWithDoorKey_p = Array_addItem(&saveData_p->levelsWithDoorKey);
	//*levelWithDoorKey_p = "get-key-up-2";

	/*
	Body *doorBody_p = Array_addItem(&saveData_p->doors);
	doorBody_p->pos = getVec2f(1400, 180);
	doorBody_p->size = getVec2f(20, 60);
	*/

}

void SaveData_read(SaveData *saveData_p){

	//free strings
	for(int i = 0; i < saveData_p->completedLevels.length; i++){
		free(*((char **)Array_getItemPointerByIndex(&saveData_p->flags, i)));
	}
	for(int i = 0; i < saveData_p->completedLevels.length; i++){
		free(*((char **)Array_getItemPointerByIndex(&saveData_p->completedLevels, i)));
	}
	for(int i = 0; i < saveData_p->levelsWithDoorKey.length; i++){
		free(*((char **)Array_getItemPointerByIndex(&saveData_p->levelsWithDoorKey, i)));
	}

	Array_clear(&saveData_p->flags);
	Array_clear(&saveData_p->completedLevels);
	Array_clear(&saveData_p->levelsWithDoorKey);

	enum CurrentReadMode currentReadMode;
	currentReadMode = SEARCHING;
	
	FILE *file;

	file = fopen("saveData.txt", "r");

	char line[255];
	char word[255];
	memset(line, 0, 255);
	memset(word, 0, 255);

	while(fgets(line, 255, file) != NULL){

		memset(word, 0, strlen(word));

		if(strcmp(strncpy(word, line, 2), "//") == 0){
			continue;
		}

		strncpy(word, line, strlen(line) - 1);

		if(strcmp(word, ":flags") == 0){
			currentReadMode = FLAGS;
			continue;
		}

		if(strcmp(word, ":playerPos") == 0){
			currentReadMode = PLAYER_POS;
			continue;
		}

		if(strcmp(word, ":completedLevels") == 0){
			currentReadMode = COMPLETED_LEVELS;
			continue;
		}

		if(strcmp(word, ":doors") == 0){
			currentReadMode = DOORS;
			continue;
		}

		if(strcmp(word, ":doorKeys") == 0){
			currentReadMode = DOOR_KEYS;
			continue;
		}

		if(strcmp(word, ":levelsWithDoorKey") == 0){
			currentReadMode = LEVELS_WITH_DOOR_KEY;
			continue;
		}

		if(currentReadMode == PLAYER_POS){

			char *ptr;

			float x = strtol(word, &ptr, 10);
			float y = strtol(ptr, &ptr, 10);

			saveData_p->playerPos.x = x;
			saveData_p->playerPos.y = y;

		}

		if(currentReadMode == DOORS){

			Body *doorBody_p = Array_addItem(&saveData_p->doors);

			char *ptr;

			float posX = strtol(word, &ptr, 10);
			float posY = strtol(ptr, &ptr, 10);
			float sizeX = strtol(ptr, &ptr, 10);
			float sizeY = strtol(ptr, &ptr, 10);

			doorBody_p->pos = getVec2f(posX, posY);
			doorBody_p->size = getVec2f(sizeX, sizeY);

		}

		if(currentReadMode == DOOR_KEYS){

			Vec2f *doorKeyPos_p = Array_addItem(&saveData_p->doorKeys);

			char *ptr;

			float x = strtol(word, &ptr, 10);
			float y = strtol(ptr, &ptr, 10);

			doorKeyPos_p->x = x;
			doorKeyPos_p->y = y;

		}

		if(currentReadMode == FLAGS){

			char **levelName = Array_addItem(&saveData_p->flags);

			*levelName = malloc(sizeof(char) * 255);//MUST FREE (is freed at top of function)
			memset(*levelName, 0, 255);
			memcpy(*levelName, word, strlen(word));

		}

		if(currentReadMode == LEVELS_WITH_DOOR_KEY){

			char **levelName = Array_addItem(&saveData_p->levelsWithDoorKey);

			*levelName = malloc(sizeof(char) * 255);//MUST FREE (is freed at top of function)
			memset(*levelName, 0, 255);
			memcpy(*levelName, word, strlen(word));

		}
	

		if(currentReadMode == COMPLETED_LEVELS){

			char **levelName = Array_addItem(&saveData_p->completedLevels);

			*levelName = malloc(sizeof(char) * 255);//MUST FREE (is freed at top of function)
			memset(*levelName, 0, 255);
			memcpy(*levelName, word, strlen(word));

		}
	
	}

	fclose(file);

}

void SaveData_write(SaveData *saveData_p){

	FILE *file;

	file = fopen("saveData.txt", "w");

	{
		fputs(":playerPos\n", file);

		char buff[255];
		memset(buff, 0, 255);
		sprintf(buff, "%i %i\n", (int)saveData_p->playerPos.x, (int)saveData_p->playerPos.y);

		fputs(buff, file);
	}
	
	{
		fputs(":doorKeys\n", file);

		for(int i = 0; i < saveData_p->doorKeys.length; i++){

			Vec2f *doorKeyPos_p = Array_getItemPointerByIndex(&saveData_p->doorKeys, i);

			char buff[255];
			memset(buff, 0, 255);
			sprintf(buff, "%i %i\n", (int)doorKeyPos_p->x, (int)doorKeyPos_p->y);

			fputs(buff, file);
		
		}
	}

	{
		fputs(":doors\n", file);

		for(int i = 0; i < saveData_p->doors.length; i++){

			Body *doorBody_p = Array_getItemPointerByIndex(&saveData_p->doors, i);

			char buff[255];
			memset(buff, 0, 255);
			sprintf(buff, "%i %i %i %i\n", (int)doorBody_p->pos.x, (int)doorBody_p->pos.y, (int)doorBody_p->size.x, (int)doorBody_p->size.y);

			fputs(buff, file);
		
		}
	}
	
	{
		fputs(":flags\n", file);

		for(int i = 0; i < saveData_p->flags.length; i++){

			char *flag = *((char **)Array_getItemPointerByIndex(&saveData_p->flags, i));

			fputs(flag, file);

			fputs("\n", file);
		
		}
	}

	{
		fputs(":levelsWithDoorKey\n", file);

		for(int i = 0; i < saveData_p->levelsWithDoorKey.length; i++){

			char *levelWithDoorKeyName = *((char **)Array_getItemPointerByIndex(&saveData_p->levelsWithDoorKey, i));

			fputs(levelWithDoorKeyName, file);

			fputs("\n", file);
		
		}
	}

	{
		fputs(":completedLevels\n", file);

		for(int i = 0; i < saveData_p->completedLevels.length; i++){

			char *completedLevelName = *((char **)Array_getItemPointerByIndex(&saveData_p->completedLevels, i));

			fputs(completedLevelName, file);

			fputs("\n", file);
		
		}
	}

	fclose(file);
	
}

bool SaveData_hasFlag(SaveData *saveData_p, char *flag){

	for(int i = 0; i < saveData_p->flags.length; i++){

		char *checkFlag = *((char **)Array_getItemPointerByIndex(&saveData_p->flags, i));

		if(strcmp(checkFlag, flag) == 0){
			return true;
		}

	}

	return false;

}

void SaveData_addFlag(SaveData *saveData_p, char *flag){
	if(!SaveData_hasFlag(saveData_p, flag)){
		char **flag_p = Array_addItem(&saveData_p->flags);
		*flag_p = flag;
	}
}
