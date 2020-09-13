//1
void{

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 20), ALL, false);

}

//2
void{

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 80), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 20), ALL, false);
	World_addObstacle(w, getVec2f(WIDTH - 100, 40), getVec2f(100, 20), ALL, false);

}

//3
void{

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH - 200, 20), ALL, false);
	World_addObstacle(w, getVec2f(WIDTH - 120, 20), getVec2f(120, 20), ALL, false);

}

//4
void{

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), ALL, false);
	World_addObstacle(w, getVec2f(WIDTH - 100, 20), getVec2f(100, 20), ALL, false);

}

//5
void{

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 120), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(WIDTH, 20), ALL, false);

	World_addObstacle(w, getVec2f(200, 80), getVec2f(WIDTH - 200, 60), ALL, false);

}

//6
void{

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), NONE, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), ALL, false);

}

//7
void{

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), NONE, false);

}

//8
void{

	World_init(w);

	World_initPlayer(w, getVec2f(50, 100), NONE);

	World_addPoint(w, getVec2f(290, 160), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(100, 20), ALL, false);

}

//9
void{

	World_init(w);

	World_initPlayer(w, getVec2f(20, 100), NONE);

	World_addPoint(w, getVec2f(270, 60), ALL, false);

	World_addObstacle(w, getVec2f(0, 20), getVec2f(50, 20), NONE, false);

	World_addObstacle(w, getVec2f(200, 100), getVec2f(20, 100), NONE, false);

}
