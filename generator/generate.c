#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct Level{
	char data[4 * 1024];
	int x;
	int y;
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

	int levelsLength = 0;
	Level levels[255];

	FILE *file;

	file = fopen("levels.cpp", "r");

	char line[255];

	while(fgets(line, 255, file) != NULL){

		char word[6];

		if(*strncpy(word, line, 6) == *":level"){

			char *endPointer = line + 6 * sizeof(char);

			levels[levelsLength].x = strtol(endPointer, &endPointer, 10);

			levels[levelsLength].y = strtol(endPointer, NULL, 10);

			levelsLength++;
		}

	}

	//char levelsData[levels][4 * 1024];

	fseek(file, 0, SEEK_SET);

	char c;
	int blockLevel = 0;
	int currentLevel = 0;
	int currentLevelIndex = 0;

	while((c = fgetc(file)) != EOF){

		if(blockLevel > 0){
			levels[currentLevel].data[currentLevelIndex] = c;

			//printf("i: %i\n", currentLevelIndex);

			currentLevelIndex++;
		}

		if(c == *"{"){
			blockLevel++;

		}

		if(c == *"}"){

			levels[currentLevel].data[currentLevelIndex] = *"\0";

			blockLevel--;

			if(blockLevel == 0){
				currentLevel++;
				currentLevelIndex = 0;
			}
		}

	}

	fclose(file);

	/*
	for(int i = 0; i < levels; i++){
		for(int j = 1023; j >= 0; j--){
			if(levelsData[i][j] == *"}"){
				levelsData[i][j + 1] = "\0";
				printf("CHECK\n");
			}
		}
	}
	*/


	/*
	for(int i = 0; i < levels; i++){
		printf("%c\n", levelsData[i][strlen(levelsData[i]) - 1]);
	}
	*/

	char *topOfFile = "#include \"stdbool.h\"\n#include \"math.h\"\n#include \"stdio.h\"\n#include \"geometry.h\"\n#include \"rendering.h\"\n#include \"utils.h\"\n#include \"stb_truetype.h\"\n#include \"text.h\"\n#include \"game.h\"\n#include \"levels.h\"\n";
	
	//char *topOfFile = "hello\n";

	file = fopen("generatedLevels.c", "w");

	fputs(topOfFile, file);

	for(int i = 0; i < levelsLength; i++){

		char definition[255];
		sprintf(definition, "\nvoid World_generateLevel%i(World *w){", i + 1);

		fputs(definition, file);

		fputs(levels[i].data, file);

		fputs("\n", file);
	}

	fclose(file);

	file = fopen("levels.h", "w");

	fputs("#ifndef LEVELS_H_\n#define LEVELS_H_\n", file);

	fputs("\ntypedef struct Level{\n\tvoid (*generate)(World *);\n\tint x;\n\tint y;\n}Level;\n", file);

	for(int i = 0; i < levelsLength; i++){

		char definition[255];
		sprintf(definition, "\nvoid World_generateLevel%i(World *);\n", i + 1);

		fputs(definition, file);
		
	}

	char levelsLengthString[255];
	sprintf(levelsLengthString, "\nstatic int levelsLength = %i;\n", levelsLength);

	fputs(levelsLengthString, file);

	//fputs("\nstatic void (*levels[255])(World *w) = {\n", file);
	fputs("\nstatic Level levels[255] = {\n", file);

	for(int i = 0; i < levelsLength; i++){

		char definition[255];
		sprintf(definition, "\tWorld_generateLevel%i, %i, %i,\n", i + 1, levels[i].x, levels[i].y);

		fputs(definition, file);
		
	}

	fputs("};\n\n", file);

	fputs("#endif", file);

	printf("gonnageneratesomelevels\n");

	return 0;
}
