void World_generateLevel1(World *w){

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), ALL);

	World_addPoint(w, getVec2f(270, 60), ALL, false);

	//World_addMovingPoint(w, getVec2f(270, 100), getVec2f(-1, 0), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(60, 20), NONE, false);

	World_addObstacle(w, getVec2f(100, 140), getVec2f(40, 40), NONE, false);

	World_addObstacle(w, getVec2f(100, 40), getVec2f(40, 40), ALL, false);

	//World_addObstacle(w, getVec2f(100, -120), getVec2f(40, 40), ALL_FROM_TOP, false);

	//World_addObstacle(w, getVec2f(100, 100), getVec2f(40, 40), NONE, false);

	//World_addObstacle(w, getVec2f(150, 150), getVec2f(50, 100), ALL_FROM_TOP, false);

	//World_addMovingObstacle(w, getVec2f(100, 100), getVec2f(50, 100), getVec2f(-1, 0), ALL, false);

	//World_addObstacle(w, getVec2f(100, 100), getVec2f(20, 20), NONE, true);

	//World_addObstacle(w, getVec2f(200, 100), getVec2f(20, 20), NONE, true);

	World_addSprite(w, getVec2f(80, 80), getVec2f(32, 21), COLOR_WHITE, MOVEMENT_HELP_TEXTURE);

	/*
	World_addObstacle(w, getVec2f(100, 110), getVec2f(50, 60), ALL, false);

	World_addObstacle(w, getVec2f(30, 110), getVec2f(50, 60), ALL, false);

	World_addObstacle(w, getVec2f(200, 50), getVec2f(50, 60), NONE, false);

	*/

}

void World_generateLevel2(World *w){

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), ALL);

	World_addPoint(w, getVec2f(270, 90), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), ALL, false);

	World_addObstacle(w, getVec2f(100, 40), getVec2f(60, 40), ALL, false);

	World_addObstacle(w, getVec2f(240, 40), getVec2f(80, 40), ALL, false);

}

void World_generateLevel3(World *w){

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), ALL, false);

	World_addObstacle(w, getVec2f(220, 20), getVec2f(100, 20), ALL, false);

	World_addSprite(w, getVec2f(80, 80), getVec2f(20, 20), COLOR_WHITE, SCALE_HELP_TEXTURE);
	
}

void World_generateLevel4(World *w){

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 140), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 20), ALL, false);

	World_addObstacle(w, getVec2f(120, 80), getVec2f(200, 80), ALL, false);

}

void World_generateLevel5(World *w){

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), ALL, false);

}

void World_generateLevel6(World *w){

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), NONE, false);

}

void World_generateLevel7(World *w){

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 160), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), ALL, false);

}

void World_generateLevel8(World *w){
	
	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 20), ALL, false);

	World_addObstacle(w, getVec2f(160, HEIGHT * 10), getVec2f(60, HEIGHT * 10 - 30), ALL, false);

}

void World_generateLevel9(World *w){
	
	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(260, 60), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 20), ALL, false);

	World_addObstacle(w, getVec2f(220, HEIGHT * 8), getVec2f(15, HEIGHT * 8), ALL, false);

}

void World_generateLevel10(World *w){
	
	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 20), ALL, false);

	World_addObstacle(w, getVec2f(180, HEIGHT * 8), getVec2f(50, HEIGHT * 8), ALL, false);
	
}

void World_generateLevel11(World *w){
	
	World_init(w);

	World_initPlayer(w, getVec2f(60, 100), ALL);

	World_addPoint(w, getVec2f(260, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), NONE, false);

}

void World_generateLevel12(World *w){
	
	World_init(w);

	World_initPlayer(w, getVec2f(60, 100), ALL);

	World_addPoint(w, getVec2f(260, 60), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), NONE, false);

}

void World_generateLevel13(World *w){

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), ALL);

	World_addPoint(w, getVec2f(270, 140), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 20), ALL, false);

	World_addObstacle(w, getVec2f(120, 80), getVec2f(200, 80), ALL, false);


}

void World_generateLevel14(World *w){
	
	World_init(w);

	World_initPlayer(w, getVec2f(60, 80), ALL);

	World_addPoint(w, getVec2f(260, 140), NONE, false);

	World_addObstacle(w, getVec2f(0, 50), getVec2f(WIDTH, 50), NONE, false);

	World_addObstacle(w, getVec2f(220, 100), getVec2f(100, 150), NONE, false);

}

