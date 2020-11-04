#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "rendering.h"
#include "utils.h"
#include "stb_truetype.h"
#include "text.h"
#include "game.h"
#include "levels.h"

void World_generateLevel1(World *w){

	World_restore(w);

	//World_addObstacle(w, getVec2f(100, 120), getVec2f(20, 20), NONE);
	//World_addObstacle(w, getVec2f(180, 120), getVec2f(20, 40), NONE);

	//World_addObstacle(w, getVec2f(180, 60), getVec2f(1, 20), NONE);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 120), NONE);

	World_addObstacle(w, getVec2f(0, 160), getVec2f(WIDTH, 20), ALL);

	//World_addObstacle(w, getVec2f(100, 80), getVec2f(20, 20), ALL);

	//World_addMovingPoint(w, getVec2f(270, 100), getVec2f(-1, 0), NONE);

	/*
	World_addObstacle(w, getVec2f(0, 20), getVec2f(60, 20), NONE);

	World_addObstacle(w, getVec2f(100, 140), getVec2f(40, 40), NONE);

	World_addObstacle(w, getVec2f(100, 40), getVec2f(40, 40), ALL);

	//World_addObstacle(w, getVec2f(100, -120), getVec2f(40, 40), ALL_FROM_TOP);

	//World_addObstacle(w, getVec2f(100, 100), getVec2f(40, 40), NONE);

	//World_addObstacle(w, getVec2f(150, 150), getVec2f(50, 100), ALL_FROM_TOP);

	//World_addMovingObstacle(w, getVec2f(100, 100), getVec2f(50, 100), getVec2f(-1, 0), ALL);

	//World_addObstacle(w, getVec2f(100, 100), getVec2f(20, 20), NONE, true);

	//World_addObstacle(w, getVec2f(200, 100), getVec2f(20, 20), NONE, true);
	*/

	//World_addSprite(w, getVec2f(80, 80), getVec2f(32, 21), COLOR_WHITE, MOVEMENT_HELP_TEXTURE);

	/*
	World_addObstacle(w, getVec2f(100, 110), getVec2f(50, 60), ALL);

	World_addObstacle(w, getVec2f(30, 110), getVec2f(50, 60), ALL);

	World_addObstacle(w, getVec2f(200, 50), getVec2f(50, 60), NONE);

	*/

}

void World_generateLevel2(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 90), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), ALL);

	World_addObstacle(w, getVec2f(100, 180 - 40), getVec2f(WIDTH - 100, 40), ALL);

	//World_addObstacle(w, getVec2f(240, 180 - 40), getVec2f(80, 40), ALL);

}

void World_generateLevel3(World *w){
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(120, 20), ALL);

	World_addObstacle(w, getVec2f(190, 180 - 20), getVec2f(150, 20), ALL);

}

void World_generateLevel4(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), ALL);

	World_addObstacle(w, getVec2f(220, 180 - 20), getVec2f(100, 20), ALL);

	//World_addSprite(w, getVec2f(80, 180 - 80), getVec2f(20, 20), COLOR_WHITE, "scale-help");

	World_addTextSprite(w, getVec2f(80, 80), "Use the \"X\" key.", 0, COLOR_WHITE);
	
}

void World_generateLevel5(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 140), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(w, getVec2f(120, 180 - 80), getVec2f(200, 60), ALL);

}

void World_generateLevel6(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), ALL);

}

void World_generateLevel7(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(250, 180 - 120), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

	World_addObstacle(w, getVec2f(230, 180 - 60), getVec2f(60, 60), ALL);


}

void World_generateLevel8(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(250, 180 - 120), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

	World_addObstacle(w, getVec2f(270, 180 - 60), getVec2f(1.2, 60), ALL);



}

void World_generateLevel9(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

}

void World_generateLevel10(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 160), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), ALL);

}

void World_generateLevel11(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 160), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

	World_addObstacle(w, getVec2f(220, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(w, getVec2f(240, 0), getVec2f(WIDTH - 250, 10), NONE);

	World_addObstacle(w, getVec2f(WIDTH - 10, 0), getVec2f(10, HEIGHT), NONE);

}

void World_generateLevel12(World *w){
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(w, getVec2f(160, 180 - HEIGHT * 10), getVec2f(60, HEIGHT * 10 - 30), ALL);

}

void World_generateLevel13(World *w){
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(260, 180 - 60), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), ALL);

	//World_addObstacle(w, getVec2f(220, 180 - 40), getVec2f(15, 20), ALL);
	World_addObstacle(w, getVec2f(220, 180 - HEIGHT * 8), getVec2f(15, HEIGHT * 8 - 20), ALL);

}

