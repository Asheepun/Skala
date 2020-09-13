#include "SDL2/SDL.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "rendering.h"
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
}LevelGridTile;

int posX;
int posY;
int velocityX;
int velocityY;

LevelGridTile levelGrid[30][30];

bool setupLevelGrid = false;

//bool playImmidietly = false;
bool playImmidietly = true;

void World_initLevelSelectState(World *world_p){

	World_restore(world_p);

	velocityX = 0;
	velocityY = 0;

	if(!setupLevelGrid){

		posX = 15;
		posY = 20;
		//posY = 5;
		//posY = 11;
		//posX = 13;
		//posY = 15;

		for(int i = 0; i < 30; i++){
			for(int j = 0; j < 30; j++){
				levelGrid[i][j].levelIndex = -1;
				//levelGrid[i][j].locked = true;
				levelGrid[i][j].locked = false;
				levelGrid[i][j].completed = false;
			}
		}

		for(int i = 0; i < levelsLength; i++){
			levelGrid[levels[i].y][levels[i].x].levelIndex = i;
		}

		levelGrid[posY][posX].locked = false;

		setupLevelGrid = true;
	}

	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			if(levelGrid[j][i].levelIndex != -1){
				levelGrid[j][i].buttonID = World_addButton(world_p, getVec2f(0 + i * 15, 0 + j * 15), getVec2f(10, 10), "level");
			}
		}
	}

	world_p->currentState = World_levelSelectState;

}

void World_levelSelectState(World *world_p){

	printf("---\n");

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
		world_p->currentState = World_initLevelState;
	}

	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			if(levelGrid[i][j].levelIndex != -1){

				Button *button_p = Array_getItemPointerByID(&world_p->buttons, levelGrid[i][j].buttonID);

				world_p->sprites[button_p->spriteIndex].color = SPRITE_COLOR_WHITE;

				if(levelGrid[i][j].locked){
					world_p->sprites[button_p->spriteIndex].color = SPRITE_COLOR_BLACK;
				}

				if(levelGrid[i][j].completed){
					world_p->sprites[button_p->spriteIndex].color = SPRITE_COLOR_GREY;
				}

				if(j == posX && i == posY){
					world_p->sprites[button_p->spriteIndex].color = SPRITE_COLOR_YELLOW;
				}

			}
		}
	}

	char fpsString[255] = "";

	sprintf(fpsString, "level: %i, %i", posX, posY);

	TextSprite *textSprite_p = Array_getItemPointerByID(&world_p->textSprites, world_p->fpsTextID);
	Texture_freeData(&textSprite_p->texture);
	textSprite_p->texture = getTextureFromFontAndString_mustFree(world_p->fonts[0], fpsString);
	textSprite_p->body.size.x = textSprite_p->texture.width;
	textSprite_p->body.size.y = textSprite_p->texture.height;

	world_p->offset.x = WIDTH / 2 - posX * 15 - 8;
	world_p->offset.y = HEIGHT / 2 - posY * 15 - 8;

}

void unlockNearbyLevels(){
	levelGrid[posY][posX].completed = true;
	levelGrid[posY + 1][posX].locked = false;
	levelGrid[posY - 1][posX].locked = false;
	levelGrid[posY][posX + 1].locked = false;
	levelGrid[posY][posX - 1].locked = false;
}
