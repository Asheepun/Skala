//#include "glad/glad.h"
//#define SDL_DISABLE_IMMINTRIN_H
//#include "SDL2/SDL.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
//#include "geometry.h"
//#include "openglUtils.h"
#define STB_IMAGE_IMPLEMENTATION
//#define STBI_NO_SIMD
//#include "stb_truetype.h"
#include "stb_image.h"
//#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"
#include "audio.h"

void drawGame();

static World world;

SDL_Window *window = NULL;
SDL_GLContext *context = NULL;

size_t time = 0;
size_t lastTime = 0;
size_t deltaTime = 0;
size_t elapsedTime = 0;

int getPixelIndex(int x, int y){
	return windowWidth * y + x;
}

void mainLoop(){

	SDL_Event e;

	while(!world.quit){

		//handle events
		while(SDL_PollEvent(&e)){

			if(e.type == SDL_QUIT
			|| e.type == SDL_KEYDOWN
			&& e.key.keysym.sym == SDLK_q){

				world.quit = true;

				return;

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
				world.keys[SDL_GetScancodeFromKey(e.key.keysym.sym)].upped = true;
			}

		}

		time = SDL_GetTicks();
		deltaTime = time - lastTime;
		lastTime = time;

		elapsedTime += deltaTime;

		while(elapsedTime > 1000 / 60){

			//handle keys
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

			//handle actions
			for(int i = 0; i < 16; i++){

				world.actions[i].down = false;
				world.actions[i].downed = false;
				world.actions[i].downedNoRepeat = false;
				world.actions[i].upped = false;

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
					if(world.keys[world.actions[i].bindings[j]].upped){
						world.actions[i].upped = true;
					}
				}
			}

			//handle fade transition
			world.fadeTransitionCounter--;

			//switch state when screen
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
			}

			//reset keys and actions
			for(int i = 0; i < 255; i++){
				world.keys[i].downed = false;
				world.keys[i].downedNoRepeat = false;
				world.keys[i].upped = false;
			}
			for(int i = 0; i < 16; i++){
				world.actions[i].downed = false;
				world.actions[i].downedNoRepeat = false;
				world.actions[i].upped = false;
			}

			freeTmpArrays();

			elapsedTime -= 1000 / 60;

		}

		drawGame();

	}

}

void drawGame(){

	glClearColor(COLOR_BLACK.x, COLOR_BLACK.y, COLOR_BLACK.z, 1);

	glClear(GL_COLOR_BUFFER_BIT);

	//draw sprite layers
	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){

		/*
		if(i == GAME_LAYER_PARTICLES){

			continue;
		}
		*/

		for(int j = 0; j < world.spriteLayers[i].length; j++){

			//Sprite *sprite_p = Array_getItemPointerByIndex(&world.spriteLayers[i], j);
			Sprite *sprite_p = IndexSafeArray_getItemPointer(&world.spriteLayers[i], j);

			if(sprite_p == NULL){
				continue;
			}

			if(sprite_p->alpha <= 0.001){
				continue;
			}

			Vec4f color = sprite_p->color;
			color.w = sprite_p->alpha;

			Vec2f pos;
			Vec2f size;

			if(sprite_p->type == REGULAR_SPRITE){

				OpenglUtils_Texture texture;

				for(int k = 0; k < world.textures.length; k++){

					OpenglUtils_Texture *texture_p = Array_getItemPointerByIndex(&world.textures, k);

					if(strcmp(texture_p->name, sprite_p->texture) == 0){
						texture = *texture_p;
						break;
					}

				}

				pos.x = (sprite_p->body.pos.x);
				pos.y = (sprite_p->body.pos.y);

				size.x = round(sprite_p->body.size.x);
				size.y = round(sprite_p->body.size.y);

				Vec4f color = sprite_p->color;
				color.w = sprite_p->alpha;

				if(sprite_p->body.size.x < 1
				|| sprite_p->body.size.y < 1){
					size = getVec2f(0, 0);
				}

				unsigned int shaderProgram = *((unsigned int *)Array_getItemPointerByIndex(&world.shaderPrograms, 0));

				Mat4f transformations = OpenglUtils_Renderer_getBodyTransformations(world.renderer, pos, size);

				glUseProgram(shaderProgram);

				unsigned int transformationsLocation = glGetUniformLocation(shaderProgram, "transformations");
				glUniformMatrix4fv(transformationsLocation, 1, GL_TRUE, transformations.values);

				unsigned int colorLocation = glGetUniformLocation(shaderProgram, "color");
				glUniform4fv(colorLocation, 1, (GLfloat *)&color);

				unsigned int facingLocation = glGetUniformLocation(shaderProgram, "facing");
				glUniform1iv(facingLocation, 1, (GLint *)&sprite_p->facing);

				glBindTexture(GL_TEXTURE_2D, texture.ID);

				glBindVertexArray(world.renderer.VAO);

				glDrawArrays(GL_TRIANGLES, 0, 6);
			
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

				char *imageData = getImageDataFromFontAndString_mustFree(font, sprite_p->text, &imageWidth, &imageHeight);

				glBindTexture(GL_TEXTURE_2D, world.renderer.textTextureID);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
				
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				free(imageData);

				size.x = round(imageWidth);
				size.y = round(imageHeight);

				unsigned int shaderProgram = *((unsigned int *)Array_getItemPointerByIndex(&world.shaderPrograms, 0));

				OpenglUtils_Renderer_drawTexture(world.renderer, pos, size, color, 1, getVec2f(0, 0), world.renderer.textTextureID, shaderProgram);
			
			}
		
		}
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

		Vec4f color = { 0, 0, 0, 1 };
		color.w = fadeTransitionAlpha;

		unsigned int textureID = 4;//4 is obstacle texture

		unsigned int shaderProgram = *((unsigned int *)Array_getItemPointerByIndex(&world.shaderPrograms, 0));

		OpenglUtils_Renderer_drawTexture(world.renderer, pos, size, color, 1, getVec2f(0, 0), textureID, shaderProgram);

	}

	SDL_GL_SwapWindow(window);

}

