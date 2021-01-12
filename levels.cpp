:level 15 20 {

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

:level 15 19 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 90), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), ALL);

	World_addObstacle(w, getVec2f(100, 180 - 40), getVec2f(WIDTH - 100, 40), ALL);

	//World_addObstacle(w, getVec2f(240, 180 - 40), getVec2f(80, 40), ALL);

}

:level 15 18 {
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(120, 20), ALL);

	World_addObstacle(w, getVec2f(190, 180 - 20), getVec2f(150, 20), ALL);

}

:level 15 17 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), ALL);

	World_addObstacle(w, getVec2f(220, 180 - 20), getVec2f(100, 20), ALL);

	//World_addSprite(w, getVec2f(80, 180 - 80), getVec2f(20, 20), COLOR_WHITE, "scale-help");

	World_addTextSprite(w, getVec2f(80, 80), "Use the \"X\" key.", 0, COLOR_WHITE, GAME_LAYER_TEXT);
	
}

:level 15 16 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 140), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(w, getVec2f(120, 180 - 80), getVec2f(200, 60), ALL);

}

:level 15 15 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), ALL);

}

:level 14 15 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(250, 180 - 120), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

	World_addObstacle(w, getVec2f(230, 180 - 60), getVec2f(60, 60), ALL);


}

:level 13 15 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(250, 180 - 120), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

	World_addObstacle(w, getVec2f(270, 180 - 60), getVec2f(1.2, 60), ALL);



}

:level 15 14 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

}

:level 15 13{

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 160), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), ALL);

}

:level 16 11{

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 160), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

	World_addObstacle(w, getVec2f(220, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(w, getVec2f(240, 0), getVec2f(WIDTH - 250, 10), NONE);

	World_addObstacle(w, getVec2f(WIDTH - 10, 0), getVec2f(10, HEIGHT), NONE);

}

:level 15 12 {
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 60), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(w, getVec2f(160, 180 - HEIGHT * 10), getVec2f(60, HEIGHT * 10 - 30), ALL);

}

:level 15 11 {
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), NONE);

	World_addPoint(w, getVec2f(260, 180 - 60), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), ALL);

	//World_addObstacle(w, getVec2f(220, 180 - 40), getVec2f(15, 20), ALL);
	World_addObstacle(w, getVec2f(220, 180 - HEIGHT * 8), getVec2f(15, HEIGHT * 8 - 20), ALL);

}

:level 15 10 {
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addPoint(w, getVec2f(260, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);
	
}

:level 15 9 {
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addPoint(w, getVec2f(260, 180 - 60), ALL);

	//World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);
	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(100, 20), NONE);

}

:level 15 8 {
	
	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addPoint(w, getVec2f(260, 180 - 60), NONE);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(w, getVec2f(100, 180 - 100), getVec2f(100, 80), ALL);

}

:level 16 8 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 20), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(w, getVec2f(200, 180 - 100), getVec2f(WIDTH - 200, 80), NONE);

	World_addPoint(w, getVec2f(260, 20), NONE);
	
}

:level 17 8 {

	World_restore(w);

	World_initPlayer(w, getVec2f(50, 180 - 100), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 50), getVec2f(WIDTH, 50), NONE);

	World_addObstacle(w, getVec2f(0, 0), getVec2f(WIDTH, 5), NONE);

	World_addObstacle(w, getVec2f(200, 40), getVec2f(WIDTH - 200, HEIGHT - 90), NONE);

	World_addPoint(w, getVec2f(260, 20), NONE);

}

:level 18 8 {

	World_restore(w);

	World_initPlayer(w, getVec2f(30, 180 - 100), ALL);

	World_addObstacle(w, getVec2f(0, 180 - 50), getVec2f(60, 50), NONE);

	World_addObstacle(w, getVec2f(60, 180 - 20), getVec2f(140, 20), NONE);

	World_addObstacle(w, getVec2f(0, 0), getVec2f(WIDTH, 5), NONE);

	World_addObstacle(w, getVec2f(200, 40), getVec2f(WIDTH - 200, HEIGHT - 40), NONE);

	World_addPoint(w, getVec2f(260, 20), NONE);

}

