//#include "glad/glad.h"
//#define SDL_DISABLE_IMMINTRIN_H
//#include "SDL2/SDL.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
//#include "geometry.h"
//#include "openglUtils.h"
//#define STB_IMAGE_IMPLEMENTATION
//#define STBI_NO_SIMD
//#include "stb_truetype.h"
//#include "stb_image.h"
//#include "text.h"
//#include "utils.h"
#include "engine/engine.h"
#include "engine/renderer2d.h"
#include "engine/array.h"
#include "game.h"
#include "levels.h"
//#include "audio.h"

static World world;

Renderer2D_ShaderProgram singleColorTextureShaderProgram;

void Engine_start(){

	//set up world and game
	World_init(&world);

	initTmpArrays();

	for(int i = 0; i < 16; i++){
		Action_init(&world.actions[i]);
	}

	Action_addBinding(&world.actions[UP_ACTION], ENGINE_KEY_UP);
	Action_addBinding(&world.actions[UP_ACTION], ENGINE_KEY_W);
	Action_addBinding(&world.actions[DOWN_ACTION], ENGINE_KEY_DOWN);
	Action_addBinding(&world.actions[DOWN_ACTION], ENGINE_KEY_S);
	Action_addBinding(&world.actions[LEFT_ACTION], ENGINE_KEY_LEFT);
	Action_addBinding(&world.actions[LEFT_ACTION], ENGINE_KEY_A);
	Action_addBinding(&world.actions[RIGHT_ACTION], ENGINE_KEY_RIGHT);
	Action_addBinding(&world.actions[RIGHT_ACTION], ENGINE_KEY_D);
	Action_addBinding(&world.actions[JUMP_ACTION], ENGINE_KEY_UP);
	Action_addBinding(&world.actions[JUMP_ACTION], ENGINE_KEY_W);
	Action_addBinding(&world.actions[JUMP_ACTION], ENGINE_KEY_SPACE);
	Action_addBinding(&world.actions[SCALE_ACTION], ENGINE_KEY_X);
	Action_addBinding(&world.actions[SCALE_ACTION], ENGINE_KEY_J);
	Action_addBinding(&world.actions[DO_ACTION], ENGINE_KEY_X);
	Action_addBinding(&world.actions[DO_ACTION], ENGINE_KEY_J);
	Action_addBinding(&world.actions[DO_ACTION], ENGINE_KEY_SPACE);
	Action_addBinding(&world.actions[BACK_ACTION], ENGINE_KEY_ESCAPE);
	Action_addBinding(&world.actions[MENU_ACTION], ENGINE_KEY_ESCAPE);
	Action_addBinding(&world.actions[RESTART_ACTION], ENGINE_KEY_R);

	world.currentLevel = "bug-testing-level";

	World_switchToAndInitState(&world, LEVEL_HUB_STATE);

	//set up engine and renderer
	Engine_setWindowTitle("Skala");

	Engine_setWindowSize(WIDTH * 2.5, HEIGHT * 2.5);
	Engine_centerWindow();
	
	Renderer2D_init(&world.renderer, WIDTH, HEIGHT);

	{
		Renderer2D_ShaderPathTypePair shaderFiles[] = {
			"shaders/texture-vertex-shader.glsl", RENDERER2D_VERTEX_SHADER,
			"shaders/single-color-texture-fragment-shader.glsl", RENDERER2D_FRAGMENT_SHADER,
		};

		int shaderFilesLength = sizeof(shaderFiles) / sizeof(Renderer2D_ShaderPathTypePair);

		Renderer2D_ShaderProgram_init(&singleColorTextureShaderProgram, "single-color-texture-shader", shaderFiles, shaderFilesLength);
	
	}

	//World_switchToAndInitState(&world, LEVEL_STATE);

	//load textures
	char *assets[] = {
		"player",
		"point",
		"obstacle",
		"movement-help",
		"scale-help",
		"menu-background",
		"level",
		"door",
		"door-key",
		"level-door",
		"level-door-completed",
		"level-door-with-key",

		//furniture
		"furniture/hat-shelf",
		"furniture/coat-hanger",
		"furniture/living-room-lamp",
		"furniture/sofa",
		"furniture/book-shelf",
		"furniture/stove",
		"furniture/kitchen-table",
		"furniture/kitchen-shelf",
		"furniture/bed",
		"furniture/bedside-table",
		"furniture/washing-machine",
		"furniture/wash-basket",
		"furniture/lamp-post",
		"furniture/bench",

		"furniture/lamp-1",
		"furniture/lamp-2",
		"furniture/lamp-3",
	};

	int texturesLength = sizeof(assets) / sizeof(char *);

	for(int i = 0; i < texturesLength; i++){

		Renderer2D_Texture *texture_p = Array_addItem(&world.textures);

		char path[255];

		sprintf(path, "assets/sprites/%s.png", assets[i]);

		Renderer2D_Texture_initFromFile(texture_p, path);

		texture_p->name = assets[i];

	}

	/*
	//load audio
	char *soundAssets[] = {
		"player-jump",
		"player-land",
		"enter-level-door",
		"pickup-star",
		"pickup-key",
		"open-door",
		"begin-scaling",
		"end-scaling",
		"scaling",
	};

	int soundAssetsLength = sizeof(soundAssets) / sizeof(char *);

	initAudio(soundAssets, soundAssetsLength);

	setVolume(0.5);
	*/

	//make star background texture
	{

		Renderer2D_Texture *texture_p = Array_addItem(&world.textures);

		texture_p->name = "star-background";

		int width = 5000;
		int height = HEIGHT * 8;

		unsigned char *data = malloc((width * height) * sizeof(char) * 4);
		memset(data, 0, (width * height) * sizeof(char) * 4);

		int x = 1;
		int a = 65521;
		int c = 0;
		int m = 17364;

		for(int i = 0; i < 200000; i++){

			x = (a * x + c) % m;
			float r = (float)x;
			r /= m;

			Vec2f pos;
			pos.x = (int)(r * width);

			x = (a * x + c) % m;
			r = (float)x;
			r /= m;

			pos.y = (int)(r * height);

			int index = width * pos.y + pos.x;

			data[index * 4] = 255;
			data[index * 4 + 1] = 255;
			data[index * 4 + 2] = 255;
			data[index * 4 + 3] = 255;

		}

		Renderer2D_Texture_init(texture_p, "star-background", data, width, height);

		free(data);
		
	}


	printf("hello there, we meet again\n");

}

