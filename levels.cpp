:levelName
bug-testing-level
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(270, 100), NONE);

	World_addPoint(world_p, getVec2f(1380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 100), getVec2f(40, 100), NONE);

	World_addObstacle(world_p, getVec2f(100, 100), getVec2f(40, 60), ALL);

	World_addObstacle(world_p, getVec2f(200, 100), getVec2f(40, 100), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(300, 100), getVec2f(40, 100), ALL);

	//World_addObstacle(world_p, getVec2f(300, 100), getVec2f(40, 80), ALL);

	World_addObstacle(world_p, getVec2f(400, 100), getVec2f(40, 100), NONE);

:levelName
level-1
:screenName
Star
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

:levelName
level-2
:screenName
Steps
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
:screenName
Pit
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(210, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 210, 210), getVec2f(210, 60), ALL);

:levelName
first-scaling-level-1
:screenName
Gap
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(160, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 160, 210), getVec2f(160, 60), ALL);

	World_addTextSprite(world_p, getVec2f(140, 140), "X key to scale ", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

:levelName
first-scaling-level-2
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 180, 110), getVec2f(180, 100), ALL);

:levelName
first-scaling-level-3
:screenName
Green Ledge
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL);

:levelName
first-scaling-level-4
:screenName
Green Star
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

:levelName
make-it-bigger-1
:screenName
Platform
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(340, 140), getVec2f(80, 130), ALL);

:levelName
make-it-bigger-2
:screenName
Bridge
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(420, 140), getVec2f(1.5, 130), ALL);

:levelName
point-cage
:screenName
Filter
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

	World_addObstacle(world_p, getVec2f(370, HEIGHT - 20), getVec2f(90, 20), NONE);

:levelName
point-cage-2
:screenName
Filter 2
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 190), getVec2f(WIDTH - 130, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(20, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH - 130, 20), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);
	
	World_addObstacle(world_p, getVec2f(370, HEIGHT - 20), getVec2f(90, 20), NONE);

:levelName
point-cage-3
:screenName
Filter 3
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(150, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(110, 190), getVec2f(WIDTH - 240, 20), NONE);

	World_addObstacle(world_p, getVec2f(110, 0), getVec2f(WIDTH - 240, 20), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

	World_addObstacle(world_p, getVec2f(370, HEIGHT - 20), getVec2f(90, 20), NONE);

	//World_addObstacle(world_p, getVec2f(110, 0), getVec2f(WIDTH - 240, 20), NONE);

	World_addObstacle(world_p, getVec2f(90, 0), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 20), getVec2f(WIDTH - 110, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, 0), getVec2f(70, 20), NONE);

	//World_addObstacle(world_p, getVec2f(90, HEIGHT - 40), getVec2f(20, 20), NONE);

:levelName
slow-fall-squeeze
:screenName
Dive
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 0), ALL);

	World_addPoint(world_p, getVec2f(400, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 70), getVec2f(150, 200), NONE);

	World_addObstacle(world_p, getVec2f(340, 0), getVec2f(20, 95), NONE);

	World_addObstacle(world_p, getVec2f(360, 0), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, 100), NONE);

	World_addObstacle(world_p, getVec2f(340, 100), getVec2f(140, 170), NONE);

:levelName
high-jump-1
:screenName
Doorstep
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(400, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 100), getVec2f(WIDTH, HEIGHT - 160), NONE);

:levelName
high-jump-2
:screenName
Cliff Tunnel
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(400, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(WIDTH, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(300, 40), getVec2f(WIDTH, HEIGHT - 110), NONE);

	World_addObstacle(world_p, getVec2f(50, 10), getVec2f(30, HEIGHT - 85), NONE);

:levelName
high-jump-3
:screenName
Cliff Tunnel 2
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 100), ALL);

	World_addPoint(world_p, getVec2f(430, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 200), getVec2f(290, 70), NONE);

	World_addObstacle(world_p, getVec2f(290, 250), getVec2f(190, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(100, 40), getVec2f(60, HEIGHT - 110), NONE);

	World_addObstacle(world_p, getVec2f(220, 10), getVec2f(30, HEIGHT - 160), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 80, 40), getVec2f(80, HEIGHT - 60), NONE);

:levelName
cooler-scaling-level-1
:screenName
Green Pair
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL);

:levelName
cooler-scaling-level-2
:screenName
Mousehole
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 100), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(240, 0 - 10000), getVec2f(60, HEIGHT - 70 + 10000), ALL);