:level 15 7 {

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), NONE);

	World_addPoint(w, getVec2f(260, 40), ALL_FROM_TOP);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH, 20), NONE);

}

:level 15 6 {

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), NONE);

	World_addPoint(w, getVec2f(260, 40), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(100, 20), ALL_FROM_TOP);

}

:level 15 5 {

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), ALL_FROM_TOP);

	World_addPoint(w, getVec2f(260, 40), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(w, getVec2f(WIDTH - 100, 60), getVec2f(100, HEIGHT - 80), NONE);

	World_addObstacle(w, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

}

:level 15 4 {

	World_restore(w);

	World_initPlayer(w, getVec2f(WIDTH / 2 - 7, 20), ALL_FROM_TOP);

	World_addPoint(w, getVec2f(WIDTH / 2 - 5, 90), NONE);

	World_addObstacle(w, getVec2f(WIDTH / 2 - 50, 60), getVec2f(100, 20), NONE);

	World_addObstacle(w, getVec2f(WIDTH / 2 - 50, 80), getVec2f(20, 40), NONE);

	World_addObstacle(w, getVec2f(WIDTH / 2 + 30, 80), getVec2f(20, 40), NONE);

}

:level 16 5 {

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), NONE);

	World_addPoint(w, getVec2f(20, HEIGHT - 40), ALL);

	World_addObstacle(w, getVec2f(0, HEIGHT - 90), getVec2f(WIDTH * 4, 10), ALL_FROM_TOP);

}

:level 14 5 {

	World_restore(w);

	World_initPlayer(w, getVec2f(60, 180 - 100), NONE);

	World_addPoint(w, getVec2f(40, 20), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH, 20), NONE);

	World_addScaleField(w, getVec2f(200, 0), getVec2f(100, HEIGHT - 20), ALL);
	
}

:level 13 5 {

	World_restore(w);

	World_initPlayer(w, getVec2f(40, 180 - 100), ALL);

	World_addPoint(w, getVec2f(270, 40), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(60, 20), NONE);

	World_addObstacle(w, getVec2f(220, HEIGHT - 20), getVec2f(100, 20), NONE);

	World_addScaleField(w, getVec2f(60, 0), getVec2f(160, HEIGHT - 20), NONE);

}

:level 13 4 {

	World_restore(w);

	World_initPlayer(w, getVec2f(40, 180 - 100), NONE);

	World_addPoint(w, getVec2f(270, 10), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(w, getVec2f(0, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addScaleField(w, getVec2f(150, HEIGHT - 40), getVec2f(40, 40), ALL);

}

:level 12 5 {

	World_restore(w);

	World_initPlayer(w, getVec2f(40, 100), NONE);

	World_addPoint(w, getVec2f(270, 180 - 120), NONE);

	World_addObstacle(w, getVec2f(0, HEIGHT - 60), getVec2f(110, 60), NONE);

	World_addObstacle(w, getVec2f(WIDTH - 80, HEIGHT - 60), getVec2f(80, 60), NONE);

	World_addScaleField(w, getVec2f(WIDTH / 2 - 20, HEIGHT - 110), getVec2f(100, 40), ALL);

}

:level 11 5 {

	World_restore(w);

	World_initPlayer(w, getVec2f(20, 40), NONE);

	World_addPoint(w, getVec2f(20, HEIGHT - 30), NONE);

	World_addObstacle(w, getVec2f(0, 80), getVec2f(100, 60), NONE);

	World_addObstacle(w, getVec2f(50, HEIGHT - 30), getVec2f(50, 50), NONE);

	World_addScaleField(w, getVec2f(160, 60), getVec2f(40, 40), ALL_FROM_TOP);

}
