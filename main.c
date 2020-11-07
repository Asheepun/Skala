#include "miniglut/miniglut.h"
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

/**
 *
 * MÅSTE GÖRE EN KEY RESET FUNKTION SOM AKTIVERAS NÄR STATES BYTS!!!
 *
 *
 */

static World world;
//static Pixel *screenPixels;

size_t time = 0;
size_t lastTime = 0;
size_t deltaTime = 0;
size_t elapsedTime = 0;

int getPixelIndex(int x, int y){
	return windowWidth * y + x;
}

void mainLoop(){

	time = glutGet(GLUT_ELAPSED_TIME);
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

	if(windowWidth != glutGet(GLUT_WINDOW_WIDTH)
	|| windowHeight != glutGet(GLUT_WINDOW_HEIGHT)){

		windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

		Renderer_setSize(&world.renderer, windowWidth, windowWidth * 9 / 16);

		world.renderer.scale.x = world.renderer.width / WIDTH;
		world.renderer.scale.y = world.renderer.height / HEIGHT;

	}

	glutPostRedisplay();

}

void drawGame(){

	//draw background
	memset(world.renderer.pixels, 0, world.renderer.width * world.renderer.height * sizeof(Pixel));

	//draw sprites
	for(int i = 0; i < world.spritesLength + world.spritesGaps; i++){
		if(world.sprites[i].active){

			Sprite *sprite_p = &world.sprites[i];
			Texture texture;

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
				sprite_p->alpha,
				SPRITE_COLORS[sprite_p->color]
			);

		}
	}

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

		Texture texture;

		for(int j = 0; j < world.textures.length; j++){

			Texture *texture_p = Array_getItemPointerByIndex(&world.textures, j);

			if(strcmp(texture_p->name, "obstacle") == 0){
				texture = *texture_p;
			}

		}

		/*
		for(int y = 0; y < world.renderer.height; y++){
			for(int x = 0; x < world.renderer.width; x++){

				int pixelIndex = Renderer_getPixelIndex(&world.renderer, x, y);

				world.renderer.pixels[pixelIndex].r *= world.fadeTransitionAlpha;
				world.renderer.pixels[pixelIndex].g *= world.fadeTransitionAlpha;
				world.renderer.pixels[pixelIndex].b *= world.fadeTransitionAlpha;

			}
		}
		*/

		world.fadeTransitionCounter--;

	}

	//glTranslatef(0, 1, 0);

	glDrawPixels(world.renderer.width, world.renderer.height, GL_RGB, GL_UNSIGNED_BYTE, world.renderer.pixels);

	glutSwapBuffers();

}

void handleKeyboardDownEvents(unsigned char key, int x, int y){

	world.keys[key].down = true;
	world.keys[key].downed = true;
	world.keys[key].downedNoRepeat = true;

	if(key == *"q"){
		exit(0);
	}

}

void handleKeyboardUpEvents(unsigned char key, int x, int y){

	world.keys[key].down = false;

}

int main(int argc, char *argv[]){

	World_init(&world);

	setupLevelGrid();

	for(int i = 0; i < 16; i++){
		Action_init(&world.actions[i]);
	}

	Action_addBinding(&world.actions[UP_ACTION], SPECIAL_KEY_UP);
	Action_addBinding(&world.actions[UP_ACTION], *"w");
	Action_addBinding(&world.actions[DOWN_ACTION], SPECIAL_KEY_DOWN);
	Action_addBinding(&world.actions[DOWN_ACTION], *"s");
	Action_addBinding(&world.actions[LEFT_ACTION], SPECIAL_KEY_LEFT);
	Action_addBinding(&world.actions[LEFT_ACTION], *"a");
	Action_addBinding(&world.actions[RIGHT_ACTION], SPECIAL_KEY_RIGHT);
	Action_addBinding(&world.actions[RIGHT_ACTION], *"d");
	Action_addBinding(&world.actions[JUMP_ACTION], SPECIAL_KEY_UP);
	Action_addBinding(&world.actions[JUMP_ACTION], *"w");
	Action_addBinding(&world.actions[JUMP_ACTION], *" ");
	Action_addBinding(&world.actions[SCALE_ACTION], *"x");
	Action_addBinding(&world.actions[SCALE_ACTION], *"j");
	Action_addBinding(&world.actions[DO_ACTION], *"x");
	Action_addBinding(&world.actions[DO_ACTION], *"j");
	Action_addBinding(&world.actions[DO_ACTION], *" ");
	Action_addBinding(&world.actions[BACK_ACTION], (char)27);//ESCAPE
	Action_addBinding(&world.actions[MENU_ACTION], (char)27);//ESCAPE

	world.currentLevel = 0;

	World_initLevelSelect(&world);
	world.currentState = World_levelSelectState;
	//world.currentState = World_initLevelState;

	Renderer_setSize(&world.renderer, windowWidth, windowHeight);
	world.renderer.scale = getVec2f(windowWidth / WIDTH, windowHeight / HEIGHT);

	Renderer_testSingleThreadDrawSizeLimit(&world.renderer);

	initDrawingThreads();

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

		Texture *texture_p = Array_addItem(&world.textures);

		texture_p->name = assets[i];

		char path[255];

		sprintf(path, "assets/sprites/%s.png", texture_p->name);

		Texture_loadData(texture_p, path);
	
	}

	int window;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(400, 200);

	glutCreateWindow("opengl-window");

	glutIdleFunc(mainLoop);
	glutDisplayFunc(drawGame);
	glutKeyboardFunc(handleKeyboardDownEvents);
	glutKeyboardUpFunc(handleKeyboardUpEvents);
	glutSpecialFunc(handleKeyboardDownEvents);
	glutSpecialUpFunc(handleKeyboardUpEvents);

	glutFullScreen();

	glutMainLoop();

	return 0;

}
