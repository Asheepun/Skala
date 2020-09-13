#include "SDL2/SDL.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "geometry.h"
#include "rendering.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

/**
 *
 * MÅSTE GÖRE EN KEY RESET FUNKTION SOM AKTIVERAS NÄR STATES BYTS!!!
 *
 *
 */

int getPixelIndex(int x, int y){
	return windowWidth * y + x;
}

int main(){

	SDL_Window *window = NULL;
	SDL_GLContext *context = NULL;

	SDL_Surface *screenSurface = NULL;
	SDL_Surface *windowSurface = NULL;

	Pixel screenPixels[(int)(windowWidth * windowHeight)];

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("scale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	screenSurface = SDL_CreateRGBSurfaceFrom((void*)screenPixels, windowWidth, windowHeight, 8 * 3, 3 * windowWidth, 0, 0, 0, 0);

	windowSurface = SDL_GetWindowSurface(window);

	char *assets[] = {
		"player",
		"point",
		"obstacle",
		"movement-help",
		"scale-help",
		"menu-background",
		"level",
	};

	int texturesLength = sizeof(assets) / sizeof(char *);

	Texture textures[texturesLength];

	TextureSliceMap textureSliceMaps[texturesLength];

	for(int i = 0; i < texturesLength; i++){

		Texture *texture_p = &textures[i];
		TextureSliceMap *textureSliceMap_p = &textureSliceMaps[i];

		texture_p->name = assets[i];

		char path[255];

		sprintf(path, "assets/sprites/%s.png", texture_p->name);

		int *comp;

		texture_p->data = stbi_load(path, &texture_p->width, &texture_p->height, &comp, 4);

		if(texture_p->data == NULL){
			printf("Failed to load texture %s\n", path);
		}

		TextureSliceMap_init(textureSliceMap_p, *texture_p);

	}

	//create color arrays

	Pixel **colorsArray;
	unsigned int colorsArrayLength = sizeof(SPRITE_COLORS) / sizeof(Vec4f);
	colorsArray = malloc(colorsArrayLength * sizeof(Pixel *));

	for(int i = 0; i < colorsArrayLength; i++){
		colorsArray[i] = malloc(sizeof(Pixel) * windowWidth);

		for(int j = 0; j < windowWidth; j++){
			colorsArray[i][j].r = SPRITE_COLORS[i].x * 255;
			colorsArray[i][j].g = SPRITE_COLORS[i].y * 255;
			colorsArray[i][j].b = SPRITE_COLORS[i].z * 255;
		}
	}

	World world;

	World_init(&world);

	for(int i = 0; i < 16; i++){
		Action_init(&world.actions[i]);
	}

	Action_addBinding(&world.actions[UP_ACTION], SDL_SCANCODE_UP);
	Action_addBinding(&world.actions[UP_ACTION], SDL_SCANCODE_W);
	Action_addBinding(&world.actions[DOWN_ACTION], SDL_SCANCODE_DOWN);
	Action_addBinding(&world.actions[DOWN_ACTION], SDL_SCANCODE_S);
	Action_addBinding(&world.actions[LEFT_ACTION], SDL_SCANCODE_LEFT);
	Action_addBinding(&world.actions[LEFT_ACTION], SDL_SCANCODE_A);
	Action_addBinding(&world.actions[RIGHT_ACTION], SDL_SCANCODE_RIGHT);
	Action_addBinding(&world.actions[RIGHT_ACTION], SDL_SCANCODE_D);
	Action_addBinding(&world.actions[DO_ACTION], SDL_SCANCODE_X);
	Action_addBinding(&world.actions[DO_ACTION], SDL_SCANCODE_J);
	Action_addBinding(&world.actions[BACK_ACTION], SDL_SCANCODE_ESCAPE);
	Action_addBinding(&world.actions[MENU_ACTION], SDL_SCANCODE_ESCAPE);

	world.currentLevel = 0;

	world.currentState = World_initLevelSelectState;
	//world.currentState = World_initLevelState;

	SDL_Event e;

	Vec2f scale = getVec2f(2, 2);

	int startTicks, endTicks;

	while(!world.quit){

		startTicks = SDL_GetTicks();

		while(SDL_PollEvent(&e)){

			if(e.type == SDL_QUIT){
				world.quit = true;
			}

			if(e.type == SDL_KEYDOWN){
				if(!world.keys[SDL_GetScancodeFromKey(e.key.keysym.sym)].down){
					world.keys[SDL_GetScancodeFromKey(e.key.keysym.sym)].downed = true;
					world.keys[SDL_GetScancodeFromKey(e.key.keysym.sym)].downedNoRepeat = true;
				}
				world.keys[SDL_GetScancodeFromKey(e.key.keysym.sym)].down = true;
			}
			if(e.type == SDL_KEYUP){
				world.keys[SDL_GetScancodeFromKey(e.key.keysym.sym)].down = false;
			}

		}

		for(int i = 0; i < 255; i++){
			if(world.keys[i].down){
				world.keys[i].downCounter--;
			}else{
				world.keys[i].downCounter = 36;
				//world.keys[i].downCounter = 48;
				//world.keys[i].downCounter = 8;
			}
			if(world.keys[i].downCounter == 0){
				world.keys[i].downed = true;
				world.keys[i].downCounter = 8;
			}
		}

		for(int i = 0; i < 16; i++){

			world.actions[i].down = false;
			world.actions[i].downed = false;
			world.actions[i].downedNoRepeat = false;

			for(int j = 0; j < world.actions[i].bindingsLength; j++){
				if(world.keys[world.actions[i].bindings[j]].down){
					world.actions[i].down = true;
				}
				if(world.keys[world.actions[i].bindings[j]].downed){
					world.actions[i].downed = true;
				}
				if(world.keys[world.actions[i].bindings[j]].downedNoRepeat){
					world.actions[i].downedNoRepeat = true;
				}
			}
		}

		if(world.keys[SDL_SCANCODE_Q].down){
			world.quit = true;
		}

		world.currentState(&world);

		//render

		//draw background
		for(int x = 0; x < windowWidth; x++){
			for(int y = 0; y < windowHeight; y++){

				int pixelIndex = getPixelIndex(x, y);

				screenPixels[pixelIndex].r = 0;
				screenPixels[pixelIndex].g = 0;
				screenPixels[pixelIndex].b = 0;
			}
		}

		//draw sprites
		for(int i = 0; i < world.spritesLength + world.spritesGaps; i++){
			if(world.sprites[i].active){

				Sprite *sprite_p = &world.sprites[i];

				Texture *texture_p;
				TextureSliceMap *textureSliceMap_p;

				for(int j = 0; j < texturesLength; j++){
					if(strcmp(textures[j].name, sprite_p->texture) == 0){
						texture_p = &textures[j];
						textureSliceMap_p = &textureSliceMaps[j];
					}
				}

				if(sprite_p->body.size.x < 1
				|| sprite_p->body.size.y < 1){
					continue;
				}

				float posX = (int)(sprite_p->body.pos.x + world.offset.x);
				float posY = (int)(sprite_p->body.pos.y + world.offset.y);

				float w = (int)sprite_p->body.size.x;
				float h = (int)sprite_p->body.size.y;

				float screenPosX = posX;
				float screenPosY = posY;
				float screenWidth = w;
				float screenHeight = h;

				if(posX + w < 0
				|| posX > WIDTH
				|| posY + h < 0
				|| posY > HEIGHT){
					continue;
				}

				if(screenPosX < 0){
					screenWidth += screenPosX;
					screenPosX = 0;
				}
				if(screenPosX + screenWidth > WIDTH){
					screenWidth = WIDTH - screenPosX;
				}

				if(screenPosY < 0){
					screenHeight += screenPosY;
					screenPosY = 0;
				}
				if(screenPosY + screenHeight > HEIGHT){
					screenHeight = HEIGHT - screenPosY;
				}

				if(sprite_p->alpha == 1){

					/*
					for(float y = 0; y < h * scale.y; y++){

						Array currentSliceArray = textureSliceMap_p->sliceArrays[(int)((y* texture->height / h) / scale.y)];

						for(int j = 0; j < currentSliceArray.length; j++){

							TextureSlice *textureSlice_p = Array_getItemPointerByIndex(&currentSliceArray, j);

							int pixelIndex = getPixelIndex(roundf((posX + (textureSlice_p->x * w / texture->width)) * scale.x), (int)(posY * scale.y + y));

							memcpy(screenPixels + pixelIndex, colorsArray[sprite_p->color], roundf((textureSlice_p->width * w / texture->width) * scale.x) * sizeof(Pixel));
						
						}
					
					}
					*/

					for(float y = 0; y < screenHeight * scale.y; y++){

						Array currentSliceArray = textureSliceMap_p->sliceArrays[(int)(((screenPosY - posY + y / scale.y) * texture_p->height / h))];

						for(int j = 0; j < currentSliceArray.length; j++){

							TextureSlice *textureSlice_p = Array_getItemPointerByIndex(&currentSliceArray, j);

							if(screenPosX + textureSlice_p->x > WIDTH){
								continue;
							}

							int width = roundf(textureSlice_p->width * screenWidth / texture_p->width);

							if(screenPosX + textureSlice_p->x + textureSlice_p->width > WIDTH){
								width = WIDTH - screenPosX - textureSlice_p->x;
							}

							int pixelIndex = getPixelIndex((int)((screenPosX + textureSlice_p->x) * scale.x), (int)(screenPosY * scale.y + y));

							memcpy(screenPixels + pixelIndex, colorsArray[sprite_p->color], (int)(width * scale.x * sizeof(Pixel)));
						
						}
						
					}

					/*
					//slice map rendering
					for(float y = 0; y < h * scale.y; y++){

						Array currentSliceArray = textureSliceMap_p->sliceArrays[(int)((y * texture_p->height / h) / scale.y)];

						for(int j = 0; j < currentSliceArray.length; j++){

							TextureSlice *textureSlice_p = Array_getItemPointerByIndex(&currentSliceArray, j);

							if(posX + textureSlice_p->x > WIDTH){
								continue;
							}

							int pixelIndex = getPixelIndex((roundf)((posX + (textureSlice_p->x * w / texture_p->width)) * scale.x), (int)(posY * scale.y + y));

							int width = textureSlice_p->width;
							if(posX + textureSlice_p->x + width > WIDTH){
								width = (int)(WIDTH - posX - textureSlice_p->x);
							}

							memcpy(screenPixels + pixelIndex, colorsArray[sprite_p->color], roundf((width * w / texture_p->width) * scale.x) * sizeof(Pixel));

						
						}
					
					}
					*/

				}else{

					for(float y = 0; y < h * scale.y; y++){
						for(float x = 0; x < w * scale.x; x++){

							int texturePixelIndex = getPixelIndexFromTexture(
								*texture_p,
								(int)((x * texture_p->width / sprite_p->body.size.x) / scale.x),
								(int)((y * texture_p->height / sprite_p->body.size.y) / scale.y)
							);

							if(texture_p->data[texturePixelIndex + 3] == 0){
								continue;
							}

							int pixelIndex = getPixelIndex((int)(posX * scale.x + x), (int)(posY * scale.y + y));

							Vec4f color = SPRITE_COLORS[sprite_p->color];

							//printf("%i\n", screenPixels[pixelIndex].r);
							screenPixels[pixelIndex].r = (int)((1 - (1 - color.x * sprite_p->alpha) * (1 - screenPixels[pixelIndex].r / 255)) * 255);
							screenPixels[pixelIndex].g = (int)((1 - (1 - color.y * sprite_p->alpha) * (1 - screenPixels[pixelIndex].g / 255)) * 255);
							screenPixels[pixelIndex].b = (int)((1 - (1 - color.z * sprite_p->alpha) * (1 - screenPixels[pixelIndex].b / 255)) * 255);
							//screenPixels[pixelIndex].g = (int)(color.y * 255);
							//screenPixels[pixelIndex].b = (int)(color.z * 255);
						
						}
					}

				}
				
			}
		}

		//draw text sprites
		for(int i = 0; i < world.textSprites.length; i++){

			TextSprite *textSprite_p = Array_getItemPointerByIndex(&world.textSprites, i);

			Texture texture = textSprite_p->texture;

			if(textSprite_p->body.size.x < 1
			|| textSprite_p->body.size.y < 1){
				continue;
			}

			float posX = (int)(textSprite_p->body.pos.x + world.offset.x);
			float posY = (int)(textSprite_p->body.pos.y + world.offset.y);

			float w = (int)textSprite_p->body.size.x;
			float h = (int)textSprite_p->body.size.y;

			if(posX + w < 0
			|| posX > WIDTH
			|| posY + h < 0
			|| posY > HEIGHT){
				continue;
			}

			if(posX < 0){
				w += posX;
				posX = 0;
			}
			if(posX + w > WIDTH){
				w = WIDTH - posX;
			}

			if(posY < 0){
				h += posY;
				posY = 0;
			}
			if(posY + h > HEIGHT){
				h = HEIGHT - posY;
			}
			
			for(float y = 0; y < h * scale.y; y++){
				for(float x = 0; x < w * scale.x; x++){

					int texturePixelIndex = getPixelIndexFromTexture(
						texture,
						(int)((x * texture.width / textSprite_p->body.size.x) / scale.x),
						(int)((y * texture.height / textSprite_p->body.size.y) / scale.y)
					);

					if(texture.data[texturePixelIndex + 3] == 0){
						continue;
					}

					int pixelIndex = getPixelIndex((int)(posX * scale.x + x), (int)(posY * scale.y + y));

					screenPixels[pixelIndex].r = (int)(textSprite_p->color.x * 255);
					screenPixels[pixelIndex].g = (int)(textSprite_p->color.y * 255);
					screenPixels[pixelIndex].b = (int)(textSprite_p->color.z * 255);
				
				}
			}
		
		}

		for(int i = 0; i < 255; i++){
			world.keys[i].downed = false;
			world.keys[i].downedNoRepeat = false;
		}
		for(int i = 0; i < 16; i++){
			world.actions[i].downed = false;
			world.actions[i].downedNoRepeat = false;
		}

		SDL_BlitSurface(screenSurface, NULL, windowSurface, NULL);

		SDL_UpdateWindowSurface(window);

		endTicks = SDL_GetTicks();

		float delay = 1000 / 60 + (float)startTicks - (float)endTicks;

		//FPS COUNTER
		TextSprite *textSprite_p = Array_getItemPointerByID(&world.textSprites, world.fpsTextID);
		textSprite_p->body.pos.x = 10 -world.offset.x;
		textSprite_p->body.pos.y = 10 -world.offset.y;

		/*
		char fpsString[255] = "";

		//sprintf(fpsString, "ft: , %i", (int)delay);

		Texture_freeData(&textSprite_p->texture);
		textSprite_p->texture = getTextureFromFontAndString_mustFree(world.fonts[0], fpsString);
		textSprite_p->body.size.x = textSprite_p->texture.width;
		textSprite_p->body.size.y = textSprite_p->texture.height;
		*/

		if(delay < 0){
			delay = 0;
		}

		SDL_Delay(delay);

	}

	SDL_Quit();

	return 0;

}
