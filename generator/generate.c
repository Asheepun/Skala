#include "stdio.h"
#include "string.h"
#include "stdlib.h"

enum CurrentReadMode{
	NONE,
	LEVEL_NAME,
	LEVEL_CODE,
};

typedef struct Level{
	char name[255];
	char code[4 * 1024];
	//int x;
	//int y;
}Level;

int getWordCount(char *str, int len){
	int count = 1;
	for(int i = 0; i < len; i++){
		if(str[i] == *" "){
			count++;
		}
	}
	return count;
}

int main(){

	enum CurrentReadMode currentReadMode;
	currentReadMode = NONE;

	int levelsLength = 0;
	Level levels[255];

	FILE *file;

	//read input file
	file = fopen("levels.cpp", "r");

	char line[255];
	char word[255];

	printf("gonnageneratesomelevels\n");

	while(fgets(line, 255, file) != NULL){

		if(strcmp(strncpy(word, line, 2), "//") == 0){
			continue;
		}

		if(strcmp(strncpy(word, line, 10), ":levelName") == 0){

			currentReadMode = LEVEL_NAME;
			levelsLength++;

			continue;

		}

		if(strcmp(strncpy(word, line, 10), ":levelCode") == 0){

			currentReadMode = LEVEL_CODE;

			continue;

		}

		if(currentReadMode == LEVEL_NAME){

			strncpy(levels[levelsLength - 1].name, line, strlen(line) - 1);

		}

		if(currentReadMode == LEVEL_CODE){
			strcat(levels[levelsLength - 1].code, line);
		}

	}

	//write to output file generatedLevels.c
	char *topOfFile = "#include \"stdbool.h\"\n#include \"math.h\"\n#include \"stdio.h\"\n#include \"geometry.h\"\n#include \"utils.h\"\n#include \"stb_truetype.h\"\n#include \"text.h\"\n#include \"game.h\"\n#include \"levels.h\"\n";

	file = fopen("generatedLevels.c", "w");

	fputs(topOfFile, file);

	for(int i = 0; i < levelsLength; i++){

		char buffer[255];
		sprintf(buffer, "\nWorld_generateLevel%i(World *world_p){\n", i + 1);

		fputs(buffer, file);

		fputs(levels[i].code, file);

		fputs("}\n", file);
	
	}

	//write to output file levels.h
	file = fopen("levels.h", "w");

	fputs("#ifndef LEVELS_H_\n#define LEVELS_H_\n", file);

	fputs("\ntypedef struct Level{\n\tchar *name;\n\tvoid (*generate)(World *);\n}Level;\n\n", file);

	for(int i = 0; i < levelsLength; i++){

		char buffer[255];
		sprintf(buffer, "World_generateLevel%i(World *);\n", i + 1);

		fputs(buffer, file);
	
	}

	{
		char buffer[255];
		sprintf(buffer, "\nstatic const size_t LEVELS_LENGTH = %i;\n", levelsLength);

		fputs(buffer, file);
	}

	fputs("\nstatic Level levels[255] = {\n", file);

	for(int i = 0; i < levelsLength; i++){

		fputs("\t\"", file);
		fputs(levels[i].name, file);
		fputs("\",\n", file);

		char buffer[255];
		sprintf(buffer, "\tWorld_generateLevel%i,\n", i + 1);

		fputs(buffer, file);
	
	}

	fputs("};\n", file);

	fputs("\n#endif", file);

	printf("generated %i levels!\n", levelsLength);

	return 0;
}