:levelName
cooler-scaling-level-3
:screenName
Hedge
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), ALL);

	World_addObstacle(world_p, getVec2f(320, 0 - 2000), getVec2f(20, HEIGHT - 60 + 2000), ALL);

:levelName
cooler-scaling-level-4
:screenName
Green suit
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

:levelName
cooler-scaling-level-5
:screenName
Green Couple
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(380, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

:levelName
door-key-level-1
:screenName
Door
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
:screenName
Shelf
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
door-key-level-3
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(140, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(300, 0), getVec2f(20, 150), NONE);

	World_addDoor(world_p, getVec2f(300, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(50, 0), ALL);

:levelName
key-in-box
:screenName
Box
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

	World_addObstacle(world_p, getVec2f(0, -HEIGHT), getVec2f(110, HEIGHT + 10), NONE);

	World_addObstacle(world_p, getVec2f(0, 10), getVec2f(10, 40), NONE);

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
:screenName
Key Hole
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
:screenName
Key Hole 2
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

	World_addTextSprite(world_p, getVec2f(25, 40), "R key to restart level ", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

:levelName
floor-is-door
:screenName
Trapdoor
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(380, 10), ALL);

	World_addDoor(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(100, 30), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 60, 90), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 50), getVec2f(20, 135), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 10, 0), getVec2f(10, 30), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 10, 50), getVec2f(10, 40), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 40, 70), ALL);

:levelName
push-key-with-point
:screenName
Cell
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(200, 150), NONE);

	//World_addPoint(world_p, getVec2f(380, 170), NONE);
	World_addPoint(world_p, getVec2f(420, 170), NONE);

	World_addObstacle(world_p, getVec2f(150, 210), getVec2f(180, 20), NONE);

	World_addObstacle(world_p, getVec2f(150, 230), getVec2f(200, 40), NONE);

	World_addObstacle(world_p, getVec2f(150, 110), getVec2f(180, 40), NONE);

	World_addObstacle(world_p, getVec2f(150, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(250, 170), getVec2f(20, 10), ALL);

	World_addDoor(world_p, getVec2f(310, 150), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(220, 50), NONE);

:levelName
throw-key
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 150), NONE);

	World_addPoint(world_p, getVec2f(445, 230), ALL);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 60), getVec2f(120, 60), NONE);

	World_addDoorKey(world_p, getVec2f(0, 100), ALL);

	World_addDoor(world_p, getVec2f(440, HEIGHT - 70), getVec2f(20, 20), NONE);

	//World_addObstacle(world_p, getVec2f(WIDTH - 60, HEIGHT - 20), getVec2f(60, 20), NONE);

	//World_addObstacle(world_p, getVec2f(WIDTH - 60, HEIGHT - 20), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 60, HEIGHT - 80), getVec2f(20, 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, HEIGHT - 80), getVec2f(20, 80), NONE);

	World_addObstacle(world_p, getVec2f(120, HEIGHT - 10), getVec2f(WIDTH - 180, 10), NONE);

:levelName
maybe-key-should-fly
:screenName
Locker
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH - 100, 50), NONE);

	world_p->player.facing = 0;

	World_addPoint(world_p, getVec2f(40, 230), ALL);

	World_addObstacle(world_p, getVec2f(90, 200), getVec2f(WIDTH * 100, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 20), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, HEIGHT - 10), getVec2f(50, 10), NONE);

	World_addObstacle(world_p, getVec2f(70, 60), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 20), getVec2f(40, HEIGHT - 70 - 20), NONE);

	World_addDoor(world_p, getVec2f(70, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

:levelName
flying-key-1
:screenName
Locker
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH - 100, 50), NONE);

	world_p->player.facing = 0;

	World_addPoint(world_p, getVec2f(40, 230), ALL);

	World_addObstacle(world_p, getVec2f(90, 250), getVec2f(WIDTH * 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 20), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, HEIGHT - 10), getVec2f(50, 10), NONE);

	World_addObstacle(world_p, getVec2f(70, 60), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 20), getVec2f(40, HEIGHT - 20 - 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 200), getVec2f(100, 50), NONE);

	World_addDoor(world_p, getVec2f(70, 20), getVec2f(20, 40), NONE);

	World_addDoorKey(world_p, getVec2f(200, 150), ALL);

