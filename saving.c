#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

enum CurrentReadMode{
	SEARCHING,
	PLAYER_POS,
	COMPLETED_LEVELS,
};

void SaveData_init(SaveData *saveData_p){

	//saveData_p->playerHubPos = getVec2f(0, 0);

	saveData_p->playerPos = getVec2f(1850, 50);
	//saveData_p->playerHubPos = getVec2f(100, 50);

	Array_init(&saveData_p->completedLevels, sizeof(char *));

}

void SaveData_read(SaveData *saveData_p){

	//free strings
	for(int i = 0; i < saveData_p->completedLevels.length; i++){
		free(*((char **)Array_getItemPointerByIndex(&saveData_p->completedLevels, i)));
	}

	Array_clear(&saveData_p->completedLevels);

	enum CurrentReadMode currentReadMode;
	currentReadMode = SEARCHING;
	
	FILE *file;

	file = fopen("saveData.txt", "r");

	char line[255];
	char word[255];

	while(fgets(line, 255, file) != NULL){

		memset(word, 0, strlen(word));
		strncpy(word, line, strlen(line) - 1);

		if(strcmp(word, "//") == 0){
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

		if(currentReadMode == PLAYER_POS){

			char *ptr;

			float x = strtol(word, &ptr, 10);
			float y = strtol(ptr, &ptr, 10);

			saveData_p->playerPos.x = x;
			saveData_p->playerPos.y = y;

		}

		if(currentReadMode == COMPLETED_LEVELS){

			char **levelName = Array_addItem(&saveData_p->completedLevels);

			*levelName = malloc(sizeof(char) * strlen(word));//MUST FREE (is freed at top of function)
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
		sprintf(buff, "%i %i\n", (int)saveData_p->playerPos.x, (int)saveData_p->playerPos.y);

		fputs(buff, file);
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
