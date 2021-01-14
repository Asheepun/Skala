#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "openglUtils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_truetype.h"
#include "stb_image.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

/*
 *
 * MÅSTE GÖRE EN KEY RESET FUNKTION SOM AKTIVERAS NÄR STATES BYTS!!!
 *
*/

static World world;
//static Pixel *screenPixels;

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

	bool quit = false;
	SDL_Event e;

	while(!quit){

		//handle events
		while(SDL_PollEvent(&e)){

			if(e.type == SDL_QUIT
			|| e.type == SDL_KEYDOWN
			&& e.key.keysym.sym == SDLK_q){
				quit = true;
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
					World_initLevelState(&world);
				}
				else if(world.currentState == LEVEL_SELECT_STATE){
					World_initLevelSelectState(&world);
				}
				else if(world.currentState == MENU_STATE){
					World_initMenuState(&world);
				}

				world.initCurrentState = false;

			}

			//run current state
			if(world.currentState == LEVEL_STATE
			&& world.fadeTransitionCounter < FADE_TRANSITION_TIME / 2){
				World_levelState(&world);
			}
			else if(world.currentState == LEVEL_SELECT_STATE
			&& world.fadeTransitionCounter < FADE_TRANSITION_TIME / 2){
				World_levelSelectState(&world);
			}
			else if(world.currentState == MENU_STATE){
				World_menuState(&world);
			}

			//reset keys and actions
			for(int i = 0; i < 255; i++){
				world.keys[i].downed = false;
				world.keys[i].downedNoRepeat = false;
			}
			for(int i = 0; i < 16; i++){
				world.actions[i].downed = false;
				world.actions[i].downedNoRepeat = false;
			}

			elapsedTime -= 1000 / 60;

		}

		drawGame();

	}

}

void drawGame(){

	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT);

	//draw sprite layers
	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){
		for(int j = 0; j < world.spriteLayers[i].length; j++){

			Sprite *sprite_p = Array_getItemPointerByIndex(&world.spriteLayers[i], j);

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

				pos.x = floor(sprite_p->body.pos.x);
				pos.y = floor(sprite_p->body.pos.y);

				size.x = floor(sprite_p->body.size.x);
				size.y = floor(sprite_p->body.size.y);

				if(size.x < 1
				|| size.y < 1){
					size = getVec2f(0, 0);
				}

				unsigned int shaderProgram = *((unsigned int *)Array_getItemPointerByIndex(&world.shaderPrograms, 0));

				OpenglUtils_Renderer_drawTexture(world.renderer, pos, size, color, texture.ID, shaderProgram);
			
			}
			else if(sprite_p->type == TEXT_SPRITE){

				pos.x = floor(sprite_p->pos.x);
				pos.y = floor(sprite_p->pos.y);

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

				size.x = floor(imageWidth);
				size.y = floor(imageHeight);

				unsigned int shaderProgram = *((unsigned int *)Array_getItemPointerByIndex(&world.shaderPrograms, 0));

				OpenglUtils_Renderer_drawTexture(world.renderer, pos, size, color, world.renderer.textTextureID, shaderProgram);
			
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

		OpenglUtils_Renderer_drawTexture(world.renderer, pos, size, color, textureID, shaderProgram);

	}

	SDL_GL_SwapWindow(window);

}

int main(int argc, char *argv[]){

	//set up world and game
	World_init(&world);

	setupLevelGrid();

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

	world.currentLevel = 0;

	World_switchToAndInitState(&world, LEVEL_SELECT_STATE);
	//World_switchToAndInitState(&world, LEVEL_STATE);

	//setup SDL
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Scale", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	context = SDL_GL_CreateContext(window);

	SDL_GL_MakeCurrent(window, context);

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

	mainLoop();

	return 0;

}
