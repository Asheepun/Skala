//#include "stdbool.h"
#include "game.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
//#include "geometry.h"
//#include "stb_truetype.h"
//#include "text.h"
//#include "utils.h"
#include "levels.h"
//#include "audio.h"

typedef struct Collision{
	unsigned int lighterBodyPairIndex;
	unsigned int heavierBodyPairIndex;
	bool oub;
}Collision;

int blockerAnimationCount = 25;

void World_initLevel(World *world_p){

	for(int i = 0; i < LEVELS_LENGTH; i++){
		if(strcmp(world_p->currentLevel, levels[i].name) == 0){

			levels[i].generate(world_p);

		}
	}

	world_p->levelWidth = WIDTH;
	world_p->levelHeight = HEIGHT;

	world_p->renderer.offset = getVec2f(0, 0);

	Renderer2D_Color backgroundColor = COLOR_BLACK;
	if(world_p->scalingByPlayerPosition){
		backgroundColor = COLOR_DARK_GREY;
	}

	World_addSprite(world_p, getVec2f(0, 0), getVec2f(WIDTH, HEIGHT), backgroundColor, "obstacle", 1, GAME_LAYER_BACKGROUND);

	if(world_p->scalingByPlayerPosition){
		//playSound("begin-scaling");
	}

}

int scalingSoundCounter = 0;

