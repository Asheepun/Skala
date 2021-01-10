#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

#define LEVEL_GRID_WIDTH 30
#define LEVEL_GRID_HEIGHT 30

typedef struct LevelGridTile{
	int levelIndex;
	int buttonID;
	bool locked;
	bool completed;
	int unlockCounter;
	int unlockDelayCounter;
}LevelGridTile;

float UNLOCK_TIME = 60;
float UNLOCK_DELAY_TIME = 20;

int posX;
int posY;
int velocityX;
int velocityY;

LevelGridTile levelGrid[30][30];

bool playImmidietly = false;
//bool playImmidietly = true;

size_t currentLevelTextSpriteID;
size_t startTextSpriteID;

bool hasStarted = false;

size_t levelSelectStateFadeTransitionID = 6900;//så att det inte krockar första gången

void setupLevelGrid(){

	posX = 15;
	posY = 20;
	//posY = 9;
	//posY = 5;
	//posY = 11;
	//posX = 13;
	//posY = 15;

	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			levelGrid[i][j].levelIndex = -1;
			levelGrid[i][j].locked = true;
			//levelGrid[i][j].locked = false;
			levelGrid[i][j].completed = false;
			levelGrid[i][j].unlockCounter = -1;
			levelGrid[i][j].unlockDelayCounter = -1;
		}
	}

	for(int i = 0; i < levelsLength; i++){
		levelGrid[levels[i].y][levels[i].x].levelIndex = i;
	}

	levelGrid[posY][posX].locked = false;

}

void World_initLevelSelect(World *world_p){

	World_restore(world_p);

	velocityX = 0;
	velocityY = 0;

	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			if(levelGrid[j][i].levelIndex != -1){
				levelGrid[j][i].buttonID = World_addButton(world_p, getVec2f(0 + i * 15, 0 + j * 15), getVec2f(10, 10), "level");
			}
		}
	}

	currentLevelTextSpriteID = World_addTextSprite(world_p, getVec2f(100, 100), "", 0, COLOR_WHITE);

	if(!hasStarted){

		startTextSpriteID = World_addTextSprite(world_p, getVec2f(175, 330), "Press X to start", 0, COLOR_WHITE);
		
		hasStarted = true;

	}

	world_p->currentState = World_levelSelectState;

}

void World_levelSelectState(World *world_p){

	if(world_p->fadeTransitionCounter > FADE_TRANSITION_TIME / 2){
		return;
	}

	//printf("---\n");

	velocityX = 0;
	velocityY = 0;

	if(world_p->actions[UP_ACTION].downed){
		velocityY--;
	}
	if(world_p->actions[DOWN_ACTION].downed){
		velocityY++;
	}
	if(world_p->actions[LEFT_ACTION].downed){
		velocityX--;
	}
	if(world_p->actions[RIGHT_ACTION].downed){
		velocityX++;
	}

	posX += velocityX;

	if(posX < 0
	|| posX > 29
	|| levelGrid[posY][posX].levelIndex == -1
	|| levelGrid[posY][posX].locked){
		posX -= velocityX;
	}

	posY += velocityY;

	if(posY < 0
	|| posY > 29
	|| levelGrid[posY][posX].levelIndex == -1
	|| levelGrid[posY][posX].locked){
		posY -= velocityY;
	}

	if(world_p->actions[DO_ACTION].downedNoRepeat
	|| playImmidietly){
		world_p->currentLevel = levelGrid[posY][posX].levelIndex;
		world_p->fadeTransitionCounter = FADE_TRANSITION_TIME;
		world_p->nextStateAfterTransition = World_initLevelState;
		//levelSelectStateFadeTransitionID = World_fadeTransition(world_p);
	}

	/*
	if(world_p->fadeTransitionCounter == FADE_TRANSITION_TIME / 2
	&& levelSelectStateFadeTransitionID == world_p->currentFadeTransitionID){
		world_p->currentLevel = levelGrid[posY][posX].levelIndex;
		world_p->currentState = World_initLevelState;
	}
	*/

	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			if(levelGrid[i][j].levelIndex != -1){

				Button *button_p = Array_getItemPointerByID(&world_p->buttons, levelGrid[i][j].buttonID);

				Sprite *sprite_p = &world_p->sprites[button_p->spriteIndex];

				LevelGridTile *levelTile_p = &levelGrid[i][j];

				if(levelTile_p->unlockDelayCounter == 0){
					levelTile_p->unlockCounter = UNLOCK_TIME;
				}
				if(levelTile_p->unlockDelayCounter >= 0
				&& world_p->fadeTransitionCounter < 0){
					levelTile_p->unlockDelayCounter--;
				}

				if(levelTile_p->unlockCounter > 0){

					levelTile_p->unlockCounter--;

					sprite_p->alpha = (UNLOCK_TIME - (float)levelTile_p->unlockCounter) / UNLOCK_TIME;

				}

				sprite_p->color = SPRITE_COLOR_WHITE;

				if(levelTile_p->locked
				|| levelTile_p->unlockDelayCounter >= 0){
					sprite_p->alpha = 0;
				}

				if(levelTile_p->completed){
					sprite_p->color = SPRITE_COLOR_GREY;
				}

				if(j == posX && i == posY){
					sprite_p->color = SPRITE_COLOR_YELLOW;
				}

			}
		}
	}

	world_p->renderOffset.x = WIDTH / 2 - posX * 15 - 8;
	world_p->renderOffset.y = HEIGHT / 2 - posY * 15 - 8;

	TextSprite *currentLevelTextSprite_p = World_getTextSpriteByID(world_p, currentLevelTextSpriteID);

	currentLevelTextSprite_p->pos.x = 10 - world_p->renderOffset.x;
	currentLevelTextSprite_p->pos.y = 5 - world_p->renderOffset.y;

	sprintf(currentLevelTextSprite_p->text, "%i, %i", posX, posY);

	strcpy(currentLevelTextSprite_p->text, "");

}

void unlockNearbyLevels(){

	levelGrid[posY][posX].locked = false; //for first level

	levelGrid[posY][posX].completed = true;

	int coolDelay = 0;

	if(levelGrid[posY][posX - 1].locked
	&& levelGrid[posY][posX - 1].levelIndex != -1){
		levelGrid[posY][posX - 1].unlockDelayCounter = UNLOCK_DELAY_TIME * coolDelay;
		levelGrid[posY][posX - 1].locked = false;
		coolDelay++;
	}
	if(levelGrid[posY - 1][posX].locked
	&& levelGrid[posY - 1][posX].levelIndex != -1){
		levelGrid[posY - 1][posX].unlockDelayCounter = UNLOCK_DELAY_TIME * coolDelay;
		levelGrid[posY - 1][posX].locked = false;
		coolDelay++;
	}
	if(levelGrid[posY][posX + 1].locked
	&& levelGrid[posY][posX + 1].levelIndex != -1){
		levelGrid[posY][posX + 1].unlockDelayCounter = UNLOCK_DELAY_TIME * coolDelay;
		levelGrid[posY][posX + 1].locked = false;
		coolDelay++;
	}
	if(levelGrid[posY + 1][posX].locked
	&& levelGrid[posY + 1][posX].levelIndex != -1){
		levelGrid[posY + 1][posX].unlockDelayCounter = UNLOCK_DELAY_TIME * coolDelay;
		levelGrid[posY + 1][posX].locked = false;
		coolDelay++;
	}

	/*
	levelGrid[posY + 1][posX].locked = false;
	levelGrid[posY - 1][posX].locked = false;
	levelGrid[posY][posX + 1].locked = false;
	levelGrid[posY][posX - 1].locked = false;
	*/

}
