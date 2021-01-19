#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

void SaveData_init(SaveData *saveData_p){

	//saveData_p->playerHubPos = getVec2f(0, 0);

	saveData_p->playerHubPos = getVec2f(1850, 50);
	//saveData_p->playerHubPos = getVec2f(100, 50);

	Array_init(&saveData_p->completedLevels, sizeof(char *));

}