void Engine_update(float deltaTime){

	if(ENGINE_KEYS[ENGINE_KEY_Q].down){
		Engine_quit();
	}

	if(ENGINE_KEYS[ENGINE_KEY_F].downed){
		Engine_toggleFullscreen();
	}

	//handle actions
	for(int i = 0; i < 16; i++){

		world.actions[i].down = false;
		world.actions[i].downed = false;
		world.actions[i].downedNoRepeat = false;
		world.actions[i].upped = false;

		for(int j = 0; j < world.actions[i].bindingsLength; j++){
			if(ENGINE_KEYS[world.actions[i].bindings[j]].down){
				world.actions[i].down = true;
			}
			if(ENGINE_KEYS[world.actions[i].bindings[j]].downed){
				world.actions[i].downed = true;
			}
			if(ENGINE_KEYS[world.actions[i].bindings[j]].upped){
				world.actions[i].upped = true;
			}
		}
	}

	//handle fade transition
	world.fadeTransitionCounter--;

	//switch state when screen is black
	if(world.fadeTransitionCounter == FADE_TRANSITION_TIME / 2){
		world.currentState = world.nextStateAfterTransition;

		world.initCurrentState = true;
	}

	//init current state if needed
	if(world.initCurrentState){

		if(world.currentState == LEVEL_STATE){
			World_initLevel(&world);
		}
		if(world.currentState == LEVEL_HUB_STATE){
			World_initLevelHub(&world);
		}
		else if(world.currentState == MENU_STATE){
			World_initMenu(&world);
		}
		else if(world.currentState == CREDITS_STATE){
			World_initCredits(&world);
		}

		world.initCurrentState = false;

	}

	//run current state
	if((world.currentState == LEVEL_STATE
	|| world.currentState == LEVEL_HUB_STATE)
	&& world.fadeTransitionCounter < FADE_TRANSITION_TIME / 2){
		World_levelState(&world);
	}
	else if(world.currentState == MENU_STATE){
		World_menuState(&world);
	}else if(world.currentState == CREDITS_STATE){
		World_creditsState(&world);
	}

	//reset actions
	for(int i = 0; i < 16; i++){
		world.actions[i].downed = false;
		world.actions[i].downedNoRepeat = false;
		world.actions[i].upped = false;
	}

	freeTmpArrays();

}

