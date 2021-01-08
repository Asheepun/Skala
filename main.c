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

			world.currentState(&world);

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

	/*
	//draw background
	memset(world.renderer.pixels, 0, world.renderer.width * world.renderer.height * sizeof(Pixel));

	//draw sprites
	for(int i = 0; i < world.spritesLength + world.spritesGaps; i++){
		if(world.sprites[i].active){

			Sprite *sprite_p = &world.sprites[i];
			Texture texture;
			//TextureSliceMap textureSliceMap;

			for(int j = 0; j < world.textures.length; j++){

				Texture *texture_p = Array_getItemPointerByIndex(&world.textures, j);

				if(strcmp(texture_p->name, sprite_p->texture) == 0){
					texture = *texture_p;
				}

			}

			Renderer_drawTextureInSingleColor(&world.renderer,
				sprite_p->body.pos.x,
				sprite_p->body.pos.y,
				sprite_p->body.size.x,
				sprite_p->body.size.y,
				texture,
				//textureSliceMap,
				sprite_p->alpha,
				SPRITE_COLORS[sprite_p->color]
			);

		}
	}

	float startTime = glutGet(GLUT_ELAPSED_TIME);

	for(int i = 0; i < 1; i++){
		Renderer_drawTextureInSingleColor(&world.renderer,
			0,
			0,
			WIDTH,
			HEIGHT,
			*(Texture *)Array_getItemPointerByIndex(&world.textures, 2),
			//textureSliceMap,
			1,
			COLOR_GREEN
		);
	}

	float endTime = glutGet(GLUT_ELAPSED_TIME);

	printf("time: %f\n", endTime - startTime);

	//draw text sprites
	for(int i = 0; i < world.textSprites.length; i++){

		TextSprite *textSprite_p = Array_getItemPointerByIndex(&world.textSprites, i);

		Texture texture = getTextureFromFontAndString_mustFree(world.fonts[textSprite_p->font], textSprite_p->text);

		Renderer_drawTextureInSingleColor(
			&world.renderer,
			textSprite_p->pos.x,
			textSprite_p->pos.y,
			texture.width,
			texture.height,
			texture,
			textSprite_p->alpha,
			textSprite_p->color
		);

		Texture_freeData(&texture);
	
	}

	//draw fade transition
	if(world.fadeTransitionCounter >= 0){

		world.fadeTransitionAlpha = (float)(world.fadeTransitionCounter) / (float)(FADE_TRANSITION_TIME / 3);

		if(world.fadeTransitionCounter <= FADE_TRANSITION_TIME * 2 / 3){
			world.fadeTransitionAlpha = 0;
		}

		if(world.fadeTransitionCounter <= FADE_TRANSITION_TIME / 3){
			world.fadeTransitionAlpha = (float)(FADE_TRANSITION_TIME / 3 - world.fadeTransitionCounter) / (float)(FADE_TRANSITION_TIME / 3);
		}

		world.renderer.fadeOutAlpha = world.fadeTransitionAlpha;

		world.fadeTransitionCounter--;

	}

	//glTranslatef(0, 1, 0);

	glDrawPixels(world.renderer.width, world.renderer.height, GL_RGB, GL_UNSIGNED_BYTE, world.renderer.pixels);

	*/

	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT);

	//draw sprites
	for(int i = 0; i < world.spritesLength + world.spritesGaps; i++){
		if(world.sprites[i].active){

			Sprite *sprite_p = &world.sprites[i];

			OpenglUtils_Texture texture;

			for(int j = 0; j < world.textures.length; j++){

				OpenglUtils_Texture *texture_p = Array_getItemPointerByIndex(&world.textures, j);

				if(strcmp(texture_p->name, sprite_p->texture) == 0){
					texture = *texture_p;
				}

			}

			Vec2f pos = sprite_p->body.pos;
			Vec2f size = sprite_p->body.size;

			Vec2f textureSize = getVec2f(14, 20);

			pos.x = floor(pos.x);
			pos.y = floor(pos.y);

			size.x = floor(size.x);
			size.y = floor(size.y);

			if(size.x < 1
			|| size.y < 1){
				size = getVec2f(0, 0);
			}

			float alpha = sprite_p->alpha;
			Vec4f color = SPRITE_COLORS[sprite_p->color];
			color.w = alpha;

			Mat4f transformations = {
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};

			Mat4f_translate(&transformations, -1, 1, 0);

			Mat4f_translate(&transformations, size.x / (float)WIDTH, -size.y / (float)HEIGHT, 0);

			Mat4f_translate(&transformations, 2 * pos.x / (float)WIDTH, 2 * -pos.y / (float)HEIGHT, 0);

			Mat4f_translate(&transformations, 2 * world.renderOffset.x / (float)WIDTH, 2 * -world.renderOffset.y / (float)HEIGHT, 0);

			Mat4f_scale(&transformations, size.x / (float)WIDTH, size.y / (float)HEIGHT, 1);

			unsigned int shaderProgram = *((unsigned int *)Array_getItemPointerByIndex(&world.shaderPrograms, 0));

			glUseProgram(shaderProgram);

			unsigned int transformationsLocation = glGetUniformLocation(shaderProgram, "transformations");
			glUniformMatrix4fv(transformationsLocation, 1, GL_TRUE, transformations.values);

			unsigned int colorLocation = glGetUniformLocation(shaderProgram, "color");
			glUniform4fv(colorLocation, 1, &color);

			unsigned int textureSizeLocation = glGetUniformLocation(shaderProgram, "textureSize");
			glUniform2fv(textureSizeLocation, 1, &textureSize);

			glBindTexture(GL_TEXTURE_2D, texture.ID);

			glBindVertexArray(world.VAO);

			glDrawArrays(GL_TRIANGLES, 0, 6);

		}
	}

	SDL_GL_SwapWindow(window);

}

int main(int argc, char *argv[]){

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
	Action_addBinding(&world.actions[JUMP_ACTION], SPECIAL_KEY_UP);
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

	World_initLevelSelect(&world);
	//world.currentState = World_levelSelectState;
	world.currentState = World_initLevelState;

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

	/*
	for(int i = 0; i < texturesLength; i++){

		Texture *texture_p = Array_addItem(&world.textures);

		texture_p->name = assets[i];

		char path[255];

		sprintf(path, "assets/sprites/%s.png", texture_p->name);

		Texture_loadData(texture_p, path);
	
	}

	for(int i = 0; i < world.textures.length; i++){

		TextureSliceMap *textureSliceMap_p = Array_addItem(&world.textureSliceMaps);
		Texture texture = *(Texture *)Array_getItemPointerByIndex(&world.textures, i);

		TextureSliceMap_init(textureSliceMap_p, texture);

		textureSliceMap_p->name = texture.name;
		
	}
	*/

	//set up opengl
	glViewport(0, 0, windowWidth, windowHeight);

	//glOrtho(0, 0, windowWidth, windowHeight, 0, 0, 1);

	//glTranslatef(0.375f, 0.375f, 0);

	//set up VBO and VAO
	float vertices[] = {
		1, 1, 0, 		1, 0,
		-1, 1, 0, 		0, 0,
		-1, -1, 0, 		0, 1,

		1, 1, 0, 		1, 0,
		1, -1, 0, 		1, 1,
		-1, -1, 0, 		0, 1,
	};

	glGenBuffers(1, &world.VBO);

	glGenVertexArrays(1, &world.VAO);

	glBindVertexArray(world.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, world.VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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