:levelName
flying-key-2-trickshot-edition
:screenName
Locker 3
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH - 100, 50), NONE);

	world_p->player.facing = 0;

	World_addPoint(world_p, getVec2f(40, 230), ALL);

	World_addObstacle(world_p, getVec2f(90, 250), getVec2f(WIDTH * 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 20), getVec2f(20, HEIGHT - 20), NONE);

	World_addObstacle(world_p, getVec2f(20, HEIGHT - 10), getVec2f(50, 10), NONE);

	World_addObstacle(world_p, getVec2f(70, 60), getVec2f(20, HEIGHT - 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 20), getVec2f(40, HEIGHT - 20 - 20), NONE);

	World_addDoor(world_p, getVec2f(70, 20), getVec2f(20, 40), NONE);

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
:screenName
Purple Ledge
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), ALL_FROM_TOP);

:levelName
all-from-top-2
:screenName
Purple Star
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(380, 70), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

:levelName
all-from-top-3
:screenName
Cancellation
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), ALL_FROM_TOP);

	World_addPoint(world_p, getVec2f(420, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(WIDTH, 10), NONE);

	World_addObstacle(world_p, getVec2f(380, 60), getVec2f(100, HEIGHT - 120), NONE);

:levelName
point-pikaboo
:screenName
Faith
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(70, 210), ALL);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(WIDTH * 3, 10), ALL_FROM_TOP);

:levelName
get-under-cup
:screenName
Cup
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(WIDTH / 2 - 10, 50), ALL_FROM_TOP);

	World_addPoint(world_p, getVec2f(WIDTH / 2 - 5, 140), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 - 60, 100), getVec2f(120, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 - 60, 120), getVec2f(20, 50), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH / 2 + 60 - 20, 120), getVec2f(20, 50), NONE);

:levelName
key-obstacle-course
:screenName
Opening
:levelCode

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
:screenName
Lock
:levelCode

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


:levelName
scale-field-1
:screenName
Cold
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 120), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addScaleField(world_p, getVec2f(280, 50), getVec2f(50, HEIGHT - 50), NONE);


:levelName
scale-field-2
:screenName
Warm
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(400, 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 10, 0), getVec2f(10, HEIGHT), NONE);

	World_addScaleField(world_p, getVec2f(330, 0), getVec2f(140, HEIGHT), ALL);

:levelName
scale-field-3
:screenName
Spots
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(420, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 150, 70), getVec2f(150, HEIGHT - 130), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, -HEIGHT), getVec2f(100, HEIGHT + 40), NONE);

	World_addScaleField(world_p, getVec2f(220, 180), getVec2f(40, 30), ALL);

	World_addScaleField(world_p, getVec2f(0, 30), getVec2f(60, 40), ALL);

:levelName
get-over-the-field
:screenName
Swamp
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 200), NONE);

	World_addPoint(world_p, getVec2f(420, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addScaleField(world_p, getVec2f(0, 230), getVec2f(WIDTH, 40), ALL);

:levelName
layers-of-fields
:screenName
Transfers
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 200), NONE);

	World_addPoint(world_p, getVec2f(420, 10), NONE);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(340, 210), getVec2f(20, 30), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 210), getVec2f(20, 40), NONE);

	World_addScaleField(world_p, getVec2f(360, 0), getVec2f(100, 50), ALL);

	World_addScaleField(world_p, getVec2f(360, 50), getVec2f(100, 50), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(360, 100), getVec2f(100, 50), ALL);

	World_addScaleField(world_p, getVec2f(360, 150), getVec2f(100, 50), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(360, 200), getVec2f(100, 50), ALL);

:levelName
player-position-1
:screenName
Coordination
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 190), NONE);

	World_addPoint(world_p, getVec2f(250, 170), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 105), NONE);

:levelName
player-position-2
:screenName
Mirror
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(100, 100), NONE);

	World_addPoint(world_p, getVec2f(350, 200), NONE);

	World_addObstacle(world_p, getVec2f(0, 120), getVec2f(WIDTH - 150, 10), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 120), getVec2f(100, 10), NONE);

	World_addObstacle(world_p, getVec2f(80, 150), getVec2f(40, 40), ALL_FROM_TOP);

