:levelName
level-1
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

:levelName
level-2
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 110), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(280, 190), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(world_p, getVec2f(320, 170), getVec2f(WIDTH, 20), ALL);

	World_addObstacle(world_p, getVec2f(360, 150), getVec2f(WIDTH, 20), ALL);

:levelName
level-3
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(210, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 210, 210), getVec2f(210, 60), ALL);

:levelName
first-scaling-level-1
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(160, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 160, 210), getVec2f(160, 60), ALL);

	World_addTextSprite(world_p, getVec2f(140, 140), "Use the \"X\" key", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

:levelName
first-scaling-level-2
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 180, 110), getVec2f(180, 100), ALL);

:levelName
first-scaling-level-3
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL);


:levelName
first-scaling-level-4
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

:levelName
make-it-bigger-1
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(340, 140), getVec2f(80, 130), ALL);

:levelName
make-it-bigger-2
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(420, 140), getVec2f(1.5, 130), ALL);

:levelName
point-cage
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

:levelName
high-jump-1
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(400, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 100), getVec2f(WIDTH, HEIGHT - 160), NONE);

:levelName
high-jump-2
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(400, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(300, 40), getVec2f(WIDTH, HEIGHT - 100), NONE);

:levelName
cooler-scaling-level-1
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL);

:levelName
cooler-scaling-level-2
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 100), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(240, 0 - 10000), getVec2f(60, HEIGHT - 70 + 10000), ALL);

:levelName
cooler-scaling-level-3
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(320, 0 - 2000), getVec2f(20, HEIGHT - 60 + 2000), ALL);

:levelName
cooler-scaling-level-4
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

:levelName
cooler-scaling-level-5
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

:levelName
door-key-level-1
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 170), NONE);

:levelName
door-key-level-2
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 0), ALL);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(120, 20), NONE);

:levelName

:levelName
door-key-level-3
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 30), ALL);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(120, 20), NONE);

	World_addObstacle(world_p, getVec2f(110, 0), getVec2f(10, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(110, 10), NONE);

:levelName

//:levelName
//door-key-level-4
//:levelCode

	//World_restore(world_p);

	//World_initPlayer(world_p, getVec2f(70, 100), NONE);

	//World_addPoint(world_p, getVec2f(380, 170), NONE);

	//World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	//World_addObstacle(world_p, getVec2f(240, 20), getVec2f(20, 40), NONE);

	//World_addObstacle(world_p, getVec2f(0, 60), getVec2f(300, 20), NONE);

	//World_addObstacle(world_p, getVec2f(0, 0), getVec2f(300, 20), NONE);

	//World_addDoor(world_p, getVec2f(300, 0), getVec2f(20, HEIGHT - 60), NONE);

	//World_addDoorKey(world_p, getVec2f(90, 20), ALL);

:levelName
get-key-up-1
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 120), getVec2f(210, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(220, 40), NONE);

	World_addObstacle(world_p, getVec2f(220, 120), getVec2f(260, 150), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(300, 60), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(100, 230), ALL);

:levelName
get-key-up-2
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 120), getVec2f(210, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(220, 40), NONE);

	World_addObstacle(world_p, getVec2f(220, 120), getVec2f(260, 150), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(300, 60), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(210, 0), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(100, 230), ALL);

:levelName
floor-is-door
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 10), ALL);

	World_addDoor(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(100, 30), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 50, 90), getVec2f(50, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 110, 50), getVec2f(20, 135), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 30, 70), ALL);

:levelName
push-key-with-point
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(200, 150), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(150, 210), getVec2f(180, 20), NONE);

	World_addObstacle(world_p, getVec2f(150, 230), getVec2f(195, 40), NONE);

	World_addObstacle(world_p, getVec2f(150, 110), getVec2f(180, 40), NONE);

	World_addObstacle(world_p, getVec2f(150, 150), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(310, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(220, 50), NONE);

:levelName
maybe-key-should-fly
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(30, 50), NONE);

	World_addPoint(world_p, getVec2f(420, 230), ALL);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(WIDTH - 130, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 260), getVec2f(WIDTH - 100, 10), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, 60), getVec2f(30, HEIGHT - 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 20), getVec2f(20, HEIGHT - 30), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 120, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

:levelName
flying-key-1
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(30, 50), NONE);

	World_addPoint(world_p, getVec2f(420, 230), ALL);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(100, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 260), getVec2f(WIDTH - 100, 10), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, 60), getVec2f(30, HEIGHT - 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 20), getVec2f(20, HEIGHT - 30), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 120, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

:levelName
flying-key-2-trickshot-edition
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(30, 50), NONE);

	World_addPoint(world_p, getVec2f(420, 230), ALL);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 260), getVec2f(WIDTH - 100, 10), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 130, 60), getVec2f(30, HEIGHT - 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 20), getVec2f(20, HEIGHT - 30), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 120, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

:levelName
door-key-level-with-key
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 170), NONE);

	World_addPoint(world_p, getVec2f(420, 190), ALL);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 170), getVec2f(40, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 190), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(80, 20), NONE);

	World_addObstacle(world_p, getVec2f(360, 0), getVec2f(20, HEIGHT - 100), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(380, 0), getVec2f(80, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(380, 20), NONE);

	World_addDoor(world_p, getVec2f(360, HEIGHT - 100), getVec2f(20, 60), NONE);

	World_addDoor(world_p, getVec2f(200, 170), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(150, 150), getVec2f(80, 20), NONE);

	World_addDoorKey(world_p, getVec2f(90, 100), ALL);

:levelName
all-from-top-1
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL_FROM_TOP);

:levelName
all-from-top-2
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

:levelName
all-from-top-3
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL_FROM_TOP);

	World_addPoint(world_p, getVec2f(420, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(380, 60), getVec2f(100, HEIGHT - 120), NONE);

:levelName
point-pikaboo
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(70, 210), ALL);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(WIDTH * 3, 10), ALL_FROM_TOP);

:levelName
get-under-cup
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH / 2 - 10, 50), ALL_FROM_TOP);

	World_addPoint(world_p, getVec2f(WIDTH / 2 - 5, 140), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 - 60, 100), getVec2f(120, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 - 60, 120), getVec2f(20, 50), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 + 60 - 20, 120), getVec2f(20, 50), NONE);

:levelName
key-obstacle-course
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(110, 100), NONE);

	World_addPoint(world_p, getVec2f(30, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 230), getVec2f(100, 40), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 130, 180), getVec2f(30, 90), NONE);

	World_addDoor(world_p, getVec2f(230, 120), getVec2f(30, 90), NONE);

	World_addObstacle(world_p, getVec2f(230, 0), getVec2f(30, 120), NONE);

	World_addObstacle(world_p, getVec2f(260, 0), getVec2f(200, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 50, 150), ALL_FROM_TOP);

:levelName
key-in-cage-all-from-top
:levelCode

	World_restore(world_p);

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(110, 100), NONE);

	World_addPoint(world_p, getVec2f(30, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 230), getVec2f(100, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 0), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 20), getVec2f(20, HEIGHT - 20), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 50, 150), ALL_FROM_TOP);

