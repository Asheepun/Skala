:levelName
level-1
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 100), NONE);

	World_addPoint(world_p, getVec2f(270, 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 160), getVec2f(WIDTH, 20), NONE);

:levelName
level-2
:levelCode

	World_restore(world_p);

	World_initPlayer(world_p, getVec2f(50, 100), NONE);

	World_addPoint(world_p, getVec2f(270, 120), NONE);

	World_addObstacle(world_p, getVec2f(0, 160), getVec2f(WIDTH, 20), ALL);