:levelName
player-position-3
:screenName
Acceleration
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 190), ALL);

	World_addPoint(world_p, getVec2f(WIDTH / 2 + 100, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(WIDTH, HEIGHT - 60), NONE);

:levelName
slide-slide-slide
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(200, 30), ALL_FROM_TOP);

	World_addPoint(world_p, getVec2f(210, 240), NONE);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(WIDTH - 100, 20), NONE);

	World_addObstacle(world_p, getVec2f(100, 150), getVec2f(150, 20), NONE);

	World_addObstacle(world_p, getVec2f(230, 170), getVec2f(20, 200), NONE);

:levelName
grow-through-jumping
:screenName
Magic Bean
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(200, 190), NONE);

	World_addPoint(world_p, getVec2f(400, 50), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 150, 90), getVec2f(150, 120), NONE);

	World_addScaleField(world_p, getVec2f(100, 190), getVec2f(50, 20), ALL);

:levelName
player-pos-key
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 190), NONE);

	World_addPoint(world_p, getVec2f(400, 170), NONE);

	World_addDoor(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addDoor(world_p, getVec2f(350, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(100, 190), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(120, 170), getVec2f(60, 20), NONE);

	World_addObstacle(world_p, getVec2f(140, 150), getVec2f(20, 20), NONE);

	World_addDoorKey(world_p, getVec2f(400, 0), ALL);

	World_addObstacle(world_p, getVec2f(350, 50), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(430, 30), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(350, 30), getVec2f(20, 20), NONE);

:levelName
airport-control
:screenName
Tunnel
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(1, 150), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 20, 150), NONE);

	World_addObstacle(world_p, getVec2f(70, 170), getVec2f(190, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 230), getVec2f(260, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 190), getVec2f(20, 20), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(40, 20), NONE);

	//World_addObstacle(world_p, getVec2f(240, 190), getVec2f(20, 20), NONE);

	//World_addObstacle(world_p, getVec2f(220, 210), getVec2f(40, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 40, 190), getVec2f(40, 100), NONE);

	World_addScaleField(world_p, getVec2f(130, 150), getVec2f(40, 20), ALL);

	World_addObstacle(world_p, getVec2f(130, 130), getVec2f(40, 20), NONE);

	//World_addScaleField(world_p, getVec2f(100, 210), getVec2f(20, 20), ALL);

:levelName
player-position-jumping-key-1
:screenName
Puppet
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 0), NONE);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(100, 40), NONE);

	World_addPoint(world_p, getVec2f(10, 190), NONE);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(60, 20), NONE);

	World_addDoor(world_p, getVec2f(40, 170), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(400, 150), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 40), getVec2f(WIDTH, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 60), getVec2f(20, HEIGHT - 100), NONE);

:levelName
player-position-jumping-key-2
:screenName
Puppet 2
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 0), NONE);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(100, 40), NONE);

	World_addPoint(world_p, getVec2f(10, 190), NONE);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(60, 20), NONE);

	World_addDoor(world_p, getVec2f(40, 170), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(400, 150), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 40), getVec2f(WIDTH, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 300, 0), getVec2f(20, 180), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 140, 110), getVec2f(20, 120), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 140, 70), getVec2f(20, 40), NONE);

:levelName
player-position-jumping-key-3
:screenName
Puppet 3
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 0), NONE);

	World_addObstacle(world_p, getVec2f(0, 50), getVec2f(100, 40), NONE);

	World_addPoint(world_p, getVec2f(10, 190), NONE);

	World_addObstacle(world_p, getVec2f(0, 150), getVec2f(60, 20), NONE);

	World_addDoor(world_p, getVec2f(40, 170), getVec2f(20, 60), NONE);

	World_addDoorKey(world_p, getVec2f(400, 150), ALL_FROM_TOP);

	World_addObstacle(world_p, getVec2f(0, HEIGHT - 40), getVec2f(WIDTH, 40), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 40), NONE);

	//World_addDoor(world_p, getVec2f(WIDTH - 300, 0), getVec2f(20, 180), NONE);

	//World_addDoor(world_p, getVec2f(WIDTH - 140, 110), getVec2f(20, 120), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 70), getVec2f(20, HEIGHT - 110), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 170, 0), getVec2f(10, 150), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 240, 120), getVec2f(20, HEIGHT - 160), NONE);

