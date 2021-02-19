#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

typedef struct Collision{
	unsigned int lighterBodyPairIndex;
	unsigned int heavierBodyPairIndex;
	bool oub;
}Collision;

int blockerAnimationCount = 25;

size_t levelStateFadeTransitionID = 6900;//så att det inte krockar första gången

void World_initLevel(World *world_p){

	for(int i = 0; i < LEVELS_LENGTH; i++){
		if(strcmp(world_p->currentLevel, levels[i].name) == 0){

			levels[i].generate(world_p);

		}
	}

	world_p->levelWidth = WIDTH;
	world_p->levelHeight = HEIGHT;

	world_p->renderer.offset = getVec2f(0, 0);

}

void World_levelState(World *world_p){

	if(world_p->fadeTransitionCounter > FADE_TRANSITION_TIME / 2
	&& world_p->points.length == 0){
		return;
	}

	printf("---\n");

	if(world_p->actions[MENU_ACTION].downed){

		world_p->stateBeforeOpeningMenu = world_p->currentState;

		World_switchToAndInitState(world_p, MENU_STATE);

		return;

	}

	world_p->scaling = false;
	if(world_p->actions[SCALE_ACTION].down){
		world_p->scaling = true;
	}

	world_p->lastScale = world_p->scale;
	world_p->deltaScale = world_p->scale;

	Player *player_p = &world_p->player;

	Vec2f_set(&player_p->physics.acceleration, 0, 0);

	//control scale
	if(world_p->scalingByPlayerPosition){

		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);

		world_p->scale.x = playerBodyPair_p->originBody.pos.x / playerBodyPair_p->body.pos.x;
		world_p->scale.y = (world_p->levelHeight - playerBodyPair_p->originBody.pos.y - playerBodyPair_p->originBody.size.y) / (world_p->levelHeight - playerBodyPair_p->body.pos.y - playerBodyPair_p->body.size.y);
	
	}else if(world_p->scaling){

		if(world_p->actions[LEFT_ACTION].down){
			world_p->scale.x *= 1 + world_p->scaleSpeed * world_p->levelHeight / world_p->levelWidth * sqrt(sqrt(world_p->scale.x));
			//world_p->scale.x += world_p->scaleSpeed * HEIGHT / WIDTH;
		}
		if(world_p->actions[RIGHT_ACTION].down){
			world_p->scale.x /= 1 + world_p->scaleSpeed * world_p->levelHeight / world_p->levelWidth * sqrt(sqrt(world_p->scale.x));
			//world_p->scale.x *= 1 - world_p->scaleSpeed * HEIGHT / WIDTH;
			//world_p->scale.x -= world_p->scaleSpeed * HEIGHT / WIDTH;
		}
		if(world_p->actions[DOWN_ACTION].down){
			world_p->scale.y *= 1 + world_p->scaleSpeed * sqrt(sqrt(world_p->scale.y));
			//world_p->scale.y *= 1 + world_p->scaleSpeed;
			//world_p->scale.y += world_p->scaleSpeed;
		}
		if(world_p->actions[UP_ACTION].down){
			world_p->scale.y /= 1 + world_p->scaleSpeed * sqrt(sqrt(world_p->scale.y));
			//world_p->scale.y /= 1 + world_p->scaleSpeed;
			//world_p->scale.y *= 1 - world_p->scaleSpeed;
			//world_p->scale.y -= world_p->scaleSpeed;
		}

	}

	//limit scale
	if(world_p->scale.x < 1 / world_p->levelWidth / 100
	|| world_p->scale.x >= world_p->levelWidth * 100){
		world_p->scale.x = world_p->lastScale.x;
	}
	if(world_p->scale.y < 1 / world_p->levelHeight / 100
	|| world_p->scale.y >= world_p->levelHeight * 100){
		world_p->scale.y = world_p->lastScale.y;
	}

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
		}

		if(!world_p->actions[JUMP_ACTION].down
		&& playerPhysics_p->velocity.y < 0){
			playerPhysics_p->velocity.y = 0;
		}

	}

	world_p->deltaScale = world_p->scale;
	Vec2f_sub(&world_p->deltaScale, &world_p->lastScale);

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
	
	//update bodyPairs last bodies
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->lastBody = bodyPair_p->body;
		
	}

	//scale x
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		Vec2f scale = World_getScaleFromScaleType(world_p, bodyPair_p->scaleType);
		Vec2f lastScale = World_getLastScaleFromScaleType(world_p, bodyPair_p->scaleType);
		Vec2f origin = World_getOriginFromScaleType(world_p, bodyPair_p->scaleType);

		Body_unScaleX(&bodyPair_p->body, origin, lastScale);

		Body_scaleX(&bodyPair_p->body, origin, scale);
	
	}

	//handle scale collisions x
	Array collisions;
	Array_init(&collisions, sizeof(Collision));

	Array lastCollisions;
	Array_init(&lastCollisions, sizeof(Collision));

	for(int k = 0; k < 10; k++){

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
				Body_init(&oubBodyPair.body, getVec2f(0, 0), getVec2f(0, 0));
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
						Body_init(&oubBodyPair.body, getVec2f(0, 0), getVec2f(0, 0));
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

	//scale y
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		Vec2f scale = World_getScaleFromScaleType(world_p, bodyPair_p->scaleType);
		Vec2f lastScale = World_getLastScaleFromScaleType(world_p, bodyPair_p->scaleType);
		Vec2f origin = World_getOriginFromScaleType(world_p, bodyPair_p->scaleType);

		Body_unScaleY(&bodyPair_p->body, origin, lastScale);

		Body_scaleY(&bodyPair_p->body, origin, scale);
	
	}

	//handle scale collisions y
	Array_clear(&collisions);
	Array_clear(&lastCollisions);

	for(int k = 0; k < 10; k++){

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

			if((bodyPair1_p->body.pos.y + bodyPair1_p->body.size.y > HEIGHT
			&& bodyPair1_p->scaleType != ALL_FROM_TOP
			|| bodyPair1_p->body.pos.y < 0
			&& bodyPair1_p->scaleType == ALL_FROM_TOP)
			&& bodyPair1_p->entityHeader.ID != world_p->player.bodyPairID){
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
				Body_init(&oubBodyPair.body, getVec2f(0, HEIGHT), getVec2f(0, 0));
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
						Body_init(&oubBodyPair.body, getVec2f(0, HEIGHT), getVec2f(0, 0));
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

		Vec2f_add(&bodyPair_p->physics.velocity, &bodyPair_p->physics.acceleration);

		Vec2f_mul(&bodyPair_p->physics.velocity, &bodyPair_p->physics.resistance);

		bodyPair_p->physics.onGround = false;

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
		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
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
		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			&& i != j
			//&& (bodyPair1_p->canCollideWithPlayer || bodyPair2_p->canCollideWithPlayer)
			&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
			&& bodyPair1_p->collisionWeight == MOVABLE
			&& bodyPair2_p->collisionWeight == STATIC){

				float bodyPair1CenterY = bodyPair1_p->lastBody.pos.y + bodyPair1_p->lastBody.size.y / 2;
				float bodyPair2CenterY = bodyPair2_p->lastBody.pos.y + bodyPair2_p->lastBody.size.y / 2;

				if(bodyPair1CenterY < bodyPair2CenterY){
					bodyPair1_p->body.pos.y = bodyPair2_p->body.pos.y - bodyPair1_p->body.size.y;
					bodyPair1_p->physics.onGround = true;
				}
				if(bodyPair1CenterY > bodyPair2CenterY){
					bodyPair1_p->body.pos.y = bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y;
				}

				bodyPair1_p->physics.velocity.y = 0;
				
			}

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
	player_p->holdingKey = false;

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
		Vec2f_sub(&velocity, &doorKeyHold);
		Vec2f_mul(&velocity, &doorKeyPhysicsScale);

		float mag = Vec2f_getMag(velocity);

		Vec2f_normalize(&velocity);
		Vec2f_mulByFactor(&velocity, mag);
		//Vec2f_divByFactor(&velocity, 3);

		if(checkBodyToBodyCol(playerBodyPair_p->body, doorKeyBodyPair_p->body)
		&& !player_p->holdingKey){

			player_p->holdingKey = true;

			doorKeyBodyPair_p->physics.velocity = velocity;
			doorKey_p->facing = player_p->facing;

		}

	}

	//check if door keys collide with doors
	for(int i = 0; i < world_p->doors.length; i++){
		for(int j = 0; j < world_p->doorKeys.length; j++){
			
			Door *door_p = Array_getItemPointerByIndex(&world_p->doors, i);
			DoorKey *doorKey_p = Array_getItemPointerByIndex(&world_p->doorKeys, j);
			BodyPair *doorBodyPair_p = World_getBodyPairByID(world_p, door_p->bodyPairID);
			BodyPair *doorKeyBodyPair_p = World_getBodyPairByID(world_p, doorKey_p->bodyPairID);

			if(checkBodyPairToBodyPairCollision(*doorBodyPair_p, *doorKeyBodyPair_p)){

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

		}

	}

	//check collision with scale fields
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->scaleType = bodyPair_p->originScaleType;

		for(int j = 0; j < world_p->scaleFields.length; j++){

			ScaleField *scaleField_p = Array_getItemPointerByIndex(&world_p->scaleFields, j);

			if(checkBodyToBodyColCastToInt(bodyPair_p->body, scaleField_p->body)){

				bodyPair_p->scaleType = scaleField_p->scaleType;
				
			}
		
		}
	
	}

	//update sprites

	//update obstacle sprites
	for(int i = 0; i < world_p->obstacles.length; i++){

		Obstacle *obstacle_p = Array_getItemPointerByIndex(&world_p->obstacles, i);

		BodyPair *obstacleBodyPair_p = World_getBodyPairByID(world_p, obstacle_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByID(world_p, obstacle_p->spriteID);

		sprite_p->body = obstacleBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[obstacleBodyPair_p->scaleType];

		Vec2f scale = BodyPair_getPhysicsScale(obstacleBodyPair_p);

		//sprite_p->borderSize.x = 7 / scale.x;
		//sprite_p->borderSize.y = 7 / scale.y;

	}

	//update point sprites
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		BodyPair *pointBodyPair_p = World_getBodyPairByID(world_p, point_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByID(world_p, point_p->spriteID);

		sprite_p->body = pointBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[pointBodyPair_p->scaleType];

	}

	//update door sprites
	for(int i = 0; i < world_p->doors.length; i++){

		Door *door_p = Array_getItemPointerByIndex(&world_p->doors, i);

		BodyPair *doorBodyPair_p = World_getBodyPairByID(world_p, door_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByID(world_p, door_p->spriteID);

		sprite_p->body = doorBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[doorBodyPair_p->scaleType];

	}

	//update door key sprites
	for(int i = 0; i < world_p->doorKeys.length; i++){

		DoorKey *doorKey_p = Array_getItemPointerByIndex(&world_p->doorKeys, i);

		BodyPair *doorKeyBodyPair_p = World_getBodyPairByID(world_p, doorKey_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByID(world_p, doorKey_p->spriteID);

		sprite_p->body = doorKeyBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[doorKeyBodyPair_p->scaleType];

		sprite_p->facing = doorKey_p->facing;

	}

	//update scale field sprites
	for(int i = 0; i < world_p->scaleFields.length; i++){

		ScaleField *scaleField_p = Array_getItemPointerByIndex(&world_p->scaleFields, i);

		//BodyPair *scaleFieldBodyPair_p = World_getBodyPairByID(world_p, scaleField_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByID(world_p, scaleField_p->spriteID);

		//sprite_p->body = scaleFieldBodyPair_p->body;
		sprite_p->body = scaleField_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[scaleField_p->scaleType];

	}

	//update player sprite
	{
		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, world_p->player.bodyPairID);

		Sprite *sprite_p = World_getSpriteByID(world_p, world_p->player.spriteID);

		sprite_p->body = playerBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[playerBodyPair_p->scaleType];

		sprite_p->facing = world_p->player.facing;
	}

	//update offset
	if(world_p->currentState == LEVEL_HUB_STATE){

		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, world_p->player.bodyPairID);

		world_p->cameraPos.x = round(WIDTH / 2 - playerBodyPair_p->body.pos.x);

		//world_p->cameraPos.y = round(HEIGHT / 2 - playerBodyPair_p->body.pos.y);

		//world_p->renderer.offset.y = round(HEIGHT / 2 - playerBodyPair_p->body.pos.y);

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
		/*
		if(playerBodyPair_p->body.pos.y < -HEIGHT * 3){
			world_p->cameraTarget.y = HEIGHT * 4;
		}
		if(playerBodyPair_p->body.pos.y < -HEIGHT * 4){
			world_p->cameraTarget.y = HEIGHT * 5;
		}
		*/

		world_p->cameraPos.y += -(world_p->cameraPos.y - world_p->cameraTarget.y) / cameraSpeedY;

		world_p->renderer.offset.x = world_p->cameraPos.x;
		world_p->renderer.offset.y = world_p->cameraPos.y;
		//world_p->renderer.offset.y = world_p->cameraPos.y;

		if(world_p->renderer.offset.x > 0){
			world_p->renderer.offset.x = 0;
		}
	
	}

}