void Engine_draw(){

	Renderer2D_updateDrawSize(&world.renderer, clientWidth, clientHeight);

	Renderer2D_clear(&world.renderer);

	Renderer2D_setShaderProgram(&world.renderer, world.renderer.colorShaderProgram);

	Renderer2D_beginRectangle(&world.renderer, -world.renderer.offset.x, -world.renderer.offset.y, WIDTH, HEIGHT);

	Renderer2D_Color color = COLOR_BLACK;
	float alpha = 1.0;

	Renderer2D_supplyUniform(&world.renderer, &alpha, "alpha", RENDERER2D_UNIFORM_TYPE_FLOAT);
	Renderer2D_supplyUniform(&world.renderer, &color, "color", RENDERER2D_UNIFORM_TYPE_COLOR);

	Renderer2D_drawRectangle(&world.renderer);

	Renderer2D_setShaderProgram(&world.renderer, singleColorTextureShaderProgram);

	//draw sprite layers
	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){

		for(int j = 0; j < world.spriteLayers[i].length; j++){

			Sprite *sprite_p = IndexSafeArray_getItemPointer(&world.spriteLayers[i], j);

			if(sprite_p == NULL){
				continue;
			}

			if(sprite_p->alpha <= 0.001){
				continue;
			}

			Renderer2D_Color color = sprite_p->color;
			float alpha = sprite_p->alpha;

			Vec2f pos;
			Vec2f size;

			if(sprite_p->type == REGULAR_SPRITE){

				Renderer2D_Texture texture;

				for(int k = 0; k < world.textures.length; k++){

					Renderer2D_Texture *texture_p = Array_getItemPointerByIndex(&world.textures, k);

					if(strcmp(texture_p->name, sprite_p->texture) == 0){
						texture = *texture_p;
						break;
					}

				}

				pos.x = (sprite_p->body.pos.x);
				pos.y = (sprite_p->body.pos.y);

				size.x = round(sprite_p->body.size.x);
				size.y = round(sprite_p->body.size.y);

				if(pos.x + size.x < -world.renderer.offset.x
				|| pos.y + size.y < -world.renderer.offset.y
				|| pos.x > -world.renderer.offset.x + WIDTH
				|| pos.y > -world.renderer.offset.y + HEIGHT){
					continue;
				}

				if(sprite_p->body.size.x < 1
				|| sprite_p->body.size.y < 1){
					size = getVec2f(0, 0);
				}

				int facing = sprite_p->facing;

				Renderer2D_beginRectangle(&world.renderer, pos.x, pos.y, size.x, size.y);

				Renderer2D_setTexture(&world.renderer, texture);

				Renderer2D_supplyUniform(&world.renderer, &facing, "facing", RENDERER2D_UNIFORM_TYPE_INT);

				Renderer2D_supplyUniform(&world.renderer, &alpha, "alpha", RENDERER2D_UNIFORM_TYPE_FLOAT);
				Renderer2D_supplyUniform(&world.renderer, &color, "color", RENDERER2D_UNIFORM_TYPE_COLOR);

				Renderer2D_drawRectangle(&world.renderer);
			
			}
			else if(sprite_p->type == TEXT_SPRITE){

				pos.x = round(sprite_p->pos.x);
				pos.y = round(sprite_p->pos.y);

				int imageWidth, imageHeight;

				Font font;
				for(int k = 0; k < world.fonts.length; k++){

					Font *font_p = Array_getItemPointerByIndex(&world.fonts, k);

					if(strcmp(font_p->name, sprite_p->fontName) == 0){
						font = *font_p;
						break;
					}
				
				}

				char *ptr;
				int fontSize;
				fontSize = strtol(sprite_p->fontName + 5, &ptr, 10);

				Renderer2D_beginText(&world.renderer, sprite_p->text, pos.x, pos.y, fontSize, font);

				Renderer2D_supplyUniform(&world.renderer, &color, "color", RENDERER2D_UNIFORM_TYPE_COLOR);
				Renderer2D_supplyUniform(&world.renderer, &alpha, "alpha", RENDERER2D_UNIFORM_TYPE_FLOAT);
				Renderer2D_supplyUniform(&world.renderer, &sprite_p->facing, "facing", RENDERER2D_UNIFORM_TYPE_INT);

				Renderer2D_drawRectangle(&world.renderer);
			
			}
		
		}
	}

	if(world.endingFlashAlpha > 0){
		
		Renderer2D_setShaderProgram(&world.renderer, world.renderer.colorShaderProgram);

		Renderer2D_beginRectangle(&world.renderer, -world.renderer.offset.x, -world.renderer.offset.y, WIDTH, HEIGHT);

		color = COLOR_WHITE;
		alpha = world.endingFlashAlpha;

		Renderer2D_supplyUniform(&world.renderer, &alpha, "alpha", RENDERER2D_UNIFORM_TYPE_FLOAT);
		Renderer2D_supplyUniform(&world.renderer, &color, "color", RENDERER2D_UNIFORM_TYPE_COLOR);

		Renderer2D_drawRectangle(&world.renderer);

	}

	//draw fade transition
	if(world.fadeTransitionCounter > 0){

		float fadeTransitionAlpha = 3 * ((float)(FADE_TRANSITION_TIME - world.fadeTransitionCounter) / (float)(FADE_TRANSITION_TIME));

		if(world.fadeTransitionCounter <= FADE_TRANSITION_TIME * 2 / 3){
			fadeTransitionAlpha = 1;
		}

		if(world.fadeTransitionCounter <= FADE_TRANSITION_TIME / 3){
			fadeTransitionAlpha = 3 * ((float)(world.fadeTransitionCounter) / (float)(FADE_TRANSITION_TIME));
		}

		Vec2f pos = { -world.renderer.offset.x, -world.renderer.offset.y };
		Vec2f size = { WIDTH, HEIGHT };

		Renderer2D_setShaderProgram(&world.renderer, world.renderer.colorShaderProgram);

		Renderer2D_beginRectangle(&world.renderer, pos.x, pos.y, size.x, size.y);

		color = COLOR_BLACK;
		alpha = fadeTransitionAlpha;

		Renderer2D_supplyUniform(&world.renderer, &alpha, "alpha", RENDERER2D_UNIFORM_TYPE_FLOAT);
		Renderer2D_supplyUniform(&world.renderer, &color, "color", RENDERER2D_UNIFORM_TYPE_COLOR);

		Renderer2D_drawRectangle(&world.renderer);

	}

}

void Engine_finnish(){

	SaveData_write(&world.saveData);

}