:levelName
point-field-cage
:screenName
Tangible
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(70, 100), NONE);

	World_addPoint(world_p, getVec2f(410, 100), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(150, 60), NONE);

	World_addObstacle(world_p, getVec2f(350, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT - 180), NONE);

	World_addObstacle(world_p, getVec2f(370, 0), getVec2f(90, 20), NONE);

	World_addScaleField(world_p, getVec2f(370, 60), getVec2f(90, HEIGHT - 60), ALL);

	World_addScaleField(world_p, getVec2f(240, 60), getVec2f(90, HEIGHT - 60), ALL);


:levelName
no-legs
:screenName
Depart
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

:levelName
no-legs-2
:screenName
No hurdle
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 200, 130), getVec2f(200, 80), NONE);

:levelName
no-legs-3
:screenName
No dead end
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(100, 60), NONE);

:levelName
no-legs-4
:screenName
No gate
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 200, 130), getVec2f(200, 80), NONE);

	World_addObstacle(world_p, getVec2f(0, 0), getVec2f(40, 80), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 270, 0), getVec2f(40, 170), NONE);

	World_addObstacle(world_p, getVec2f(40, 0), getVec2f(170, 20), NONE);

:levelName
no-legs-scalable-point
:screenName
Lost
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH * 100, 60), NONE);

:levelName
no-legs-scalable-point-first
:screenName
Offset
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 90), ALL);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH * 100, 60), NONE);

	World_addObstacle(world_p, getVec2f(200, 0), getVec2f(40, 60), NONE);

:levelName
no-legs-scalable-point-scale-field
:screenName
Offsetter
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 170), ALL);

	//World_addDoorKey(world_p, getVec2f(70, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH - 200, 60), NONE);

	World_addScaleField(world_p, getVec2f(200, 40), getVec2f(60, 170), NONE);

:levelName
no-legs-scalable-point-scale-field-2
:screenName
Lost
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 170), ALL);

	//World_addDoorKey(world_p, getVec2f(70, 90), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH - 200, 60), NONE);

	World_addScaleField(world_p, getVec2f(200, 0), getVec2f(60, 40), NONE);

:levelName
no-legs-scalable-point-2
:screenName
Island
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(70, 100), ALL);

	World_addPoint(world_p, getVec2f(410, 70), ALL);

	//World_addDoorKey(world_p, getVec2f(70, 90), NONE);

	World_addObstacle(world_p, getVec2f(30, 210), getVec2f(WIDTH - 330, 60), NONE);

:levelName
no-legs-key-block
:screenName
Pick
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(20, 170), NONE);

	World_addDoorKey(world_p, getVec2f(WIDTH - 150, 170), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH * 100, 60), NONE);

	World_addObstacle(world_p, getVec2f(50, 90), getVec2f(20, 20), ALL);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

:levelName
no-legs-point-hole
:screenName
Hurdle
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(50, 100), ALL);

	World_addPoint(world_p, getVec2f(WIDTH - 50, 230), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(100, 60), NONE);

	World_addObstacle(world_p, getVec2f(200, 210), getVec2f(60, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 120, 210), getVec2f(60, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 30, -HEIGHT), getVec2f(30, 2 * HEIGHT), NONE);

:levelName
no-legs-scale-field-key
:screenName
Mold
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(30, 170), NONE);

	World_addDoorKey(world_p, getVec2f(200, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addScaleField(world_p, getVec2f(250, 130), getVec2f(80, 80), ALL);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, 210), NONE);

:levelName
no-legs-drag-key
:screenName
Force
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(10, 170), NONE);

	World_addDoorKey(world_p, getVec2f(200, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(0, 130), getVec2f(80, 20), NONE);

	World_addDoor(world_p, getVec2f(60, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, 210), NONE);

:levelName
no-legs-key-first
:screenName
Key and lock
:levelCode

	World_restore(world_p);

	world_p->playerHasNoLegs = true;

	World_initPlayer(world_p, getVec2f(150, 100), ALL);

	World_addPoint(world_p, getVec2f(WIDTH - 60, 170), NONE);

	World_addDoorKey(world_p, getVec2f(50, 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(200, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 200, 210), getVec2f(200, 60), NONE);

	World_addDoor(world_p, getVec2f(WIDTH - 100, 150), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 130), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 150), getVec2f(20, 60), NONE);

:levelName
scale-position-block
:screenName
Rider
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 190), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 70, 50), NONE);

	World_addObstacle(world_p, getVec2f(20, 210), getVec2f(80, 20), ALL);