void World_generateLevel14(World *w){
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addPoint(w, getVec2f(260, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);
	
}

void World_generateLevel15(World *w){
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addPoint(w, getVec2f(260, 180 - 60), ALL);

	//World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);
	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

}

void World_generateLevel16(World *w){
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addPoint(w, getVec2f(260, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(w, getVec2f(100, 180 - 100), getVec2f(100, 80), ALL);

}

void World_generateLevel17(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(w, getVec2f(200, 180 - 100), getVec2f(WIDTH - 200, 80), NONE);

	World_addPoint(w, getVec2f(260, 20), NONE);
	
}

void World_generateLevel18(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 50), getVec2f(WIDTH, 50), NONE);

	World_addObstacle(w, getVec2f(0, 0), getVec2f(WIDTH, 5), NONE);

	World_addObstacle(w, getVec2f(200, 40), getVec2f(WIDTH - 200, HEIGHT - 90), NONE);

	World_addPoint(w, getVec2f(260, 20), NONE);

}

void World_generateLevel19(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(30, 180 - 100), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 50), getVec2f(60, 50), NONE);

	World_addObstacle(w, getVec2f(60, 180 - 20), getVec2f(140, 20), NONE);

	World_addObstacle(w, getVec2f(0, 0), getVec2f(WIDTH, 5), NONE);

	World_addObstacle(w, getVec2f(200, 40), getVec2f(WIDTH - 200, HEIGHT - 40), NONE);

	World_addPoint(w, getVec2f(260, 20), NONE);

}

void World_generateLevel20(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), NONE);

	World_addPoint(w, getVec2f(260, 40), ALL_FROM_TOP);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH, 20), NONE);

}

void World_generateLevel21(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), NONE);

	World_addPoint(w, getVec2f(260, 40), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(100, 20), ALL_FROM_TOP);

}

void World_generateLevel22(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), ALL_FROM_TOP);

	World_addPoint(w, getVec2f(260, 40), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(w, getVec2f(WIDTH - 100, 60), getVec2f(100, HEIGHT - 80), NONE);

	World_addObstacle(w, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

}

void World_generateLevel23(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(WIDTH / 2 - 7, 20), ALL_FROM_TOP);

	World_addPoint(w, getVec2f(WIDTH / 2 - 5, 90), NONE);

	World_addObstacle(w, getVec2f(WIDTH / 2 - 50, 60), getVec2f(100, 20), NONE);

	World_addObstacle(w, getVec2f(WIDTH / 2 - 50, 80), getVec2f(20, 40), NONE);

	World_addObstacle(w, getVec2f(WIDTH / 2 + 30, 80), getVec2f(20, 40), NONE);

}

void World_generateLevel24(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), NONE);

	World_addPoint(w, getVec2f(20, HEIGHT - 40), ALL);

	World_addObstacle(w, getVec2f(0, HEIGHT - 90), getVec2f(WIDTH * 4, 10), ALL_FROM_TOP);

}

void World_generateLevel25(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), NONE);

	World_addPoint(w, getVec2f(40, 20), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH, 20), NONE);

	World_addScaleField(w, getVec2f(200, 0), getVec2f(100, HEIGHT - 20), ALL);
	
}

void World_generateLevel26(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(40, 180 - 100), ALL);

	World_addPoint(w, getVec2f(270, 40), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(60, 20), NONE);

	World_addObstacle(w, getVec2f(220, HEIGHT - 20), getVec2f(100, 20), NONE);

	World_addScaleField(w, getVec2f(60, 0), getVec2f(160, HEIGHT - 20), NONE);

}

void World_generateLevel27(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(40, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 10), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(w, getVec2f(0, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addScaleField(w, getVec2f(150, HEIGHT - 40), getVec2f(40, 40), ALL);

}

void World_generateLevel28(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(40, 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 120), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 60), getVec2f(110, 60), NONE);

	World_addObstacle(w, getVec2f(WIDTH - 80, HEIGHT - 60), getVec2f(80, 60), NONE);

	World_addScaleField(w, getVec2f(WIDTH / 2 - 20, HEIGHT - 110), getVec2f(100, 40), ALL);

}

void World_generateLevel29(World *w){

	World_restore(w);

	World_initPlayer(w, getVec2f(20, 40), NONE);

	World_addPoint(w, getVec2f(20, HEIGHT - 30), NONE);

	World_addObstacle(w, getVec2f(0, 80), getVec2f(100, 60), NONE);

	World_addObstacle(w, getVec2f(50, HEIGHT - 30), getVec2f(50, 50), NONE);

	World_addScaleField(w, getVec2f(160, 60), getVec2f(40, 40), ALL_FROM_TOP);

}