int main(int argc, char *argv[]){

	//set up world and game
	World_init(&world);

	initTmpArrays();

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
	Action_addBinding(&world.actions[JUMP_ACTION], SDL_SCANCODE_UP);
	Action_addBinding(&world.actions[JUMP_ACTION], SDL_SCANCODE_W);
	Action_addBinding(&world.actions[JUMP_ACTION], SDL_SCANCODE_SPACE);
	Action_addBinding(&world.actions[SCALE_ACTION], SDL_SCANCODE_X);
	Action_addBinding(&world.actions[SCALE_ACTION], SDL_SCANCODE_J);
	Action_addBinding(&world.actions[DO_ACTION], SDL_SCANCODE_X);
	Action_addBinding(&world.actions[DO_ACTION], SDL_SCANCODE_J);
	Action_addBinding(&world.actions[DO_ACTION], SDL_SCANCODE_SPACE);
	Action_addBinding(&world.actions[BACK_ACTION], SDL_SCANCODE_ESCAPE);
	Action_addBinding(&world.actions[MENU_ACTION], SDL_SCANCODE_ESCAPE);
	Action_addBinding(&world.actions[RESTART_ACTION], SDL_SCANCODE_R);

	world.currentLevel = "bug-testing-level";

	World_switchToAndInitState(&world, LEVEL_HUB_STATE);
	//World_switchToAndInitState(&world, LEVEL_STATE);

	//setup SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("Scale", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	context = SDL_GL_CreateContext(window);

	SDL_GL_MakeCurrent(window, context);

	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
		printf("ERROR LOADING WITH GLAD\n");
	}

	//set up opengl
	glViewport(0, 0, windowWidth, windowHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	OpenglUtils_Renderer_init(&world.renderer, WIDTH, HEIGHT);

	//load shaders
	unsigned int vertexShader = getCompiledShader("shaders/vertex-shader.glsl", GL_VERTEX_SHADER);

	unsigned int fragmentShader = getCompiledShader("shaders/fragment-shader.glsl", GL_FRAGMENT_SHADER);

	Array_init(&world.shaderPrograms, sizeof(unsigned int));

	unsigned int *shaderProgram = Array_addItem(&world.shaderPrograms);

	*shaderProgram = glCreateProgram();

	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);

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

		OpenglUtils_Texture *texture = Array_addItem(&world.textures);

		texture->name = assets[i];

		char path[255];

		sprintf(path, "assets/sprites/%s.png", assets[i]);

		int imageWidth, imageHeight, nrChannels;

		unsigned char *imageData = stbi_load(path, &imageWidth, &imageHeight, &nrChannels, 0);

		if(!imageData){
			printf("Could not load image: %s\n", path);
		}

		glGenTextures(1, &texture->ID);

		glBindTexture(GL_TEXTURE_2D, texture->ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(imageData);
	
	}

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

	//make star background texture
	{

		OpenglUtils_Texture *texture_p = Array_addItem(&world.textures);

		texture_p->name = "star-background";

		int width = 5000;
		int height = HEIGHT * 4;

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

		glGenTextures(1, &texture_p->ID);

		glBindTexture(GL_TEXTURE_2D, texture_p->ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		free(data);
		
	}

	mainLoop();

	//quit the game
	SaveData_write(&world.saveData);

	return 0;

}