void World_generateLevel15(World *w){
	
	World_init(w);

	World_initPlayer(w, getVec2f(60, 80), ALL);

	World_addPoint(w, getVec2f(260, 170), NONE, false);

	World_addObstacle(w, getVec2f(0, 50), getVec2f(WIDTH, 50), NONE, false);

	World_addObstacle(w, getVec2f(220, 150), getVec2f(100, 150), NONE, false);

}

void{
	
	World_init(w);

	World_initPlayer(w, getVec2f(40, 80), ALL);

	World_addPoint(w, getVec2f(260, 170), NONE, false);

	World_addObstacle(w, getVec2f(0, 50), getVec2f(60, 50), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 50), NONE, false);

	World_addObstacle(w, getVec2f(220, 150), getVec2f(100, 150), NONE, false);

}

void{
	
	World_init(w);

	//w->origin.y = 0;

	World_initPlayer(w, getVec2f(60, -80 + HEIGHT), NONE);

	World_addPoint(w, getVec2f(260, -30 + HEIGHT), NONE, false);

	World_addObstacle(w, getVec2f(0, -130), getVec2f(WIDTH, 50), ALL_FROM_TOP, false);

}

void{
	
	World_init(w);

	//w->origin.y = 0;

	World_initPlayer(w, getVec2f(60, -80 + HEIGHT), NONE);

	World_addPoint(w, getVec2f(260, -30), ALL_FROM_TOP, false);

	World_addObstacle(w, getVec2f(0, -130 + HEIGHT), getVec2f(WIDTH, 50), NONE, false);

}

void World_generateLevel16(World *w){
	
	World_init(w);

	//w->origin.y = 0;

	World_initPlayer(w, getVec2f(WIDTH / 2, 80), ALL_FROM_TOP);

	World_addPoint(w, getVec2f(WIDTH / 2 - 5, -100 + HEIGHT), NONE, false);

	World_addObstacle(w, getVec2f(WIDTH / 2 - 50, -60 + HEIGHT), getVec2f(100, 20), NONE, false);
	World_addObstacle(w, getVec2f(WIDTH / 2 - 50, -60 + HEIGHT), getVec2f(20, 60), NONE, false);
	World_addObstacle(w, getVec2f(WIDTH / 2 + 30, -60 + HEIGHT), getVec2f(20, 60), NONE, false);

}

void{
	
	World_init(w);

	World_initPlayer(w, getVec2f(40, 80), ALL_FROM_TOP);

	World_addPoint(w, getVec2f(30, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 120), getVec2f(WIDTH - 40, 20), NONE, false);

}

void{
	
	World_init(w);

	World_initPlayer(w, getVec2f(40, 80), NONE);

	World_addPoint(w, getVec2f(290, 60), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(80, 20), NONE, false);

	World_addObstacle(w, getVec2f(250, HEIGHT), getVec2f(20, HEIGHT), NONE, false);

}

void{
	
	World_init(w);

	World_initPlayer(w, getVec2f(40, 80), NONE);

	World_addPoint(w, getVec2f(290, 60), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(80, 20), NONE, false);

	World_addObstacle(w, getVec2f(250, 100), getVec2f(20, 100), NONE, false);

	World_addObstacle(w, getVec2f(190, 100), getVec2f(20, 100), NONE, true);

}

void{
	
	World_init(w);

	World_initPlayer(w, getVec2f(40, 80), NONE);

	World_addPoint(w, getVec2f(290, 60), ALL, true);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(80, 20), NONE, false);

	World_addObstacle(w, getVec2f(250, 100), getVec2f(20, 100), NONE, false);

}

void{
	
	World_init(w);

	World_initPlayer(w, getVec2f(40, 80), NONE);

	World_addPoint(w, getVec2f(290, 60), ALL, true);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(80, 20), NONE, false);

	World_addObstacle(w, getVec2f(250, HEIGHT), getVec2f(20, HEIGHT), NONE, false);

}

void{
	
	World_init(w);

	World_initPlayer(w, getVec2f(40, 80), ALL);

	World_addPoint(w, getVec2f(300, 170), NONE, false);

	World_addObstacle(w, getVec2f(20, 30), getVec2f(WIDTH, 30), NONE, false);

	World_addObstacle(w, getVec2f(190, 80), getVec2f(20, 80), NONE, false);

	World_addObstacle(w, getVec2f(0, 100), getVec2f(10, 100), ALL, true);

}