:levelName
scale-position-block-2
:screenName
Kick flip
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(50, 130), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 60, 130), NONE);

	World_addObstacle(world_p, getVec2f(50, 170), getVec2f(15, 20), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(100, 150), getVec2f(20, 20), NONE);

	//World_addObstacle(world_p, getVec2f(200, 130), getVec2f(20, 40), NONE);

	World_addScaleField(world_p, getVec2f(300, 150), getVec2f(20, 20), NONE);

:levelName
two-scale-fields
:screenName
Boost
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(20, 190), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 70 , 30), NONE);

	World_addObstacle(world_p, getVec2f(0, 250), getVec2f(WIDTH, 20), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, 50), getVec2f(100, HEIGHT - 70), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 20), getVec2f(20, 30), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 100, -HEIGHT), getVec2f(100, HEIGHT + 20), NONE);

	World_addScaleField(world_p, getVec2f(50, 0), getVec2f(140, HEIGHT - 20), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(190, 0), getVec2f(140, HEIGHT - 20), ALL);

:levelName
scale-position-block-3
:screenName
block
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 190), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 60, 130), NONE);

	World_addObstacle(world_p, getVec2f(50, 210), getVec2f(60, 30), ALL_FROM_TOP);

	World_addScaleField(world_p, getVec2f(0, 00), getVec2f(50, HEIGHT), ALL);

	//World_addObstacle(world_p, getVec2f(200, 60), getVec2f(60, 210), NONE);

:levelName
scale-position-block-4
:screenName
block
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 190), NONE);

	World_addPoint(world_p, getVec2f(50, 40), NONE);

	World_addObstacle(world_p, getVec2f(0, 210), getVec2f(WIDTH, 60), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 150, 60), getVec2f(60, 10), ALL);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 00), getVec2f(50, HEIGHT - 60), ALL_FROM_TOP);

	//World_addDoorKey(world_p, getVec2f(70, 190), ALL);

:levelName
scale-position-block-5
:screenName
Diver
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 30), NONE);

	World_addPoint(world_p, getVec2f(70, 190), NONE);

	World_addObstacle(world_p, getVec2f(40, 50), getVec2f(80, 20), ALL);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 0), getVec2f(50, HEIGHT), ALL_FROM_TOP);

:levelName
scale-position-block-6
:screenName
Conger
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(20, 100), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 50, 250), NONE);

	World_addObstacle(world_p, getVec2f(20, 120), getVec2f(15, 40), ALL);

	World_addScaleField(world_p, getVec2f(200, 60), getVec2f(50, 100), ALL_FROM_TOP);

	//World_addScaleField(world_p, getVec2f(WIDTH - 200, 0), getVec2f(50, HEIGHT), NONE);

	//World_addObstacle(world_p, getVec2f(WIDTH - 20, 0), getVec2f(20, HEIGHT), NONE);

	World_addObstacle(world_p, getVec2f(WIDTH - 20, 210), getVec2f(20, 60), NONE);

	World_addObstacle(world_p, getVec2f(200, 190), getVec2f(WIDTH - 200, 20), NONE);

	World_addScaleField(world_p, getVec2f(220, 210), getVec2f(WIDTH - 220, 60), NONE);

:levelName
scale-position-block-7
:screenName
block
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 50), NONE);

	World_addPoint(world_p, getVec2f(WIDTH - 50, 250-1000), NONE);

	World_addObstacle(world_p, getVec2f(50, 70), getVec2f(80, 20), NONE);

	World_addObstacle(world_p, getVec2f(190, 70), getVec2f(80, 20), NONE);

	World_addObstacle(world_p, getVec2f(20, 200), getVec2f(80, 20), ALL);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 100), getVec2f(50, 110), ALL_FROM_TOP);

:levelName
scale-position-block-5.2
:screenName
Ascent
:levelCode

	World_restore(world_p);

	world_p->scalingByPlayerPosition = true;

	World_initPlayer(world_p, getVec2f(70, 30), NONE);

	World_addPoint(world_p, getVec2f(30, 130), NONE);

	World_addObstacle(world_p, getVec2f(40, 50), getVec2f(80, 20), ALL);

	World_addObstacle(world_p, getVec2f(0, 90), getVec2f(100, 20), NONE);

	World_addObstacle(world_p, getVec2f(80, 110), getVec2f(20, 60), NONE);

	World_addScaleField(world_p, getVec2f(WIDTH - 50, 0), getVec2f(50, HEIGHT), ALL_FROM_TOP);