void World_levelState(World *world_p){

	if(world_p->fadeTransitionCounter > FADE_TRANSITION_TIME / 2
	&& world_p->points.length == 0){
		return;
	}

	//printf("---\n");

	if(world_p->actions[MENU_ACTION].downed){

		world_p->stateBeforeOpeningMenu = world_p->currentState;

		World_switchToAndInitState(world_p, MENU_STATE);

		return;

	}

	world_p->scaling = false;
	if(world_p->actions[SCALE_ACTION].down){
		world_p->scaling = true;
	}
	if(!world_p->scalingByPlayerPosition){
		if(world_p->actions[SCALE_ACTION].downedNoRepeat){
			//playSound("begin-scaling");
			scalingSoundCounter = 0;
		}
		if(world_p->actions[SCALE_ACTION].upped){
			//playSound("end-scaling");
		}
	}

	world_p->lastScale = world_p->scale;
	world_p->deltaScale = world_p->scale;

	Player *player_p = &world_p->player;

	Vec2f_set(&player_p->physics.acceleration, 0, 0);

	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->lastScale = bodyPair_p->scale;
		bodyPair_p->lastScaleExponent = bodyPair_p->scaleExponent;
	
	}

	//control scale
	if(world_p->scalingByPlayerPosition){

		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			bodyPair_p->scale.x = playerBodyPair_p->originBody.pos.x / playerBodyPair_p->body.pos.x;
			bodyPair_p->scale.y = (world_p->levelHeight - playerBodyPair_p->originBody.pos.y - playerBodyPair_p->originBody.size.y) / (world_p->levelHeight - playerBodyPair_p->body.pos.y - playerBodyPair_p->body.size.y);

		}
	
	}else if(world_p->scaling){

		for(int i = 0; i < world_p->bodyPairs.length; i++){
			
			BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			if(world_p->actions[LEFT_ACTION].down){
				bodyPair_p->scaleExponent.x++;
				//bodyPair_p->scale.x -= world_p->scaleSpeed;
				//bodyPair_p->scale.x *= 1 + world_p->scaleSpeed / world_p->levelWidth;
				//bodyPair_p->scale.x *= 1 + world_p->scaleSpeed * world_p->levelHeight / world_p->levelWidth * sqrt(sqrt(bodyPair_p->scale.x));
				//bodyPair_p->scaleIndexX++;
			}
			if(world_p->actions[RIGHT_ACTION].down){
				bodyPair_p->scaleExponent.x--;
				//bodyPair_p->scale.x += world_p->scaleSpeed;
				//bodyPair_p->scale.x /= 1 + world_p->scaleSpeed / world_p->levelWidth;
				//bodyPair_p->scale.x /= 1 + world_p->scaleSpeed * world_p->levelHeight / world_p->levelWidth * sqrt(sqrt(bodyPair_p->scale.x));
				//bodyPair_p->scaleIndexX--;
			}
			if(world_p->actions[DOWN_ACTION].down){
				bodyPair_p->scaleExponent.y++;
				//bodyPair_p->scale.y -= world_p->scaleSpeed;
				//bodyPair_p->scale.y *= 1 + world_p->scaleSpeed / world_p->levelHeight;
				//bodyPair_p->scale.y *= 1 + world_p->scaleSpeed * sqrt(sqrt(bodyPair_p->scale.y));
				//bodyPair_p->scaleIndexY++;
			}
			if(world_p->actions[UP_ACTION].down){
				bodyPair_p->scaleExponent.y--;
				//bodyPair_p->scale.y += world_p->scaleSpeed;
				//bodyPair_p->scale.y /= 1 + world_p->scaleSpeed / world_p->levelHeight;
				//bodyPair_p->scale.y /= 1 + world_p->scaleSpeed * sqrt(sqrt(bodyPair_p->scale.y));
				//bodyPair_p->scaleIndexY--;
			}

			bodyPair_p->scale = World_BodyPair_getScaleFromExponent(world_p, bodyPair_p);
			//bodyPair_p->lastScale = World_BodyPair_getLastScaleFromExponent(world_p, bodyPair_p);


			/*
			if(bodyPair_p->scale.x < 1 / world_p->levelWidth / 100
			|| bodyPair_p->scale.x >= world_p->levelWidth * 100){
				//bodyPair_p->scale.x = bodyPair_p->lastScale.x;
				//bodyPair_p->scale.x = bodyPair_p->lastScale.x;
			}
			if(bodyPair_p->scale.y < 1 / world_p->levelHeight / 100
			|| bodyPair_p->scale.y >= world_p->levelHeight * 100){
				//bodyPair_p->scale.y = bodyPair_p->lastScale.y;
				//bodyPair_p->scale.y = bodyPair_p->lastScale.y;
			}
			*/

		}

		/*
		if(world_p->actions[LEFT_ACTION].down){
			world_p->scale.x *= 1 + world_p->scaleSpeed * world_p->levelHeight / world_p->levelWidth * sqrt(sqrt(world_p->scale.x));
			//world_p->scale.x *= 1 + (world_p->scaleSpeed / world_p->levelWidth);
		}
		if(world_p->actions[RIGHT_ACTION].down){
			//world_p->scale.x /= 1 + (world_p->scaleSpeed / world_p->levelWidth);
			world_p->scale.x /= 1 + world_p->scaleSpeed * world_p->levelHeight / world_p->levelWidth * sqrt(sqrt(world_p->scale.x));
			//world_p->scale.x *= 1 - world_p->scaleSpeed * HEIGHT / WIDTH;
			//world_p->scale.x -= world_p->scaleSpeed * HEIGHT / WIDTH;
		}
		if(world_p->actions[DOWN_ACTION].down){
			world_p->scale.y *= 1 + world_p->scaleSpeed * sqrt(sqrt(world_p->scale.y));
			//world_p->scale.y *= 1 + (world_p->scaleSpeed / world_p->levelHeight);
			//world_p->scale.y += world_p->scaleSpeed;
		}
		if(world_p->actions[UP_ACTION].down){
			world_p->scale.y /= 1 + world_p->scaleSpeed * sqrt(sqrt(world_p->scale.y));
			//world_p->scale.y /= 1 + (world_p->scaleSpeed / world_p->levelHeight);
			//world_p->scale.y *= 1 - world_p->scaleSpeed;
			//world_p->scale.y -= world_p->scaleSpeed;
		}
		*/

	}

	/*
	//limit scale
	if(world_p->scale.x < 1 / world_p->levelWidth / 100
	|| world_p->scale.x >= world_p->levelWidth * 100){
		world_p->scale.x = world_p->lastScale.x;
	}
	if(world_p->scale.y < 1 / world_p->levelHeight / 100
	|| world_p->scale.y >= world_p->levelHeight * 100){
		world_p->scale.y = world_p->lastScale.y;
	}
	*/

	//control player
	if(!world_p->scaling
	|| world_p->scalingByPlayerPosition){

		Physics *playerPhysics_p = &World_getBodyPairByID(world_p, player_p->bodyPairID)->physics;

		if(world_p->actions[LEFT_ACTION].down){
			playerPhysics_p->acceleration.x += -player_p->runAcceleration;
		}
		if(world_p->actions[RIGHT_ACTION].down){
			playerPhysics_p->acceleration.x += player_p->runAcceleration;
		}

		if((world_p->actions[JUMP_ACTION].down)
		&& playerPhysics_p->onGround){
			playerPhysics_p->velocity.y += player_p->jumpSpeed;
			//playSound("player-jump");
			//playSound("player-land");
		}

		if(!world_p->actions[JUMP_ACTION].down
		&& playerPhysics_p->velocity.y < 0){
			playerPhysics_p->velocity.y = 0;
		}

	}

	world_p->deltaScale = world_p->scale;
	Vec2f_sub(&world_p->deltaScale, world_p->lastScale);

	//play scaling sound
	//if(fabs(world_p->deltaScale.x) > 0
	//|| fabs(world_p->deltaScale.y) > 0){
		//if(scalingSoundCounter % 20 == 0){
			//playSound("scaling");
		//}
		//scalingSoundCounter++;
	//}

	//logic

	Body *playerBody_p = &World_getBodyPairByID(world_p, world_p->player.bodyPairID)->body;

	//check if player is dead
	if((playerBody_p->pos.y > HEIGHT + 20
	|| playerBody_p->size.x < 1
	|| playerBody_p->size.y < 1
	|| world_p->actions[RESTART_ACTION].downed)
	&& world_p->currentState == LEVEL_STATE){

		World_initLevel(world_p);

		return;

	}

	//control restart
	if(world_p->actions[RESTART_ACTION].downed){

		if(world_p->currentState == LEVEL_STATE){
			playerBody_p->pos.y = HEIGHT * 2;
		}

		if(world_p->currentState == LEVEL_HUB_STATE){
			playerBody_p->pos = world_p->saveData.playerPos;
			World_initLevelHub(world_p);
		}

	}

	//check if level is completed
	if(world_p->points.length == 0
	&& world_p->currentState == LEVEL_STATE){

		//add completed level to save data
		{
			bool alreadyCompleted = false;
			for(int i = 0; i < world_p->saveData.completedLevels.length; i++){

				char *checkLevelName = *((char **)Array_getItemPointerByIndex(&world_p->saveData.completedLevels, i));

				if(strcmp(checkLevelName, world_p->currentLevel) == 0){
					alreadyCompleted = true;
				}

			}

			if(!alreadyCompleted){
				char **completedLevel_p = Array_addItem(&world_p->saveData.completedLevels);
				*completedLevel_p = world_p->currentLevel;
			}
		}

		//check if player has unlocked a door key, and if so add to save data
		for(int i = 0; i < world_p->saveData.levelsWithDoorKey.length; i++){
			
			char *levelName_p = *((char **)Array_getItemPointerByIndex(&world_p->saveData.levelsWithDoorKey, i));

			if(strcmp(levelName_p, world_p->currentLevel) == 0){

				Vec2f *doorKeyPos_p = Array_addItem(&world_p->saveData.doorKeys);
				*doorKeyPos_p = world_p->saveData.playerPos;

				Array_removeItemByIndex(&world_p->saveData.levelsWithDoorKey, i);
				i--;

			}

		}

		World_fadeTransitionToState(world_p, LEVEL_HUB_STATE);

		return;

	}
	
	//update bodyPairs last bodies and make unstuck
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->lastBody = bodyPair_p->body;

		bodyPair_p->isStuck = false;
		
	}

	//scale x
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		//Vec2f scale = 
		//float scaleX = world_p->scalesX[bodyPair_p->scaleIndexX];
		//float lastScaleX = world_p->scalesX[bodyPair_p->lastScaleIndexX];
		Vec2f scale = bodyPair_p->scale;
		Vec2f lastScale = bodyPair_p->lastScale;
		Vec2f origin = world_p->origin;

		if(bodyPair_p->scaleType == NONE){
			scale = getVec2f(1, 1);
			lastScale = getVec2f(1, 1);
		}
		if(bodyPair_p->scaleType == ALL_FROM_TOP){
			origin = getVec2f(0, 0);
		}

		//printf("%f\n", scaleX);
		//printf("%i\n", bodyPair_p->scaleIndexX);

		Body_unScaleX(&bodyPair_p->body, origin.x, lastScale.x);

		Body_scaleX(&bodyPair_p->body, origin.x, scale.x);

		//BodyPair_World_setBodyFromScaleX(bodyPair_p, world_p);

		/*
		Vec2f scale = World_getScaleFromScaleType(world_p, bodyPair_p->scaleType);
		Vec2f lastScale = World_getLastScaleFromScaleType(world_p, bodyPair_p->scaleType);
		Vec2f origin = World_getOriginFromScaleType(world_p, bodyPair_p->scaleType);

		Body_unScaleX(&bodyPair_p->body, origin, lastScale);

		Body_scaleX(&bodyPair_p->body, origin, scale);
		*/
	
	}

	//handle scale collisions x
	Array collisions;
	Array_init(&collisions, sizeof(Collision));

	Array lastCollisions;
	Array_init(&lastCollisions, sizeof(Collision));

	for(int k = 0; k < 4; k++){

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			for(int j = 0; j < world_p->bodyPairs.length; j++){

				BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

				if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
				&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
				&& i != j){

					if(bodyPair1_p->lastBody.size.x < 1
					&& !(bodyPair1_p->collisionWeight == STATIC
					&& bodyPair2_p->collisionWeight == MOVABLE)){
						bodyPair1_p->body.size.x = bodyPair1_p->lastBody.size.x;
						bodyPair1_p->body.pos.x = bodyPair1_p->lastBody.pos.x;
						bodyPair1_p->scale.x = bodyPair1_p->lastScale.x;
						//bodyPair1_p->scaleIndexX = bodyPair1_p->lastScaleIndexX;
						bodyPair1_p->isStuck = true;
						continue;
					}

					int weakBodyPair = 1;

					bool bodyPair1IsMovable = false;
					bool bodyPair2IsMovable = false;

					if(bodyPair1_p->collisionWeight == MOVABLE){
						bodyPair1IsMovable = true;
					}
					if(bodyPair2_p->collisionWeight == MOVABLE){
						bodyPair2IsMovable = true;
					}

					for(int h = 0; h < lastCollisions.length; h++){

						Collision *collision_p = Array_getItemPointerByIndex(&lastCollisions, h);
						BodyPair *bodyPair3_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->heavierBodyPairIndex);

						if(bodyPair3_p->collisionWeight == STATIC){
							if(collision_p->lighterBodyPairIndex == i){
								bodyPair1IsMovable = false;
							}
							if(collision_p->lighterBodyPairIndex == j){
								bodyPair2IsMovable = false;
							}
						}
					
					}

					if(bodyPair1_p->collisionWeight == MOVABLE
					&& BodyPair_isScalable(bodyPair1_p)){
						bodyPair1IsMovable = true;
					}
					if(bodyPair2_p->collisionWeight == MOVABLE
					&& BodyPair_isScalable(bodyPair2_p)){
						bodyPair2IsMovable = true;
					}

					if(bodyPair1_p->body.pos.x + bodyPair1_p->body.size.x < bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x
					&& world_p->deltaScale.x < 0
					|| bodyPair1_p->body.pos.x + bodyPair1_p->body.size.x > bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x
					&& world_p->deltaScale.x > 0){
						weakBodyPair = 1;
					}else{
						weakBodyPair = 2;
					}

					if(bodyPair1IsMovable){
						weakBodyPair = 1;
					}
					if(bodyPair2IsMovable){
						weakBodyPair = 2;
					}

					if(!bodyPair1IsMovable
					&& !BodyPair_isScalable(bodyPair1_p)){
						weakBodyPair = 2;
					}
					if(!bodyPair2IsMovable
					&& !BodyPair_isScalable(bodyPair2_p)){
						weakBodyPair = 1;
					}

					if(bodyPair1_p->collisionWeight == STATIC
					&& !BodyPair_isScalable(bodyPair1_p)){
						weakBodyPair = 2;
					}
					if(bodyPair2_p->collisionWeight == STATIC
					&& !BodyPair_isScalable(bodyPair2_p)){
						weakBodyPair = 1;
					}

					Collision *collision_p = Array_addItem(&collisions);
					collision_p->oub = false;

					if(weakBodyPair == 1){
						collision_p->lighterBodyPairIndex = i;
						collision_p->heavierBodyPairIndex = j;
					}
					if(weakBodyPair == 2){
						collision_p->lighterBodyPairIndex = j;
						collision_p->heavierBodyPairIndex = i;
					}

				}

			}

			if(bodyPair1_p->body.pos.x < 0){
				Collision *collision_p = Array_addItem(&collisions);
				collision_p->lighterBodyPairIndex = i;
				collision_p->heavierBodyPairIndex = 0;
				collision_p->oub = true;
			}

		}

		if(collisions.length == 0){
			break;
		}

		for(int i = 0; i < collisions.length; i++){

			Collision *collision_p = Array_getItemPointerByIndex(&collisions, i);

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->lighterBodyPairIndex);
			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->heavierBodyPairIndex);

			if(collision_p->oub){
				BodyPair oubBodyPair;
				Body_init(&oubBodyPair.body, getVec2f(-200, 0), getVec2f(200, 0));
				oubBodyPair.lastBody = oubBodyPair.body;
				bodyPair2_p = &oubBodyPair;
			}

			float bodyPairCenterX = bodyPair1_p->lastBody.pos.x + bodyPair1_p->lastBody.size.x / 2;
			float bodyPair2CenterX = bodyPair2_p->lastBody.pos.x + bodyPair2_p->lastBody.size.x / 2;

			if(bodyPairCenterX < bodyPair2CenterX){
				bodyPair1_p->body.pos.x = bodyPair2_p->body.pos.x - bodyPair1_p->body.size.x;
			}
			if(bodyPairCenterX > bodyPair2CenterX){
				bodyPair1_p->body.pos.x = bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x;
			}

			if(!BodyPair_isScalable(bodyPair1_p)){
				continue;
			}

			for(int j = 0; j < lastCollisions.length; j++){

				Collision *collision2_p = Array_getItemPointerByIndex(&lastCollisions, j);

				if(collision_p->lighterBodyPairIndex == collision2_p->lighterBodyPairIndex
				&& collision_p->heavierBodyPairIndex != collision2_p->heavierBodyPairIndex){

					BodyPair *bodyPair3_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision2_p->heavierBodyPairIndex);

					if(collision2_p->oub){
						BodyPair oubBodyPair;
						Body_init(&oubBodyPair.body, getVec2f(-200, 0), getVec2f(200, 0));
						oubBodyPair.lastBody = oubBodyPair.body;
						bodyPair3_p = &oubBodyPair;
					}

					BodyPair *leftBodyPair_p;
					BodyPair *rightBodyPair_p;

					if(bodyPair2_p->body.pos.x < bodyPair3_p->body.pos.x){
						leftBodyPair_p = bodyPair2_p;
						rightBodyPair_p = bodyPair3_p;
					}else{
						leftBodyPair_p = bodyPair3_p;
						rightBodyPair_p = bodyPair2_p;
					}

					if(bodyPair1_p->body.pos.x <= leftBodyPair_p->body.pos.x
					|| bodyPair1_p->body.pos.x >= rightBodyPair_p->body.pos.x){
						continue;
					}

					bodyPair1_p->body.pos.x = leftBodyPair_p->body.pos.x + leftBodyPair_p->body.size.x;
					bodyPair1_p->body.size.x = rightBodyPair_p->body.pos.x - (leftBodyPair_p->body.pos.x + leftBodyPair_p->body.size.x);

				}
			
			}
			
		}

		if(k > 0){
			Array_free(&lastCollisions);
		}

		lastCollisions = collisions;
		Array_init(&collisions, sizeof(Collision));
	
	}

	/*
	//make scales proper x
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->scale.x = BodyPair_getScaleFromBodyX(bodyPair_p);

	}
	*/

	//scale y
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		//float scaleY = world_p->scalesX[bodyPair_p->scaleIndexY];
		//float lastScaleY = world_p->scalesX[bodyPair_p->lastScaleIndexY];
		//Vec2f origin = world_p->origin;

		//Body_unScaleY(&bodyPair_p->body, origin.y, lastScaleY);

		//Body_scaleY(&bodyPair_p->body, origin.y, scaleY);

		//BodyPair_World_setBodyFromScaleY(bodyPair_p, world_p);

		//Vec2f scale = World_getScaleFromScaleType(world_p, bodyPair_p->scaleType);
		//Vec2f lastScale = World_getLastScaleFromScaleType(world_p, bodyPair_p->scaleType);
		//Vec2f origin = World_getOriginFromScaleType(world_p, bodyPair_p->scaleType);

		Vec2f scale = bodyPair_p->scale;
		Vec2f lastScale = bodyPair_p->lastScale;
		Vec2f origin = world_p->origin;

		if(bodyPair_p->scaleType == NONE){
			scale = getVec2f(1, 1);
			lastScale = getVec2f(1, 1);
		}
		if(bodyPair_p->scaleType == ALL_FROM_TOP){
			origin = getVec2f(0, 0);
		}

		Body_unScaleY(&bodyPair_p->body, origin.y, lastScale.y);

		Body_scaleY(&bodyPair_p->body, origin.y, scale.y);
	
	}

	//handle scale collisions y
	Array_clear(&collisions);
	Array_clear(&lastCollisions);

	for(int k = 0; k < 4; k++){

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			for(int j = 0; j < world_p->bodyPairs.length; j++){

				BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

				if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
				&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
				&& i != j){

					if(bodyPair1_p->lastBody.size.y < 1
					&& !(bodyPair1_p->collisionWeight == STATIC
					&& bodyPair2_p->collisionWeight == MOVABLE)){
						bodyPair1_p->body.size.y = bodyPair1_p->lastBody.size.y;
						bodyPair1_p->body.pos.y = bodyPair1_p->lastBody.pos.y;
						bodyPair1_p->scale = bodyPair1_p->lastScale;
						//bodyPair1_p->scaleIndexY = bodyPair1_p->lastScaleIndexY;
						bodyPair1_p->isStuck = true;
						continue;
					}

					int weakBodyPair = 1;

					bool bodyPair1IsMovable = false;
					bool bodyPair2IsMovable = false;

					if(bodyPair1_p->collisionWeight == MOVABLE){
						bodyPair1IsMovable = true;
					}
					if(bodyPair2_p->collisionWeight == MOVABLE){
						bodyPair2IsMovable = true;
					}

					for(int h = 0; h < lastCollisions.length; h++){

						Collision *collision_p = Array_getItemPointerByIndex(&lastCollisions, h);
						BodyPair *bodyPair3_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->heavierBodyPairIndex);

						if(bodyPair3_p->collisionWeight == STATIC){
							if(collision_p->lighterBodyPairIndex == i){
								bodyPair1IsMovable = false;
							}
							if(collision_p->lighterBodyPairIndex == j){
								bodyPair2IsMovable = false;
							}
						}
					
					}

					if(bodyPair1_p->collisionWeight == MOVABLE
					&& BodyPair_isScalable(bodyPair1_p)){
						bodyPair1IsMovable = true;
					}
					if(bodyPair2_p->collisionWeight == MOVABLE
					&& BodyPair_isScalable(bodyPair2_p)){
						bodyPair2IsMovable = true;
					}

					if(bodyPair1_p->body.pos.y + bodyPair1_p->body.size.y > bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y
					&& world_p->deltaScale.y < 0
					|| bodyPair1_p->body.pos.y + bodyPair1_p->body.size.y < bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y
					&& world_p->deltaScale.y > 0){
						weakBodyPair = 1;
					}else{
						weakBodyPair = 2;
					}

					if(bodyPair1IsMovable){
						weakBodyPair = 1;
					}
					if(bodyPair2IsMovable){
						weakBodyPair = 2;
					}

					if(!bodyPair1IsMovable
					&& !BodyPair_isScalable(bodyPair1_p)){
						weakBodyPair = 2;
					}
					if(!bodyPair2IsMovable
					&& !BodyPair_isScalable(bodyPair2_p)){
						weakBodyPair = 1;
					}

					if(bodyPair1_p->collisionWeight == STATIC
					&& !BodyPair_isScalable(bodyPair1_p)){
						weakBodyPair = 2;
					}
					if(bodyPair2_p->collisionWeight == STATIC
					&& !BodyPair_isScalable(bodyPair2_p)){
						weakBodyPair = 1;
					}
					
					Collision *collision_p = Array_addItem(&collisions);
					collision_p->oub = false;

					if(weakBodyPair == 1){
						collision_p->lighterBodyPairIndex = i;
						collision_p->heavierBodyPairIndex = j;
					}
					if(weakBodyPair == 2){
						collision_p->lighterBodyPairIndex = j;
						collision_p->heavierBodyPairIndex = i;
					}

				}

			}

			if((bodyPair1_p->body.pos.y + bodyPair1_p->body.size.y > HEIGHT)
			&& bodyPair1_p->entityType != DOOR_KEY
			&& bodyPair1_p->entityType != PLAYER){
			//&& bodyPair1_p->scaleType != ALL_FROM_TOP
			//|| bodyPair1_p->body.pos.y < 0
			//&& bodyPair1_p->scaleType == ALL_FROM_TOP)
			//&& bodyPair1_p->entityHeader.ID != world_p->player.bodyPairID){
				printf("OUB COLLISION Y!\n");
				printf("%f, %f\n", bodyPair1_p->body.pos.y, bodyPair1_p->body.size.y);
				Collision *collision_p = Array_addItem(&collisions);
				collision_p->lighterBodyPairIndex = i;
				collision_p->heavierBodyPairIndex = 0;
				collision_p->oub = true;
			}

		}

		if(collisions.length == 0){
			break;
		}

		for(int i = 0; i < collisions.length; i++){

			Collision *collision_p = Array_getItemPointerByIndex(&collisions, i);

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->lighterBodyPairIndex);
			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->heavierBodyPairIndex);

			if(collision_p->oub){
				BodyPair oubBodyPair;
				Body_init(&oubBodyPair.body, getVec2f(0, HEIGHT), getVec2f(0, 200));
				//if(bodyPair1_p->scaleType == ALL_FROM_TOP){
					//oubBodyPair.body.pos.y = 0;
				//}
				oubBodyPair.lastBody = oubBodyPair.body;
				bodyPair2_p = &oubBodyPair;
			}

			float bodyPairCenterY = bodyPair1_p->lastBody.pos.y + bodyPair1_p->lastBody.size.y / 2;
			float bodyPair2CenterY = bodyPair2_p->lastBody.pos.y + bodyPair2_p->lastBody.size.y / 2;

			if(bodyPairCenterY < bodyPair2CenterY){
				bodyPair1_p->body.pos.y = bodyPair2_p->body.pos.y - bodyPair1_p->body.size.y;
			}
			if(bodyPairCenterY > bodyPair2CenterY){
				bodyPair1_p->body.pos.y = bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y;
			}

			if(!BodyPair_isScalable(bodyPair1_p)){
				continue;
			}

			for(int j = 0; j < lastCollisions.length; j++){

				Collision *collision2_p = Array_getItemPointerByIndex(&lastCollisions, j);

				if(collision_p->lighterBodyPairIndex == collision2_p->lighterBodyPairIndex
				&& collision_p->heavierBodyPairIndex != collision2_p->heavierBodyPairIndex){

					BodyPair *bodyPair3_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision2_p->heavierBodyPairIndex);

					if(collision2_p->oub){
						BodyPair oubBodyPair;
						Body_init(&oubBodyPair.body, getVec2f(0, HEIGHT), getVec2f(0, 200));
						//if(bodyPair1_p->scaleType == ALL_FROM_TOP){
							//oubBodyPair.body.pos.y = 0;
						//}
						oubBodyPair.lastBody = oubBodyPair.body;
						bodyPair3_p = &oubBodyPair;
					}

					BodyPair *upBodyPair_p;
					BodyPair *downBodyPair_p;

					if(bodyPair2_p->body.pos.y < bodyPair3_p->body.pos.y){
						upBodyPair_p = bodyPair2_p;
						downBodyPair_p = bodyPair3_p;
					}else{
						upBodyPair_p = bodyPair3_p;
						downBodyPair_p = bodyPair2_p;
					}

					if(bodyPair1_p->body.pos.y <= upBodyPair_p->body.pos.y
					|| bodyPair1_p->body.pos.y >= downBodyPair_p->body.pos.y){
						continue;
					}

					bodyPair1_p->body.pos.y = upBodyPair_p->body.pos.y + upBodyPair_p->body.size.y;
					bodyPair1_p->body.size.y = downBodyPair_p->body.pos.y - (upBodyPair_p->body.pos.y + upBodyPair_p->body.size.y);

				}
			
			}
			
		}

		if(k > 0){
			Array_free(&lastCollisions);
		}

		lastCollisions = collisions;
		Array_init(&collisions, sizeof(Collision));
	
	}

	Array_free(&collisions);
	Array_free(&lastCollisions);

	//apply physics
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->physics.acceleration.y += bodyPair_p->physics.gravity;

		//Vec2f_add(&bodyPair_p->physics.velocity, getMulVec2fFloat(bodyPair_p->physics.acceleration, world_p->deltaTime));
		Vec2f_add(&bodyPair_p->physics.velocity, bodyPair_p->physics.acceleration);

		//Vec2f resistance = bodyPair_p->physics.resistance;
		//resistance.x = pow(resistance.x, world_p->deltaTime);
		//resistance.y = pow(resistance.y, world_p->deltaTime);

		Vec2f_mul(&bodyPair_p->physics.velocity, bodyPair_p->physics.resistance);
		//printf("%f\n", resistance.x);

		//reset acceleration
		bodyPair_p->physics.acceleration = getVec2f(0, 0);
			
	}

	//move x
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
		Vec2f physicsScale = BodyPair_getPhysicsScale(bodyPair_p);

		if(bodyPair_p->body.size.x >= 1){
			bodyPair_p->body.pos.x += bodyPair_p->physics.velocity.x / physicsScale.x;
		}
	
	}

	//handle collisions x moving
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		if(bodyPair1_p->physics.velocity.x == 0){
			continue;
		}

		for(int j = 0; j < world_p->bodyPairs.length; j++){
			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			&& i != j
			&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
			&& bodyPair1_p->collisionWeight == MOVABLE
			&& bodyPair2_p->collisionWeight == STATIC){

				float bodyPair1CenterX = bodyPair1_p->lastBody.pos.x + bodyPair1_p->lastBody.size.x / 2;
				float bodyPair2CenterX = bodyPair2_p->lastBody.pos.x + bodyPair2_p->lastBody.size.x / 2;

				if(bodyPair1CenterX < bodyPair2CenterX){
					bodyPair1_p->body.pos.x = bodyPair2_p->body.pos.x - bodyPair1_p->body.size.x;
				}
				if(bodyPair1CenterX > bodyPair2CenterX){
					bodyPair1_p->body.pos.x = bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x;
				}

				bodyPair1_p->physics.velocity.x = 0;
				
			}

		}
	}

	//handle oub x
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		if(bodyPair_p->body.pos.x < 0){
			bodyPair_p->body.pos.x = 0;
			bodyPair_p->physics.velocity.x = 0;
		}

	}

	//move y
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
		Vec2f physicsScale = BodyPair_getPhysicsScale(bodyPair_p);

		if(bodyPair_p->body.size.y >= 1){
			bodyPair_p->body.pos.y += bodyPair_p->physics.velocity.y / physicsScale.y;
		}
	
	}

	//handle collisions y moving
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		if(bodyPair1_p->physics.velocity.y == 0){
			continue;
		}

		bool touchedGround = false;
		bodyPair1_p->physics.landed = false;

		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			&& i != j
			&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
			&& bodyPair1_p->collisionWeight == MOVABLE
			&& bodyPair2_p->collisionWeight == STATIC){

				float bodyPair1CenterY = bodyPair1_p->lastBody.pos.y + bodyPair1_p->lastBody.size.y / 2;
				float bodyPair2CenterY = bodyPair2_p->lastBody.pos.y + bodyPair2_p->lastBody.size.y / 2;

				if(bodyPair1CenterY < bodyPair2CenterY){
					bodyPair1_p->body.pos.y = bodyPair2_p->body.pos.y - bodyPair1_p->body.size.y;
					touchedGround = true;
				}
				if(bodyPair1CenterY > bodyPair2CenterY){
					bodyPair1_p->body.pos.y = bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y;
				}

				bodyPair1_p->physics.velocity.y = 0;
				
			}

		}

		if(touchedGround){
			if(!bodyPair1_p->physics.onGround){
				bodyPair1_p->physics.landed = true;
			}
			bodyPair1_p->physics.onGround = true;
		}else{
			bodyPair1_p->physics.onGround = false;
		}

		if(bodyPair1_p->physics.landed
		&& world_p->playerHasLanded
		&& bodyPair1_p->entityType == PLAYER){
		//&& !(world_p->actions[JUMP_ACTION].down
		//&& !world_p->scaling)){
			//playSound("player-land");
		}

	}

	//update player facing
	{
		Physics *playerPhysics_p = &World_getBodyPairByID(world_p, player_p->bodyPairID)->physics;

		if(playerPhysics_p->velocity.x > 0){
			player_p->facing = RIGHT;
		}
		if(playerPhysics_p->velocity.x < 0){
			player_p->facing = LEFT;
		}

		//check if player has landed
		if(playerPhysics_p->onGround){
			world_p->playerHasLanded = true;
		}
	}

	//check if player collides with door keys
	bool playerGotKey = false;
	for(int i = 0; i < world_p->doorKeys.length; i++){

		DoorKey *doorKey_p = Array_getItemPointerByIndex(&world_p->doorKeys, i);
		BodyPair *doorKeyBodyPair_p = World_getBodyPairByID(world_p, doorKey_p->bodyPairID);
		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);

		Vec2f playerPhysicsScale = BodyPair_getPhysicsScale(playerBodyPair_p);
		Vec2f doorKeyPhysicsScale = BodyPair_getPhysicsScale(doorKeyBodyPair_p);

		Vec2f playerHand = getVec2f(playerBodyPair_p->body.pos.x + 10 / playerPhysicsScale.x, playerBodyPair_p->body.pos.y + 15 / playerPhysicsScale.y);

		if(player_p->facing == LEFT){
			playerHand.x -= 6 / playerPhysicsScale.x;
		}

		Vec2f doorKeyHold = getVec2f(doorKeyBodyPair_p->body.pos.x, doorKeyBodyPair_p->body.pos.y + doorKeyBodyPair_p->body.size.y);

		if(player_p->facing == LEFT){
			doorKeyHold.x += doorKeyBodyPair_p->body.size.x;
		}

		Vec2f velocity = playerHand;
		Vec2f_sub(&velocity, doorKeyHold);
		Vec2f_mul(&velocity, doorKeyPhysicsScale);

		float mag = getMagVec2f(velocity);

		Vec2f_normalize(&velocity);
		Vec2f_mulByFloat(&velocity, mag);
		//Vec2f_divByFactor(&velocity, 3);

		if(checkBodyToBodyCol(playerBodyPair_p->body, doorKeyBodyPair_p->body)
		&& !playerGotKey){

			playerGotKey = true;

			doorKeyBodyPair_p->physics.velocity = velocity;
			doorKey_p->facing = player_p->facing;

		}

	}

	if(playerGotKey){
		if(!player_p->holdingKey){
			//playSound("pickup-key");
		}
		player_p->holdingKey = true;
	}else{
		player_p->holdingKey = false;
	}

	//check if door keys collide with doors
	for(int i = 0; i < world_p->doors.length; i++){
		for(int j = 0; j < world_p->doorKeys.length; j++){
			
			Door *door_p = Array_getItemPointerByIndex(&world_p->doors, i);
			DoorKey *doorKey_p = Array_getItemPointerByIndex(&world_p->doorKeys, j);
			BodyPair *doorBodyPair_p = World_getBodyPairByID(world_p, door_p->bodyPairID);
			BodyPair *doorKeyBodyPair_p = World_getBodyPairByID(world_p, doorKey_p->bodyPairID);

			if(checkBodyPairToBodyPairCollision(*doorBodyPair_p, *doorKeyBodyPair_p)){

				//playSound("open-door");

				World_removeDoorByID(world_p, door_p->entityHeader.ID);
				World_removeDoorKeyByID(world_p, doorKey_p->entityHeader.ID);

				if(world_p->currentState == LEVEL_HUB_STATE){
					//BÖR FUNGERA, då de läggs till i samma ordning som de finns i saveData, KAN DOCK VARA ELLER BLI BUGGIGT!!!
					Array_removeItemByIndex(&world_p->saveData.doors, i);
					Array_removeItemByIndex(&world_p->saveData.doorKeys, j);
				}

				i--;
				j--;

			}

		}
	}

	//check if player collides with points
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		//Body *pointBody_p = &((BodyPair *)Array_getItemPointerByID(&world_p->bodyPairs, point_p->bodyPairID))->body;
		BodyPair *pointBodyPair_p = Array_getItemPointerByID(&world_p->bodyPairs, point_p->bodyPairID);
		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);
	
		//if(checkBodyToBodyColRoundToFloat(playerBodyPair_p->body, *pointBody_p)){
		if(checkBodyPairToBodyPairCollision(*pointBodyPair_p, *playerBodyPair_p)){

			World_removePointByID(world_p, point_p->entityHeader.ID);

			i--;
			
			//playSound("pickup-star");

		}

	}

	//check if player collides with level doors
	for(int i = 0; i < world_p->levelDoors.length; i++){

		LevelDoor *levelDoor_p = Array_getItemPointerByIndex(&world_p->levelDoors, i);
		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);
	
		if(checkBodyToBodyCol(playerBodyPair_p->body, levelDoor_p->body)
		&& world_p->playerHasLanded){

			world_p->currentLevel = levelDoor_p->levelName;

			world_p->saveData.playerPos = playerBodyPair_p->body.pos;

			World_fadeTransitionToState(world_p, LEVEL_STATE);

			//playSound("enter-level-door");

		}

		/*
		//check if player is below level door
		if(playerBodyPair_p->body.pos.x + playerBodyPair_p->body.size.x > levelDoor_p->body.pos.x
		&& playerBodyPair_p->body.pos.x < levelDoor_p->body.pos.x + levelDoor_p->body.size.x
		&& playerBodyPair_p->body.pos.y > levelDoor_p->body.pos.y
		&& playerBodyPair_p->body.pos.y < levelDoor_p->body.pos.y + 70){

			if(!levelDoor_p->hasPlayerBelow){

				Particle *hoverTextParticle_p = World_getParticleByID(world_p, levelDoor_p->hoverTextParticleID);

				union ParticleProperty targetAlpha;
				targetAlpha.alpha = 1;
				Particle_addEvent(hoverTextParticle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, targetAlpha, 0, 500 / 60);

			}

			levelDoor_p->hasPlayerBelow = true;

		}else{

			if(!levelDoor_p->hasPlayerBelow){
				Particle *hoverTextParticle_p = World_getParticleByID(world_p, levelDoor_p->hoverTextParticleID);

				union ParticleProperty targetAlpha;
				targetAlpha.alpha = 0;
				Particle_addEvent(hoverTextParticle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, targetAlpha, 0, 300 / 60);
			}

			levelDoor_p->hasPlayerBelow = false;
		}
		*/

	}

	//check collision with scale fields
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->scaleType = bodyPair_p->originScaleType;

		for(int j = 0; j < world_p->scaleFields.length; j++){

			ScaleField *scaleField_p = Array_getItemPointerByIndex(&world_p->scaleFields, j);

			if(floor(bodyPair_p->body.pos.x + bodyPair_p->body.size.x) > floor(scaleField_p->body.pos.x)
			&& floor(bodyPair_p->body.pos.x) < floor(scaleField_p->body.pos.x + scaleField_p->body.size.x)
			&& floor(bodyPair_p->body.pos.y + bodyPair_p->body.size.y) > floor(scaleField_p->body.pos.y)
			&& floor(bodyPair_p->body.pos.y) < floor(scaleField_p->body.pos.y + scaleField_p->body.size.y)
					//checkBodyToBodyColCastToInt(bodyPair_p->body, scaleField_p->body)
			){

				bodyPair_p->scaleType = scaleField_p->scaleType;
				
			}
		
		}
	
	}

	/*
	//add particles to scale fields
	for(int i = 0; i < world_p->scaleFields.length; i++){

		ScaleField *scaleField_p = Array_getItemPointerByIndex(&world_p->scaleFields, i);

		scaleField_p->particleCounter++;

		float area = scaleField_p->body.size.x * scaleField_p->body.size.y;
		int frequency = 10;

		if(scaleField_p->particleCounter % frequency == 0){

			Vec2f pos = scaleField_p->body.pos;
			Vec2f size = getVec2f(round(3 + getRandom() * 2), 3 + round(getRandom() * 2));

			pos.x += 5 + getRandom() * (scaleField_p->body.size.x - 12);
			pos.y += 5 + getRandom() * (scaleField_p->body.size.y - 12);

			size_t spriteIndex = World_addSprite(world_p, pos, size, SCALE_TYPE_COLORS[scaleField_p->scaleType], "obstacle", 0, GAME_LAYER_PARTICLES);
			Particle *particle_p = World_addParticle(world_p, spriteIndex);

			union ParticleProperty targetAlpha1;
			union ParticleProperty targetAlpha2;
			targetAlpha1.alpha = 0.5 + getRandom() * 0.3;
			targetAlpha2.alpha = 0;

			Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, targetAlpha1, 0, 2000 / 60);
			Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, targetAlpha2, 5000 / 60, 2000 / 60);
			Particle_addRemoveEvent(particle_p, 7000 / 60);

		}

	}
	*/

	//update particles
	for(int i = 0; i < world_p->particles.length; i++){

		Particle *particle_p = Array_getItemPointerByIndex(&world_p->particles, i);

		//little optimization
		if(particle_p->events.length == 0){
			continue;
		}

		Sprite *sprite_p = World_getSpriteByIndex(world_p, particle_p->spriteIndex);

		for(int j = 0; j < particle_p->events.length; j++){

			ParticleEvent *particleEvent_p = Array_getItemPointerByIndex(&particle_p->events, j);

			if(particle_p->counter > particleEvent_p->activationTime + particleEvent_p->duration){

				Array_removeItemByIndex(&particle_p->events, j);
				j--;

			}

			if(particle_p->counter >= particleEvent_p->activationTime
			&& particle_p->counter <= particleEvent_p->activationTime + particleEvent_p->duration){

				if(particleEvent_p->type == PARTICLE_REMOVE_EVENT){
					World_removeParticleByID(world_p, particle_p->entityHeader.ID);
					i--;
					break;
				}

				if(particleEvent_p->propertyType == PARTICLE_ALPHA){

					if(particle_p->counter == particleEvent_p->activationTime){
						particleEvent_p->startValue.alpha = sprite_p->alpha;
					}

					if(particleEvent_p->type == PARTICLE_SET_EVENT){
						sprite_p->alpha = particleEvent_p->targetValue.alpha;
					}

					if(particleEvent_p->type == PARTICLE_LINEAR_FADE_EVENT){
						sprite_p->alpha = particleEvent_p->startValue.alpha + (particleEvent_p->targetValue.alpha - particleEvent_p->startValue.alpha) * (particle_p->counter - particleEvent_p->activationTime) / particleEvent_p->duration;
					}
				
				}
				
			}
		
		}

		Vec2f_add(&particle_p->physics.velocity, particle_p->physics.acceleration);
		Vec2f_add(&particle_p->body.pos, particle_p->physics.acceleration);

		particle_p->counter++;

		/*
		if(particle_p->type == FADE_IN_PARTICLE){

			Sprite *sprite_p = World_getSpriteByIndex(world_p, particle_p->spriteIndex);

			sprite_p->alpha += 0.01;

			if(sprite_p->alpha > 1){
				sprite_p->alpha = 1;
			}

			particle_p->counter++;
		
		}

		if(particle_p->type == LEVEL_COMPLETE_PARTICLE){

			if(particle_p->activationCounter == 0){
				particle_p->body.pos.x += 5;
				particle_p->body.pos.y += 3;
				particle_p->body.size.x = 10;
				particle_p->body.size.y = 10;
				World_getSpriteByIndex(world_p, particle_p->spriteIndex)->texture = "point";
			}

			particle_p->activationCounter--;

			if(particle_p->activationCounter > 0){
				continue;
			}

			Sprite *sprite_p = World_getSpriteByIndex(world_p, particle_p->spriteIndex);

			//change to target color
			float colorChangeSpeed = 0.02;
			if(colorChangeSpeed < fabs(sprite_p->color.x - particle_p->targetColor.x)){
				sprite_p->color.x += colorChangeSpeed * Number_normalize(particle_p->targetColor.x - sprite_p->color.x);
			}
			if(colorChangeSpeed < fabs(sprite_p->color.y - particle_p->targetColor.y)){
				sprite_p->color.y += colorChangeSpeed * Number_normalize(particle_p->targetColor.y - sprite_p->color.y);
			}
			if(colorChangeSpeed < fabs(sprite_p->color.z - particle_p->targetColor.z)){
				sprite_p->color.z += colorChangeSpeed * Number_normalize(particle_p->targetColor.z - sprite_p->color.z);
			}

			//handle particle physics
			particle_p->physics.acceleration.y = 0.05;

			if(particle_p->physics.velocity.y > 1.5){

				if(!particle_p->targeting){
					particle_p->physics.velocity.x += 7;
					particle_p->physics.velocity.y -= 2.5;
				}

				particle_p->targeting = true;

			}

			if(particle_p->targeting){

				Vec2f target = { 0, 250 };

				particle_p->physics.acceleration = target;
				Vec2f_sub(&particle_p->physics.acceleration, &particle_p->body.pos);
				Vec2f_normalize(&particle_p->physics.acceleration);
				Vec2f_mulByFactor(&particle_p->physics.acceleration, 0.8);
			
			}

			Vec2f_add(&particle_p->physics.velocity, &particle_p->physics.acceleration);

			particle_p->body.pos.y += particle_p->physics.velocity.y;
			particle_p->body.pos.x += particle_p->physics.velocity.x;

			if(particle_p->body.pos.x < 0){
				World_removeParticleByID(world_p, particle_p->entityHeader.ID);
				i--;
			}
		
		}
	*/
	
	}

	//update sprites

	//update obstacle sprites
	for(int i = 0; i < world_p->obstacles.length; i++){

		Obstacle *obstacle_p = Array_getItemPointerByIndex(&world_p->obstacles, i);

		BodyPair *obstacleBodyPair_p = World_getBodyPairByID(world_p, obstacle_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, obstacle_p->spriteIndex);

		sprite_p->body = obstacleBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[obstacleBodyPair_p->scaleType];
		if(world_p->scaling
		|| world_p->scalingByPlayerPosition){
			sprite_p->color = SCALING_SCALE_TYPE_COLORS[obstacleBodyPair_p->scaleType];
		}
		//sprite_p->color = COLOR_HOUSE;

		Vec2f scale = BodyPair_getPhysicsScale(obstacleBodyPair_p);

	}

	//update point sprites
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		BodyPair *pointBodyPair_p = World_getBodyPairByID(world_p, point_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, point_p->spriteIndex);

		sprite_p->body = pointBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[pointBodyPair_p->scaleType];
		if(world_p->scaling
		|| world_p->scalingByPlayerPosition){
			sprite_p->color = SCALING_SCALE_TYPE_COLORS[pointBodyPair_p->scaleType];
		}

	}

	//update door sprites
	for(int i = 0; i < world_p->doors.length; i++){

		Door *door_p = Array_getItemPointerByIndex(&world_p->doors, i);

		BodyPair *doorBodyPair_p = World_getBodyPairByID(world_p, door_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, door_p->spriteIndex);

		sprite_p->body = doorBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[doorBodyPair_p->scaleType];
		if(world_p->scaling
		|| world_p->scalingByPlayerPosition){
			sprite_p->color = SCALING_SCALE_TYPE_COLORS[doorBodyPair_p->scaleType];
		}

	}

	//update door key sprites
	for(int i = 0; i < world_p->doorKeys.length; i++){

		DoorKey *doorKey_p = Array_getItemPointerByIndex(&world_p->doorKeys, i);

		BodyPair *doorKeyBodyPair_p = World_getBodyPairByID(world_p, doorKey_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, doorKey_p->spriteIndex);

		sprite_p->body = doorKeyBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[doorKeyBodyPair_p->scaleType];
		if(world_p->scaling
		|| world_p->scalingByPlayerPosition){
			sprite_p->color = SCALING_SCALE_TYPE_COLORS[doorKeyBodyPair_p->scaleType];
		}

		sprite_p->facing = doorKey_p->facing;

		sprite_p->texture = "door-key";
		sprite_p->alpha = 1;

		//sprite_p = World_Sprite_setToLayer_returnsNewPointer(world_p, sprite_p, doorKey_p->spriteIndex, GAME_LAYER_DOOR_KEYS);

		if(doorKeyBodyPair_p->isStuck){

			Vec2f scale = doorKeyBodyPair_p->scale;
			Vec2f stuckScale = doorKeyBodyPair_p->scale;
			Vec2f origin = World_getOriginFromScaleType(world_p, doorKeyBodyPair_p->scaleType);

			stuckScale.x /= 1 + world_p->scaleSpeed / world_p->levelWidth;
			stuckScale.y /= 1 + world_p->scaleSpeed / world_p->levelHeight;

			//stuckScale.x /= 1 + world_p->scaleSpeed * world_p->levelHeight / world_p->levelWidth * sqrt(sqrt(stuckScale.x));
			//stuckScale.y /= 1 + world_p->scaleSpeed * sqrt(sqrt(stuckScale.y));

			//float scaleX = world_p->scalesX[doorKeyBodyPair_p->scaleIndexX];
			//float scaleY = world_p->scalesY[doorKeyBodyPair_p->scaleIndexY];
			//float stuckScaleX = world_p->scalesX[doorKeyBodyPair_p->scaleIndexX - 1];
			//float stuckScaleY = world_p->scalesY[doorKeyBodyPair_p->scaleIndexY - 1];

			Body_unScaleX(&sprite_p->body, origin.x, scale.x);
			Body_unScaleY(&sprite_p->body, origin.y, scale.y);
			Body_scaleX(&sprite_p->body, origin.x, stuckScale.x);
			Body_scaleY(&sprite_p->body, origin.y, stuckScale.y);

			sprite_p->color = COLOR_RED;
			sprite_p->texture = "obstacle";
			//sprite_p = World_Sprite_setToLayer_returnsNewPointer(world_p, sprite_p, GAME_LAYER_BLOCKED_ENTITIES);

		}

	}

	//update scale field sprites
	for(int i = 0; i < world_p->scaleFields.length; i++){

		ScaleField *scaleField_p = Array_getItemPointerByIndex(&world_p->scaleFields, i);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, scaleField_p->spriteIndex);

		sprite_p->body = scaleField_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[scaleField_p->scaleType];

	}

	//update particle sprites
	for(int i = 0; i < world_p->particles.length; i++){

		Particle *particle_p = Array_getItemPointerByIndex(&world_p->particles, i);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, particle_p->spriteIndex);

		//sprite_p->body = particle_p->body;

		//sprite_p->alpha = 1;

		//if(particle_p->activationCounter > 0){
			//sprite_p->alpha = 0;
		//}

		//sprite_p->color = SCALE_TYPE_COLORS[particle_p->scaleType];

	}

	//update player sprite
	{
		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, world_p->player.bodyPairID);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, world_p->player.spriteIndex);

		sprite_p->body = playerBodyPair_p->body;
		sprite_p->body.pos.y = (sprite_p->body.pos.y);

		sprite_p->color = SCALE_TYPE_COLORS[playerBodyPair_p->scaleType];
		if(world_p->scaling
		|| world_p->scalingByPlayerPosition){
			sprite_p->color = SCALING_SCALE_TYPE_COLORS[playerBodyPair_p->scaleType];
		}

		sprite_p->facing = world_p->player.facing;
	}

	//fade out title text
	BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, world_p->player.bodyPairID);
	if(playerBodyPair_p->body.pos.x > 200
	&& playerBodyPair_p->physics.onGround
	&& !SaveData_hasFlag(&world_p->saveData, "removed-title-text")){

		int duration = 1000 / 60;

		union ParticleProperty targetAlpha;
		targetAlpha.alpha = 0;

		Particle *titleTextParticle_p = World_getParticleByID(world_p, world_p->titleTextParticleID);
		Particle *movementKeysTextParticle_p = World_getParticleByID(world_p, world_p->movementKeysTextParticleID);
		Particle *menuKeyTextParticle_p = World_getParticleByID(world_p, world_p->menuKeyTextParticleID);

		Particle_addEvent(titleTextParticle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, targetAlpha, 0, duration);
		Particle_addEvent(movementKeysTextParticle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, targetAlpha, 0, duration);
		Particle_addEvent(menuKeyTextParticle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, targetAlpha, 0, duration);

		Particle_addRemoveEvent(titleTextParticle_p, duration);
		Particle_addRemoveEvent(movementKeysTextParticle_p, duration);
		Particle_addRemoveEvent(menuKeyTextParticle_p, duration);

		SaveData_addFlag(&world_p->saveData, "removed-title-text");

	}

	//update offset
	if(world_p->currentState == LEVEL_HUB_STATE){

		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, world_p->player.bodyPairID);

		float cameraSpeedX = 1;

		world_p->cameraTarget.x = (WIDTH / 2 - playerBodyPair_p->body.pos.x);
		float distX = fabs(world_p->cameraTarget.x - world_p->cameraPos.x);

		cameraSpeedX = 5;

		float playerPositionAreaX = 5150;

		if(playerBodyPair_p->body.pos.x > playerPositionAreaX
		&& playerBodyPair_p->body.pos.x < playerPositionAreaX + WIDTH / 2){
			world_p->cameraTarget.x = -playerPositionAreaX;
			//cameraSpeedX = 40;
			cameraSpeedX = 35;
		}

		float cameraSpeedY = 20;

		if(playerBodyPair_p->body.pos.y > 0){
			world_p->cameraTarget.y = 0;
		}
		if(playerBodyPair_p->body.pos.y < 0){
			world_p->cameraTarget.y = HEIGHT;
		}
		if(playerBodyPair_p->body.pos.y < -HEIGHT){
			world_p->cameraTarget.y = 2 * HEIGHT;
		}
		if(playerBodyPair_p->body.pos.y < -HEIGHT * 2){
			world_p->cameraTarget.y = 2.8 * HEIGHT;
		}

		if(playerBodyPair_p->body.pos.x < 400){

			world_p->cameraTarget.y = HEIGHT + 70;

			if(playerBodyPair_p->body.pos.y < -HEIGHT * 1.5){
				world_p->cameraTarget.y = HEIGHT * 2;
			}
			if(playerBodyPair_p->body.pos.y < -HEIGHT * 2){
				world_p->cameraTarget.y = HEIGHT * 2.8;
			}

			if(playerBodyPair_p->body.pos.y > 140 - HEIGHT){
				world_p->cameraTarget.y = HEIGHT - 70;
			}
			if(playerBodyPair_p->body.pos.y > 270 - HEIGHT){
				world_p->cameraTarget.y = 30;
			}
			if(playerBodyPair_p->body.pos.y > 150){
				world_p->cameraTarget.y = 0;
			}

		}

		if(playerBodyPair_p->body.pos.y < -HEIGHT * 2.8 + 100){
			world_p->cameraTarget.y = -playerBodyPair_p->body.pos.y + HEIGHT - 100;
			cameraSpeedY = 10;
		}
		if(playerBodyPair_p->body.pos.y < -HEIGHT * 3.8 + 100){
			cameraSpeedY = 5;
		}

		world_p->cameraPos.x += -(world_p->cameraPos.x - world_p->cameraTarget.x) / cameraSpeedX;
		world_p->cameraPos.y += -(world_p->cameraPos.y - world_p->cameraTarget.y) / cameraSpeedY;

		if(world_p->snapCamera){
			world_p->cameraPos = world_p->cameraTarget;
			if(!SaveData_hasFlag(&world_p->saveData, "removed-title-text")){
				world_p->cameraPos.y -= 250;
			}
			world_p->snapCamera = false;
		}

		world_p->renderer.offset.x = (world_p->cameraPos.x);
		world_p->renderer.offset.y = (world_p->cameraPos.y);

		if(world_p->renderer.offset.x > 0){
			world_p->renderer.offset.x = 0;
		}
	
	}

	//update star background sprite
	if(world_p->currentState == LEVEL_HUB_STATE){

		Sprite *sprite_p = World_getSpriteByIndex(world_p, world_p->starBackgroundSpriteIndex);

		sprite_p->body.pos.x = -world_p->renderer.offset.x * 0.3;
		sprite_p->body.pos.y = (-world_p->renderer.offset.y - HEIGHT * 8) * 0.4;

	}

}
