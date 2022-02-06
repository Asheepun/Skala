//#include "stdbool.h"
#include "engine/audio.h"
#include "engine/strings.h"
#include "engine/engine.h"

#include "game.h"
#include "levels.h"

#include "math.h"
#include "stdio.h"
#include "string.h"
//#include "geometry.h"
//#include "stb_truetype.h"
//#include "text.h"
//#include "utils.h"
//#include "audio.h"

typedef struct Collision{
	unsigned int lighterBodyPairIndex;
	unsigned int heavierBodyPairIndex;
	bool oub;
}Collision;

int blockerAnimationCount = 25;

size_t scalingSoundLoopID = -1;

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
	if(world_p->scalingByPlayerSpeed){
		//backgroundColor = COLOR_DARK_YELLOW;
	}

	World_addSprite(world_p, getVec2f(0, 0), getVec2f(WIDTH, HEIGHT), backgroundColor, "obstacle", 1, GAME_LAYER_BACKGROUND);

	if(world_p->scalingByPlayerPosition
	|| world_p->scalingByPlayerSpeed){
		//Audio_playSound("begin-scaling-1", 1.0, false, AUDIO_SOUND_TYPE_SFX);
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
		if(world_p->actions[SCALE_ACTION].downed
		&& scalingSoundLoopID == -1){
			//scalingSoundLoopID = Audio_playSound("scaling", 0.2, true, AUDIO_SOUND_TYPE_SFX);
			//Audio_playSound("begin-scaling-1", 0.5, false, AUDIO_SOUND_TYPE_SFX);
			//scalingSoundCounter = 0;
		}
		if(world_p->actions[SCALE_ACTION].upped
		&& scalingSoundLoopID != -1){
			//Audio_killSoundByID(scalingSoundLoopID);
			//scalingSoundLoopID = -1;
			//Audio_playSound("end-scaling-1", 1.0, false, AUDIO_SOUND_TYPE_SFX);
		}
	}

	Player *player_p = &world_p->player;

	Vec2f_set(&player_p->physics.acceleration, 0, 0);

	//set last scale
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->lastScaleExponent = bodyPair_p->scaleExponent;
		bodyPair_p->playerPositionLastScale = bodyPair_p->playerPositionScale;
		bodyPair_p->playerSpeedLastScale = bodyPair_p->playerSpeedScale;
	
	}

	world_p->scaleDirection = getVec2f(0, 0);

	//control scale
	if(world_p->scalingByPlayerSpeed){

		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);

		float deltaX = fabs(playerBodyPair_p->body.pos.x - world_p->lastPlayerPos.x);
		float deltaY = fabs(playerBodyPair_p->body.pos.y - world_p->lastPlayerPos.y);

		world_p->lastPlayerPos = playerBodyPair_p->body.pos;

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			bodyPair_p->playerSpeedScale.x = pow(PLAYER_SPEED_SCALE_EXPONENT, -deltaX);
			bodyPair_p->playerSpeedScale.y = pow(PLAYER_SPEED_SCALE_EXPONENT, -deltaY);

		}
	
	}else if(world_p->scalingByPlayerPosition){

		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			float playerPosX = playerBodyPair_p->body.pos.x;
			float playerPosY = (world_p->levelHeight - playerBodyPair_p->body.pos.y - playerBodyPair_p->body.size.y);

			if(playerPosX < 1){
				playerPosX = 1;
			}
			if(playerPosY < 1){
				playerPosY = 1;
			}

			//NEED TO FIX THIS SOMEHOW!!!!
			bodyPair_p->playerPositionScale.x = playerBodyPair_p->originBody.pos.x / playerPosX;
			bodyPair_p->playerPositionScale.y = (world_p->levelHeight - playerBodyPair_p->originBody.pos.y - playerBodyPair_p->originBody.size.y) / playerPosY;

		}
	
	}else if(world_p->scaling){

		if(world_p->actions[LEFT_ACTION].down){
			world_p->scaleDirection.x++;
		}
		if(world_p->actions[RIGHT_ACTION].down){
			world_p->scaleDirection.x--;
		}
		if(world_p->actions[DOWN_ACTION].down){
			world_p->scaleDirection.y++;
		}
		if(world_p->actions[UP_ACTION].down){
			world_p->scaleDirection.y--;
		}

		for(int i = 0; i < world_p->bodyPairs.length; i++){
			
			BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			if(world_p->actions[LEFT_ACTION].down){
				bodyPair_p->scaleExponent.x++;
			}
			if(world_p->actions[RIGHT_ACTION].down){
				bodyPair_p->scaleExponent.x--;
			}
			if(world_p->actions[DOWN_ACTION].down){
				bodyPair_p->scaleExponent.y++;
			}
			if(world_p->actions[UP_ACTION].down){
				bodyPair_p->scaleExponent.y--;
			}

		}

	}

	//control player
	if((!world_p->scaling
	|| world_p->scalingByPlayerPosition)
	&& !world_p->playerHasNoLegs){

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
			//Audio_playSound("player-jump-1", 3.0, false, AUDIO_SOUND_TYPE_SFX);
			//Audio_playSound("player-land", 1.0, false, AUDIO_SOUND_TYPE_SFX);
		}

		if(!world_p->actions[JUMP_ACTION].down
		&& playerPhysics_p->velocity.y < 0){
			playerPhysics_p->velocity.y = 0;
		}

	}

	//play scaling sound
	//if(fabs(world_p->deltaScale.x) > 0
	//|| fabs(world_p->deltaScale.y) > 0){
		//if(scalingSoundCounter % 20 == 0){
			//Audio_playSound("scaling", 1.0, false, AUDIO_SOUND_TYPE_SFX);
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

				char *checkLevelName = Array_getItemPointerByIndex(&world_p->saveData.completedLevels, i);

				if(strcmp(checkLevelName, world_p->currentLevel) == 0){
					alreadyCompleted = true;
				}

			}

			if(!alreadyCompleted){

				char *completedLevel_p = Array_addItem(&world_p->saveData.completedLevels);

				String_set(completedLevel_p, world_p->currentLevel, STRING_SIZE);
				//*completedLevel_p = world_p->currentLevel;
			}
		}

		//check if player has unlocked a door key, and if so add to save data
		for(int i = 0; i < world_p->saveData.levelsWithDoorKey.length; i++){
			
			char *levelName_p = Array_getItemPointerByIndex(&world_p->saveData.levelsWithDoorKey, i);

			if(strcmp(levelName_p, world_p->currentLevel) == 0){

				Vec2f *doorKeyPos_p = Array_addItem(&world_p->saveData.doorKeys);
				*doorKeyPos_p = world_p->saveData.playerPos;

				Array_removeItemByIndex(&world_p->saveData.levelsWithDoorKey, i);
				i--;

			}

		}

		World_fadeTransitionToState(world_p, LEVEL_HUB_STATE);
		//World_fadeTransitionToState(world_p, LEVEL_STATE);

		return;

	}
	
	//update bodyPairs last bodies and make unstuck
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->lastBody = bodyPair_p->body;

		bodyPair_p->isStuckX = false;
		bodyPair_p->isStuckY = false;
		
	}

	//scale x
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		Vec2f scale = World_BodyPair_getScaleFromExponent(world_p, bodyPair_p);
		Vec2f lastScale = World_BodyPair_getLastScaleFromExponent(world_p, bodyPair_p);
		Vec2f origin = world_p->origin;

		if(world_p->scalingByPlayerSpeed){
			scale = bodyPair_p->playerSpeedScale;
			lastScale = bodyPair_p->playerSpeedLastScale;
		}

		if(world_p->scalingByPlayerPosition){
			scale = bodyPair_p->playerPositionScale;
			lastScale = bodyPair_p->playerPositionLastScale;
		}

		if(bodyPair_p->scaleType == NONE){
			scale = getVec2f(1, 1);
			lastScale = getVec2f(1, 1);
		}
		if(bodyPair_p->scaleType == ALL_FROM_TOP){
			origin = getVec2f(0, 0);
		}

		Body_unScaleX(&bodyPair_p->body, origin.x, lastScale.x);

		Body_scaleX(&bodyPair_p->body, origin.x, scale.x);

	}

	//handle scale collisions x
	Array collisions;
	Array_init(&collisions, sizeof(Collision));

	Array lastCollisions;
	Array_init(&lastCollisions, sizeof(Collision));

	for(int k = 0; k < 5; k++){

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			for(int j = 0; j < world_p->bodyPairs.length; j++){

				BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

				//optimization to skip over the most common case in level hub
				if(bodyPair1_p->collisionWeight == STATIC
				&& bodyPair1_p->scaleType == NONE
				&& bodyPair2_p->collisionWeight == STATIC
				&& bodyPair2_p->scaleType == NONE){
					continue;
				}

				if((checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
				|| checkBodyPairToBodyPairMoveBoxCollisionX(*bodyPair1_p, *bodyPair2_p))
				&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
				&& i != j
				&& !(world_p->obstaclesCannotCollideWithEachOther
				&& bodyPair1_p->entityType == OBSTACLE
				&& bodyPair2_p->entityType == OBSTACLE)){

					if(bodyPair1_p->lastBody.size.x < 1
					&& (bodyPair2_p->entityType == OBSTACLE
					|| bodyPair2_p->entityType == DOOR)){

						bodyPair1_p->body.size.x = bodyPair1_p->lastBody.size.x;
						bodyPair1_p->body.pos.x = bodyPair1_p->lastBody.pos.x;
						bodyPair1_p->scaleExponent.x = bodyPair1_p->lastScaleExponent.x;
						bodyPair1_p->playerPositionScale.x = bodyPair1_p->playerPositionLastScale.x;
						bodyPair1_p->playerSpeedScale.x = bodyPair1_p->playerSpeedLastScale.x;

						bodyPair1_p->isStuckX = true;

						continue;

					}

					if(bodyPair2_p->lastBody.size.x < 1
					&& (bodyPair1_p->entityType == OBSTACLE
					|| bodyPair1_p->entityType == DOOR)){
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

						if(collision_p->oub){

							if(collision_p->lighterBodyPairIndex == i){
								bodyPair1IsMovable = false;
							}
							if(collision_p->lighterBodyPairIndex == j){
								bodyPair2IsMovable = false;
							}
							
						}else{

							BodyPair *bodyPair3_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->heavierBodyPairIndex);

							if(bodyPair3_p->collisionWeight == STATIC){
								if(collision_p->lighterBodyPairIndex == i
								&& collision_p->heavierBodyPairIndex != j){
									bodyPair1IsMovable = false;
								}
								if(collision_p->lighterBodyPairIndex == j
								&& collision_p->heavierBodyPairIndex != i){
									bodyPair2IsMovable = false;
								}
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
					&& world_p->scaleDirection.x < 0
					|| bodyPair1_p->body.pos.x + bodyPair1_p->body.size.x > bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x
					&& world_p->scaleDirection.x > 0){
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
				collision_p->heavierBodyPairIndex = -1;
				collision_p->oub = true;
			}

		}

		if(collisions.length == 0){
			break;
		}

		for(int i = 0; i < collisions.length; i++){

			Collision *collision_p = Array_getItemPointerByIndex(&collisions, i);

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->lighterBodyPairIndex);
			BodyPair *bodyPair2_p;

			if(collision_p->oub){
				BodyPair oubBodyPair;
				Body_init(&oubBodyPair.body, getVec2f(-200, 0), getVec2f(200, 0));
				oubBodyPair.lastBody = oubBodyPair.body;
				bodyPair2_p = &oubBodyPair;
			}else{
				bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->heavierBodyPairIndex);
			}

			float bodyPair1CenterX = bodyPair1_p->lastBody.pos.x + bodyPair1_p->lastBody.size.x / 2;
			float bodyPair2CenterX = bodyPair2_p->lastBody.pos.x + bodyPair2_p->lastBody.size.x / 2;

			if(bodyPair1CenterX < bodyPair2CenterX){
				bodyPair1_p->body.pos.x = roundTo2Dec(bodyPair2_p->body.pos.x) - roundTo2Dec(bodyPair1_p->body.size.x);

				if(roundTo2Dec(bodyPair1_p->body.pos.x + bodyPair1_p->body.size.x) > bodyPair2_p->body.pos.x){
					bodyPair1_p->body.pos.x = floor(bodyPair1_p->body.pos.x);
					bodyPair1_p->body.size.x = floor(bodyPair1_p->body.size.x);
				}

			}
			if(bodyPair1CenterX > bodyPair2CenterX){
				bodyPair1_p->body.pos.x = roundTo2Dec(bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x);

				if(roundTo2Dec(bodyPair1_p->body.pos.x) < roundTo2Dec(bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x)){
					bodyPair1_p->body.pos.x = ceil(bodyPair1_p->body.pos.x);
					bodyPair1_p->body.size.x = ceil(bodyPair1_p->body.size.x);
				}

			}

			if(!BodyPair_isScalable(bodyPair1_p)){
				continue;
			}

			for(int j = 0; j < lastCollisions.length; j++){

				Collision *collision2_p = Array_getItemPointerByIndex(&lastCollisions, j);

				if(collision_p->lighterBodyPairIndex == collision2_p->lighterBodyPairIndex
				&& collision_p->heavierBodyPairIndex != collision2_p->heavierBodyPairIndex){

					BodyPair *bodyPair3_p;

					if(collision2_p->oub){
						BodyPair oubBodyPair;
						Body_init(&oubBodyPair.body, getVec2f(-200, 0), getVec2f(200, 0));
						oubBodyPair.lastBody = oubBodyPair.body;
						bodyPair3_p = &oubBodyPair;
					}else{
						bodyPair3_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision2_p->heavierBodyPairIndex);
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

					bodyPair1_p->body.pos.x = roundTo2Dec(leftBodyPair_p->body.pos.x + leftBodyPair_p->body.size.x);
					bodyPair1_p->body.size.x = roundTo2Dec(rightBodyPair_p->body.pos.x) - roundTo2Dec(leftBodyPair_p->body.pos.x + leftBodyPair_p->body.size.x);

					//shift in case there still is collision
					bodyPair1_p->body.pos.x = ceil(bodyPair1_p->body.pos.x);
					bodyPair1_p->body.size.x = floor(bodyPair1_p->body.size.x);

					if(bodyPair1_p->body.pos.x + bodyPair1_p->body.size.x > rightBodyPair_p->body.pos.x){
						bodyPair1_p->body.size.x -= 1;
					}

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

		//things that are below or to the left of the origin cannot be scaled might have to remove if bugs appear
		if(bodyPair_p->body.pos.y > HEIGHT + 1//buffer in case of floating point bug
		&& bodyPair_p->scaleType == ALL){
			continue;
		}

		Vec2f scale = World_BodyPair_getScaleFromExponent(world_p, bodyPair_p);
		Vec2f lastScale = World_BodyPair_getLastScaleFromExponent(world_p, bodyPair_p);
		Vec2f origin = world_p->origin;

		if(world_p->scalingByPlayerSpeed){
			scale = bodyPair_p->playerSpeedScale;
			lastScale = bodyPair_p->playerSpeedLastScale;
		}

		if(world_p->scalingByPlayerPosition){
			scale = bodyPair_p->playerPositionScale;
			lastScale = bodyPair_p->playerPositionLastScale;
		}

		if(bodyPair_p->scaleType == NONE){
			scale = getVec2f(1, 1);
			lastScale = getVec2f(1, 1);
		}
		if(bodyPair_p->scaleType == ALL_FROM_TOP){
			origin = getVec2f(0, 0);

			if(world_p->currentState == LEVEL_HUB_STATE){
				origin = getVec2f(0, -HEIGHT * 6);
			}

		}

		Body_unScaleY(&bodyPair_p->body, origin.y, lastScale.y);

		Body_scaleY(&bodyPair_p->body, origin.y, scale.y);
	
	}

	//handle scale collisions y
	Array_clear(&collisions);
	Array_clear(&lastCollisions);

	for(int k = 0; k < 5; k++){

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			for(int j = 0; j < world_p->bodyPairs.length; j++){

				BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

				//optimization to skip over the most common case in level hub
				if(bodyPair1_p->collisionWeight == STATIC
				&& bodyPair1_p->scaleType == NONE
				&& bodyPair2_p->collisionWeight == STATIC
				&& bodyPair2_p->scaleType == NONE){
					continue;
				}

				if((checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
				|| checkBodyPairToBodyPairMoveBoxCollisionY(*bodyPair1_p, *bodyPair2_p))
				&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
				&& i != j
				&& !(world_p->obstaclesCannotCollideWithEachOther
				&& bodyPair1_p->entityType == OBSTACLE
				&& bodyPair2_p->entityType == OBSTACLE)){

					if(bodyPair1_p->lastBody.size.y < 1
					&& (bodyPair2_p->entityType == OBSTACLE
					|| bodyPair2_p->entityType == DOOR)){

						bodyPair1_p->body.size.y = bodyPair1_p->lastBody.size.y;
						bodyPair1_p->body.pos.y = bodyPair1_p->lastBody.pos.y;
						//bodyPair1_p->scale.y = bodyPair1_p->lastScale.y;
						bodyPair1_p->scaleExponent.y = bodyPair1_p->lastScaleExponent.y;
						bodyPair1_p->playerPositionScale.y = bodyPair1_p->playerPositionLastScale.y;
						bodyPair1_p->playerSpeedScale.y = bodyPair1_p->playerSpeedLastScale.y;

						bodyPair1_p->isStuckY = true;

						continue;
					}

					if(bodyPair2_p->lastBody.size.y < 1
					&& (bodyPair1_p->entityType == OBSTACLE
					|| bodyPair1_p->entityType == DOOR)){
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

						if(collision_p->oub){

							if(collision_p->lighterBodyPairIndex == i){
								bodyPair1IsMovable = false;
							}
							if(collision_p->lighterBodyPairIndex == j){
								bodyPair2IsMovable = false;
							}
						
						}else{

							BodyPair *bodyPair3_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->heavierBodyPairIndex);

							if(bodyPair3_p->collisionWeight == STATIC){
								if(collision_p->lighterBodyPairIndex == i
								&& collision_p->heavierBodyPairIndex != j){
									bodyPair1IsMovable = false;
								}
								if(collision_p->lighterBodyPairIndex == j
								&& collision_p->heavierBodyPairIndex != i){
									bodyPair2IsMovable = false;
								}

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
					&& world_p->scaleDirection.y < 0
					|| bodyPair1_p->body.pos.y + bodyPair1_p->body.size.y < bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y
					&& world_p->scaleDirection.y > 0){
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

			if(world_p->currentState != LEVEL_HUB_STATE//fix small thing in elevator, will probably need a better fix
			&& (bodyPair1_p->body.pos.y + bodyPair1_p->body.size.y > HEIGHT
			&& bodyPair1_p->scaleType == ALL
			|| bodyPair1_p->body.pos.y < 0
			&& bodyPair1_p->scaleType == ALL_FROM_TOP
			&& world_p->currentState == LEVEL_STATE)
			&& bodyPair1_p->entityType != DOOR_KEY
			&& bodyPair1_p->entityType != PLAYER){

				Collision *collision_p = Array_addItem(&collisions);
				collision_p->lighterBodyPairIndex = i;
				collision_p->heavierBodyPairIndex = -1;
				collision_p->oub = true;

			}

		}

		if(collisions.length == 0){
			break;
		}

		for(int i = 0; i < collisions.length; i++){

			Collision *collision_p = Array_getItemPointerByIndex(&collisions, i);

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->lighterBodyPairIndex);
			BodyPair *bodyPair2_p;

			if(collision_p->oub){
				BodyPair oubBodyPair;
				Body_init(&oubBodyPair.body, getVec2f(0, HEIGHT), getVec2f(0, 200));
				if(bodyPair1_p->scaleType == ALL_FROM_TOP){
					oubBodyPair.body.pos.y = -200;
				}
				oubBodyPair.lastBody = oubBodyPair.body;
				bodyPair2_p = &oubBodyPair;
			}else{
				bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision_p->heavierBodyPairIndex);
			}

			float bodyPair1CenterY = bodyPair1_p->lastBody.pos.y + bodyPair1_p->lastBody.size.y / 2;
			float bodyPair2CenterY = bodyPair2_p->lastBody.pos.y + bodyPair2_p->lastBody.size.y / 2;

			if(bodyPair1CenterY < bodyPair2CenterY){

				bodyPair1_p->body.pos.y = roundTo2Dec(bodyPair2_p->body.pos.y) - roundTo2Dec(bodyPair1_p->body.size.y);

				if(roundTo2Dec(bodyPair1_p->body.pos.y + bodyPair1_p->body.size.y) > bodyPair2_p->body.pos.y){
					bodyPair1_p->body.pos.y = floor(bodyPair1_p->body.pos.y);
					bodyPair1_p->body.size.y = floor(bodyPair1_p->body.size.y);
				}

			}
			if(bodyPair1CenterY > bodyPair2CenterY){

				bodyPair1_p->body.pos.y = roundTo2Dec(bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y);

				if(roundTo2Dec(bodyPair1_p->body.pos.y) < roundTo2Dec(bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y)){
					bodyPair1_p->body.pos.y = ceil(bodyPair1_p->body.pos.y);
					bodyPair1_p->body.size.y = ceil(bodyPair1_p->body.size.y);
				}

			}

			if(!BodyPair_isScalable(bodyPair1_p)){
				continue;
			}

			for(int j = 0; j < lastCollisions.length; j++){

				Collision *collision2_p = Array_getItemPointerByIndex(&lastCollisions, j);

				if(collision_p->lighterBodyPairIndex == collision2_p->lighterBodyPairIndex
				&& collision_p->heavierBodyPairIndex != collision2_p->heavierBodyPairIndex){

					BodyPair *bodyPair3_p;

					if(collision2_p->oub){
						BodyPair oubBodyPair;
						Body_init(&oubBodyPair.body, getVec2f(0, HEIGHT), getVec2f(0, 200));
						if(bodyPair1_p->scaleType == ALL_FROM_TOP){
							oubBodyPair.body.pos.y = -200;
						}
						oubBodyPair.lastBody = oubBodyPair.body;
						bodyPair3_p = &oubBodyPair;
					}else{
						bodyPair3_p = Array_getItemPointerByIndex(&world_p->bodyPairs, collision2_p->heavierBodyPairIndex);
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

					bodyPair1_p->body.pos.y = roundTo2Dec(upBodyPair_p->body.pos.y + upBodyPair_p->body.size.y);
					bodyPair1_p->body.size.y = roundTo2Dec(downBodyPair_p->body.pos.y) - roundTo2Dec(upBodyPair_p->body.pos.y + upBodyPair_p->body.size.y);

					//shift in case there still is collision
					bodyPair1_p->body.pos.y = ceil(bodyPair1_p->body.pos.y);
					bodyPair1_p->body.size.y = floor(bodyPair1_p->body.size.y);

					if(bodyPair1_p->body.pos.y + bodyPair1_p->body.size.y > downBodyPair_p->body.pos.y){
						bodyPair1_p->body.size.y -= 1;
					}

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

	//apply physics and update last bodies
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		//optimization to skip over bodypairs who do not need to move
		//if(bodyPair_p->collisionWeight == STATIC){
			//continue;
		//}

		bodyPair_p->physics.acceleration.y += bodyPair_p->physics.gravity;

		Vec2f_add(&bodyPair_p->physics.velocity, bodyPair_p->physics.acceleration);

		Vec2f_mul(&bodyPair_p->physics.velocity, bodyPair_p->physics.resistance);

		//reset acceleration
		bodyPair_p->physics.acceleration = getVec2f(0, 0);

		//update last bodies
		bodyPair_p->lastBody = bodyPair_p->body;
			
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

			if((checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			|| checkBodyPairToBodyPairMoveBoxCollisionX(*bodyPair1_p, *bodyPair2_p))
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

			if((checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			|| checkBodyPairToBodyPairMoveBoxCollisionY(*bodyPair1_p, *bodyPair2_p))
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
			//Audio_playSound("player-jump-1", 0.5, false, AUDIO_SOUND_TYPE_SFX);
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

		if(checkBodyPairToBodyPairCollision(*playerBodyPair_p, *doorKeyBodyPair_p)
		&& !playerGotKey){

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

			playerGotKey = true;

			doorKeyBodyPair_p->physics.velocity = velocity;
			doorKey_p->facing = player_p->facing;

		}

	}

	if(playerGotKey){
		if(!player_p->holdingKey){
			Audio_playSoundVariation("pickup-key", 3, 1.0, false, AUDIO_SOUND_TYPE_SFX);
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

				//particle effect
				{
					Vec2f pos = doorBodyPair_p->body.pos;
					Vec2f size = doorBodyPair_p->body.size;

					size_t particleSpriteIndex = World_addSprite(world_p, pos, size, COLOR_WHITE, "door", 1, GAME_LAYER_PARTICLES);
					Sprite *sprite_p = World_getSpriteByIndex(world_p, particleSpriteIndex);
					sprite_p->textureArea = getVec2f(20, 60);

					Particle *particle_p = World_addParticle(world_p, particleSpriteIndex);

					particle_p->body.pos = pos;
					particle_p->body.size = size;

					int fadeOutTime = (300 + getRandom() * 200) / 60;

					union ParticleProperty property;

					property.alpha = 0;
					Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, property, 0, fadeOutTime);

					property.size = getVec2f(size.x, 0);
					Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_SIZE, property, 0, fadeOutTime);

					property.pos = getVec2f(pos.x, pos.y + size.y / 2);
					Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_POS, property, 0, fadeOutTime);

					Particle_addEvent(particle_p, PARTICLE_REMOVE_EVENT, 0, property, fadeOutTime, 0);
				}
				{

					Vec2f pos = doorKeyBodyPair_p->body.pos;
					Vec2f size = doorKeyBodyPair_p->body.size;

					size_t particleSpriteIndex = World_addSprite(world_p, pos, size, SCALE_TYPE_COLORS[doorKeyBodyPair_p->scaleType], "door-key", 1, GAME_LAYER_PARTICLES);
					Sprite *sprite_p = World_getSpriteByIndex(world_p, particleSpriteIndex);
					Sprite *originalSprite_p = World_getSpriteByIndex(world_p, doorKey_p->spriteIndex);

					sprite_p->textureArea = getVec2f(20, 10);
					sprite_p->facing = originalSprite_p->facing;
					//sprite_p->

					Particle *particle_p = World_addParticle(world_p, particleSpriteIndex);

					particle_p->body.pos = pos;
					particle_p->body.size = size;

					int fadeOutStartTime = 0;
					//int fadeOutStartTime = (300 + getRandom() * 200) / 60;
					int fadeOutTime = (600 + getRandom() * 500) / 60;

					union ParticleProperty property;

					property.alpha = 0;
					Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, property, fadeOutStartTime, fadeOutTime);

					property.size = getVec2f(size.x, 0);
					Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_SIZE, property, fadeOutStartTime, fadeOutTime);

					property.pos = getVec2f(pos.x, pos.y + size.y / 2);
					Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_POS, property, fadeOutStartTime, fadeOutTime);

					Particle_addEvent(particle_p, PARTICLE_REMOVE_EVENT, 0, property, fadeOutStartTime + fadeOutTime , 0);
				}

				//sound effect
				Audio_playSound("open-door-1", 1.0, false, AUDIO_SOUND_TYPE_SFX);

				//remove door and key
				World_removeDoorByID(world_p, door_p->entityHeader.ID);
				World_removeDoorKeyByID(world_p, doorKey_p->entityHeader.ID);

				//update save data in level hub state
				if(world_p->currentState == LEVEL_HUB_STATE){

					Array_clear(&world_p->saveData.doors);
					Array_clear(&world_p->saveData.doorKeys);

					for(int k = 0; k < world_p->doors.length; k++){
						Body *doorBody_p = Array_addItem(&world_p->saveData.doors);
						*doorBody_p = World_getBodyPairByID(world_p, ((Door *)Array_getItemPointerByIndex(&world_p->doors, k))->bodyPairID)->body;
					}
					for(int k = 0; k < world_p->doorKeys.length; k++){
						Vec2f *doorKeyPos_p = Array_addItem(&world_p->saveData.doorKeys);
						*doorKeyPos_p = World_getBodyPairByID(world_p, ((DoorKey *)Array_getItemPointerByIndex(&world_p->doorKeys, k))->bodyPairID)->body.pos;
					}
				
				}

				i--;
				j--;

				break;

			}

		}
	}

	//check if player collides with points
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		BodyPair *pointBodyPair_p = Array_getItemPointerByID(&world_p->bodyPairs, point_p->bodyPairID);
		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);
	
		//if(checkBodyToBodyColRoundToFloat(playerBodyPair_p->body, *pointBody_p)){
		if(checkBodyPairToBodyPairCollision(*pointBodyPair_p, *playerBodyPair_p)){

			World_removePointByID(world_p, point_p->entityHeader.ID);

			i--;
			
			//Audio_playSound("pickup-star-3", 1.0, false, AUDIO_SOUND_TYPE_SFX);

		}

	}

	//check if player collides with level doors
	for(int i = 0; i < world_p->levelDoors.length; i++){

		LevelDoor *levelDoor_p = Array_getItemPointerByIndex(&world_p->levelDoors, i);
		BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, player_p->bodyPairID);
	
		if(checkBodyToBodyCol(playerBodyPair_p->body, levelDoor_p->body)
		&& playerBodyPair_p->physics.velocity.y < 0
		&& world_p->playerHasLanded){

			//world_p->currentLevel = levelDoor_p->levelName;
			String_set(world_p->currentLevel, levelDoor_p->levelName, STRING_SIZE);

			world_p->saveData.playerPos = playerBodyPair_p->body.pos;

			World_fadeTransitionToState(world_p, LEVEL_STATE);

			//Audio_playSound("enter-level-door", 1.0, false, AUDIO_SOUND_TYPE_SFX);

		}

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

	//make small and non scalable objects appear as stuck
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		if(bodyPair_p->scaleType == NONE){
			if(bodyPair_p->body.size.x < 1){
				bodyPair_p->isStuckX = true;
			}
			if(bodyPair_p->body.size.y < 1){
				bodyPair_p->isStuckY = true;
			}
		}
	
	}

	//add arrows pointing to bodypairs outside of screen
	if(world_p->currentState == LEVEL_STATE){
		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			if((bodyPair_p->scaleType != NONE
			|| bodyPair_p->entityType == PLAYER
			|| bodyPair_p->entityType == DOOR_KEY)
			&& !(bodyPair_p->entityType == OBSTACLE
			&& !world_p->obstaclesNeedArrows)){

				Vec2f pos = getVec2f(100, 100);
				Vec2f size = getVec2f(15, 15);
				char spriteName[STRING_SIZE];
				bool oub = false;

				float sizeScaleFactor = 1;

				sizeScaleFactor = pow(2, (300 - getMagVec2f(getSubVec2f(getAddVec2f(bodyPair_p->body.pos, getDivVec2fFloat(bodyPair_p->body.size, 2)), getVec2f(WIDTH / 2, HEIGHT / 2)))) / 2000);

				//up
				if(bodyPair_p->body.pos.y + bodyPair_p->body.size.y < 0){
					size = getVec2f(15, 17);
					pos.x = bodyPair_p->body.pos.x + bodyPair_p->body.size.x / 2;
					pos.y = 20;
					String_set(spriteName, "arrow-up", STRING_SIZE);
					oub = true;
				}
				//down
				if(bodyPair_p->body.pos.y > HEIGHT){
					sizeScaleFactor = pow(2, (HEIGHT - bodyPair_p->body.pos.y) / 200);
					size = getVec2f(15, 17);
					pos.x = bodyPair_p->body.pos.x + bodyPair_p->body.size.x / 2;
					pos.y = HEIGHT - 30;
					String_set(spriteName, "arrow-down", STRING_SIZE);
					oub = true;
				}
				//right
				if(bodyPair_p->body.pos.x > WIDTH){
					size = getVec2f(17, 15);
					pos.x = WIDTH - 50;
					pos.y = bodyPair_p->body.pos.y + bodyPair_p->body.size.y / 2;
					String_set(spriteName, "arrow-right", STRING_SIZE);
					oub = true;
				}
				//up right
				if(bodyPair_p->body.pos.y + bodyPair_p->body.size.y / 2 < 0
				&& bodyPair_p->body.pos.x > WIDTH
				|| bodyPair_p->body.pos.y + bodyPair_p->body.size.y < 0
				&& bodyPair_p->body.pos.x + bodyPair_p->body.size.x / 2 > WIDTH){
					size = getVec2f(15, 15);
					pos.x = WIDTH - 50;
					pos.y = 20;
					String_set(spriteName, "arrow-up-right", STRING_SIZE);
					oub = true;
				}
				//down right
				if(bodyPair_p->body.pos.y + bodyPair_p->body.size.y / 2 > HEIGHT
				&& bodyPair_p->body.pos.x > WIDTH
				|| bodyPair_p->body.pos.y > HEIGHT
				&& bodyPair_p->body.pos.x + bodyPair_p->body.size.x / 2 > WIDTH){
					size = getVec2f(15, 15);
					pos.x = WIDTH - 50;
					pos.y = HEIGHT - 30;
					String_set(spriteName, "arrow-down-right", STRING_SIZE);
					oub = true;
				}

				if(oub){

					Renderer2D_Color color = SCALE_TYPE_COLORS[bodyPair_p->scaleType];

					//if(bodyPair_p->entityType == PLAYER){
						//color = COLOR_YELLOW;
					//}

					size_t newSpriteIndex = World_addSprite(world_p, pos, size, color, spriteName, 1.0, GAME_LAYER_PARTICLES);

					Particle *newParticle_p = World_addParticle(world_p, newSpriteIndex);

					sizeScaleFactor *= 0.9;

					Vec2f_mulByFloat(&size, sizeScaleFactor);

					Vec2f_sub(&pos, getDivVec2fFloat(size, 2));

					newParticle_p->body.pos = pos;
					newParticle_p->body.size = size;

					union ParticleProperty property;

					Particle_addEvent(newParticle_p, PARTICLE_REMOVE_EVENT, 0, property, 1, 0);
				
				}

			}
		
		}
	}

	//update particles
	for(int i = 0; i < world_p->particles.length; i++){

		Particle *particle_p = Array_getItemPointerByIndex(&world_p->particles, i);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, particle_p->spriteIndex);

		if(particle_p->edge == PARTICLE_EDGE_UP
		&& particle_p->body.pos.y < particle_p->edgePos
		|| particle_p->edge == PARTICLE_EDGE_DOWN
		&& particle_p->body.pos.y > particle_p->edgePos
		|| particle_p->edge == PARTICLE_EDGE_LEFT
		&& particle_p->body.pos.x < particle_p->edgePos
		|| particle_p->edge == PARTICLE_EDGE_RIGHT
		&& particle_p->body.pos.x > particle_p->edgePos){
			World_removeParticleByID(world_p, particle_p->entityHeader.ID);
			i--;
		}

		if(particle_p->isEmitter
		&& sprite_p->alpha > 0
		&& particle_p->counter > 0){

			Vec2f pos = particle_p->body.pos;
			Vec2f_add(&pos, getVec2f(1 + 8 * getRandom(), 1 + 8 * getRandom()));
			
			size_t newSpriteIndex = World_addSprite(world_p, pos, getVec2f(1, 1), sprite_p->color, "obstacle", 1, GAME_LAYER_PARTICLES);
			Particle *newParticle_p = World_addParticle(world_p, newSpriteIndex);

			newParticle_p->body.pos = pos;
			newParticle_p->body.size = getVec2f(1, 1);

			newParticle_p->physics.velocity = getVec2f((getRandom() - 0.5) * 0.2, 0.1 + 0.15 * getRandom());

			union ParticleProperty property;

			int fadeOutStartTime = (0.5 + getRandom() * 0.7) * 60;
			int fadeOutTime = (0.1 + getRandom() * 0.1) * 60;

			if(getMagVec2f(particle_p->physics.velocity) > 5){
				fadeOutStartTime += 1500;
				newParticle_p->physics.velocity.y *= 0.2;
			}

			property.alpha = 0;

			Particle_addEvent(newParticle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, property, fadeOutStartTime, fadeOutTime);

			Particle_addEvent(newParticle_p, PARTICLE_REMOVE_EVENT, 0, property, fadeOutStartTime + fadeOutTime, 0);

		}

		bool removed = false;

		for(int j = 0; j < particle_p->events.length; j++){

			ParticleEvent *particleEvent_p = Array_getItemPointerByIndex(&particle_p->events, j);

			if(particle_p->counter > particleEvent_p->activationTime + particleEvent_p->duration){

				Array_removeItemByIndex(&particle_p->events, j);
				j--;

				continue;

			}

			if(particle_p->counter >= particleEvent_p->activationTime
			&& particle_p->counter <= particleEvent_p->activationTime + particleEvent_p->duration){

				if(particleEvent_p->type == PARTICLE_REMOVE_EVENT){
					World_removeParticleByID(world_p, particle_p->entityHeader.ID);
					i--;
					removed = true;
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

				if(particleEvent_p->propertyType == PARTICLE_COLOR){

					if(particle_p->counter == particleEvent_p->activationTime){
						particleEvent_p->startValue.color = sprite_p->color;
					}

					if(particleEvent_p->type == PARTICLE_SET_EVENT){
						sprite_p->color = particleEvent_p->targetValue.color;
					}

					if(particleEvent_p->type == PARTICLE_LINEAR_FADE_EVENT){
						sprite_p->color.r = particleEvent_p->startValue.color.r + (particleEvent_p->targetValue.color.r - particleEvent_p->startValue.color.r) * (particle_p->counter - particleEvent_p->activationTime) / particleEvent_p->duration;
						sprite_p->color.g = particleEvent_p->startValue.color.g + (particleEvent_p->targetValue.color.g - particleEvent_p->startValue.color.g) * (particle_p->counter - particleEvent_p->activationTime) / particleEvent_p->duration;
						sprite_p->color.b = particleEvent_p->startValue.color.b + (particleEvent_p->targetValue.color.b - particleEvent_p->startValue.color.b) * (particle_p->counter - particleEvent_p->activationTime) / particleEvent_p->duration;
					}
					

				}

				if(particleEvent_p->propertyType == PARTICLE_VELOCITY){

					if(particle_p->counter == particleEvent_p->activationTime){
						particleEvent_p->startValue.velocity = particle_p->physics.velocity;
					}

					if(particleEvent_p->type == PARTICLE_SET_EVENT){
						particle_p->physics.velocity = particleEvent_p->targetValue.velocity;
					}
					
				}

				if(particleEvent_p->propertyType == PARTICLE_ACCELERATION){

					if(particle_p->counter == particleEvent_p->activationTime){
						particleEvent_p->startValue.acceleration = particle_p->physics.acceleration;
					}

					if(particleEvent_p->type == PARTICLE_SET_EVENT){
						particle_p->physics.acceleration = particleEvent_p->targetValue.acceleration;
					}
					
				}

				if(particleEvent_p->propertyType == PARTICLE_POS){

					if(particle_p->counter == particleEvent_p->activationTime){
						particleEvent_p->startValue.pos = particle_p->body.pos;
					}

					if(particleEvent_p->type == PARTICLE_SET_EVENT){
						particle_p->body.pos = particleEvent_p->targetValue.pos;
					}

					if(particleEvent_p->type == PARTICLE_LINEAR_FADE_EVENT){
						particle_p->body.pos.x = particleEvent_p->startValue.pos.x + (particleEvent_p->targetValue.pos.x - particleEvent_p->startValue.pos.x) * (particle_p->counter - particleEvent_p->activationTime) / particleEvent_p->duration;
						particle_p->body.pos.y = particleEvent_p->startValue.pos.y + (particleEvent_p->targetValue.pos.y - particleEvent_p->startValue.pos.y) * (particle_p->counter - particleEvent_p->activationTime) / particleEvent_p->duration;
					}
				
				}

				if(particleEvent_p->propertyType == PARTICLE_SIZE){

					if(particle_p->counter == particleEvent_p->activationTime){
						particleEvent_p->startValue.size = particle_p->body.size;
					}

					if(particleEvent_p->type == PARTICLE_SET_EVENT){
						particle_p->body.size = particleEvent_p->targetValue.size;
					}

					if(particleEvent_p->type == PARTICLE_LINEAR_FADE_EVENT){
						particle_p->body.size.x = particleEvent_p->startValue.size.x + (particleEvent_p->targetValue.size.x - particleEvent_p->startValue.size.x) * (particle_p->counter - particleEvent_p->activationTime) / particleEvent_p->duration;
						particle_p->body.size.y = particleEvent_p->startValue.size.y + (particleEvent_p->targetValue.size.y - particleEvent_p->startValue.size.y) * (particle_p->counter - particleEvent_p->activationTime) / particleEvent_p->duration;
					}
					
				}
				
			}
		
		}

		if(removed){
			continue;
		}

		Vec2f_add(&particle_p->physics.velocity, particle_p->physics.acceleration);
		Vec2f_add(&particle_p->body.pos, particle_p->physics.velocity);

		//update sprite
		sprite_p->body = particle_p->body;

		particle_p->counter++;

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

		//handle obstacle sprite being stuck
		sprite_p = World_Sprite_setToLayer_returnsNewPointerAndUpdatesIndex(world_p, sprite_p, &obstacle_p->spriteIndex, GAME_LAYER_OBSTACLES);
		String_set(sprite_p->texture, "obstacle", SMALL_STRING_SIZE);

		if(obstacleBodyPair_p->isStuckY
		|| obstacleBodyPair_p->isStuckX){
			sprite_p->color = COLOR_RED;
			String_set(sprite_p->texture, "obstacle", SMALL_STRING_SIZE);
			sprite_p = World_Sprite_setToLayer_returnsNewPointerAndUpdatesIndex(world_p, sprite_p, &obstacle_p->spriteIndex, GAME_LAYER_BLOCKED_ENTITIES);
		}
		if(obstacleBodyPair_p->isStuckY){
			sprite_p->body.size.y = 1;
		}
		if(obstacleBodyPair_p->isStuckX){
			sprite_p->body.size.x = 1;
		}

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

		//handle point sprite being stuck
		sprite_p = World_Sprite_setToLayer_returnsNewPointerAndUpdatesIndex(world_p, sprite_p, &point_p->spriteIndex, GAME_LAYER_FOREGROUND);
		String_set(sprite_p->texture, "point", SMALL_STRING_SIZE);

		if(pointBodyPair_p->isStuckY
		|| pointBodyPair_p->isStuckX){
			sprite_p->color = COLOR_RED;
			String_set(sprite_p->texture, "obstacle", SMALL_STRING_SIZE);
			sprite_p = World_Sprite_setToLayer_returnsNewPointerAndUpdatesIndex(world_p, sprite_p, &point_p->spriteIndex, GAME_LAYER_BLOCKED_ENTITIES);
		}
		if(pointBodyPair_p->isStuckY){
			sprite_p->body.size.y = 1;
		}
		if(pointBodyPair_p->isStuckX){
			sprite_p->body.size.x = 1;
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

		//sprite_p->texture = "door-key";
		//sprite_p->alpha = 1;

		//handle door key sprite being stuck
		sprite_p = World_Sprite_setToLayer_returnsNewPointerAndUpdatesIndex(world_p, sprite_p, &doorKey_p->spriteIndex, GAME_LAYER_FOREGROUND);
		String_set(sprite_p->texture, "door-key", SMALL_STRING_SIZE);

		if(doorKeyBodyPair_p->isStuckY
		|| doorKeyBodyPair_p->isStuckX){
			sprite_p->color = COLOR_RED;
			String_set(sprite_p->texture, "obstacle", SMALL_STRING_SIZE);
			sprite_p = World_Sprite_setToLayer_returnsNewPointerAndUpdatesIndex(world_p, sprite_p, &doorKey_p->spriteIndex, GAME_LAYER_BLOCKED_ENTITIES);

		}
		if(doorKeyBodyPair_p->isStuckY){
			sprite_p->body.size.y = 1;
		}
		if(doorKeyBodyPair_p->isStuckX){
			sprite_p->body.size.x = 1;
		}

	}

	//update scale field sprites
	for(int i = 0; i < world_p->scaleFields.length; i++){

		ScaleField *scaleField_p = Array_getItemPointerByIndex(&world_p->scaleFields, i);

		Sprite *sprite_p = World_getSpriteByIndex(world_p, scaleField_p->spriteIndex);

		sprite_p->body = scaleField_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[scaleField_p->scaleType];

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

		//animate
		if(world_p->playerHasNoLegs){
			Animation_setState(&world_p->player.animation, "no-legs");
		}
		else if(playerBodyPair_p->physics.velocity.y < 0){
			Animation_setState(&world_p->player.animation, "jumping");
		}
		else if(playerBodyPair_p->physics.velocity.y > 0){
			Animation_setState(&world_p->player.animation, "falling");
		}
		else if((world_p->actions[LEFT_ACTION].down
		|| world_p->actions[RIGHT_ACTION].down)
		&& !world_p->scaling){
		//&& fabs(playerBodyPair_p->physics.velocity.x) > 0.000001){
			Animation_setState(&world_p->player.animation, "walking");
		}
		else{
			Animation_setState(&world_p->player.animation, "idle");
		}

		Animation_updateFrame(&world_p->player.animation);

		Animation_Frame *currentFrame_p = Animation_getCurrentFramePointer(&world_p->player.animation);

		sprite_p->textureCoordOffset = currentFrame_p->textureCoordOffset;

	}

	//fade out title text
	BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, world_p->player.bodyPairID);
	if(playerBodyPair_p->body.pos.x > 200 + 300
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

		//player position levels entering
		float playerPositionAreaX = 5150 + 100;

		if(playerBodyPair_p->body.pos.x > playerPositionAreaX
		&& playerBodyPair_p->body.pos.x < playerPositionAreaX + WIDTH / 2
		&& playerBodyPair_p->body.pos.y > 0){
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
		//roof top camera
		if(playerBodyPair_p->body.pos.y < -HEIGHT * 2){
			world_p->cameraTarget.y = 2.9 * HEIGHT;
		}
		if(playerBodyPair_p->body.pos.y < -HEIGHT * 2.5){
			world_p->cameraTarget.y = 3.35 * HEIGHT;
		}

		//elevator to ending and cloud camera
		if(playerBodyPair_p->body.pos.x >= 300
		&& playerBodyPair_p->body.pos.x <= 300 + WIDTH / 2
		&& playerBodyPair_p->body.pos.y > -HEIGHT * 6){
			world_p->cameraTarget.x = -300;
		}
		if(playerBodyPair_p->body.pos.x < 300
		&& playerBodyPair_p->body.pos.y > -HEIGHT * 6){
			world_p->cameraTarget.x = 0;
		}
		if(playerBodyPair_p->body.pos.x < 500
		&& playerBodyPair_p->body.pos.y > 0){
			cameraSpeedX = 20;
		}

		//starting area y levels
		if(playerBodyPair_p->body.pos.x < 400 + 300){

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

		//secret area camera
		if(playerBodyPair_p->body.pos.x > 6440){
			if(playerBodyPair_p->body.pos.y > -HEIGHT * 5 - 100){
				world_p->cameraTarget.x = -6440 + WIDTH / 2;
			}
			cameraSpeedX = 20;
		}

		//make it so that camera follows player up
		if(playerBodyPair_p->body.pos.y < -HEIGHT * 3.2 + 100){
			world_p->cameraTarget.y = -playerBodyPair_p->body.pos.y + HEIGHT - 100;
			cameraSpeedY = 10;
		}
		if(playerBodyPair_p->body.pos.y < -HEIGHT * 4.2 + 100){
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

		float offsetY = 0;

		for(int i = 1; i < 10; i++){
			if(playerBodyPair_p->body.pos.y < -HEIGHT * 9 * i){
				offsetY = -HEIGHT * 16 * i;
			}
		}

		Sprite *sprite_p = World_getSpriteByIndex(world_p, world_p->starBackgroundSpriteIndex);

		sprite_p->body.pos.x = -world_p->renderer.offset.x * 0.3;
		sprite_p->body.pos.y = (-world_p->renderer.offset.y - HEIGHT * 16 + offsetY) * 0.4;

		if(SaveData_hasFlag(&world_p->saveData, "completed-secret-levels")){
			Sprite *sprite_p = World_getSpriteByIndex(world_p, world_p->herculesStarBackgroundSpriteIndex);

			sprite_p->body.pos.x = -(world_p->renderer.offset.x) * 0.3 + 760;
			sprite_p->body.pos.y = (-world_p->renderer.offset.y) * 0.4;
		
		}

	}

	//update ending flash
	if(world_p->currentState == LEVEL_HUB_STATE){

		float beginningPosY = -HEIGHT * 9 * 4;

		if(playerBodyPair_p->body.pos.y < beginningPosY){

			world_p->endingFlashAlpha = (float)(-playerBodyPair_p->body.pos.y + beginningPosY) / (float)(HEIGHT * 90 * 2);

		}

		if(playerBodyPair_p->body.pos.y < -HEIGHT * 9 * 20){

			World_fadeTransitionToState(world_p, CREDITS_STATE);
				
		}

	}

	//handle music
	for(int i = 0; i < world_p->musicIDs.length; i++){

		size_t ID = *(size_t *)Array_getItemPointerByIndex(&world_p->musicIDs, i);

		//printf("ID: %i, volume: %f\n", ID, Audio_getSoundVolumeByID(ID));

		if(ID == world_p->currentMusicID){
			Audio_increaseSoundVolumeByID(ID, MUSIC_FADE_IN_SPEED);
		}else{
			Audio_decreaseSoundVolumeByID(ID, MUSIC_FADE_OUT_SPEED);
		}
	
	}

	if(world_p->currentState == LEVEL_HUB_STATE){

		size_t newID = 0;

		for(int i = 0; i < world_p->musicAreas.length; i++){

			MusicArea *musicArea_p = Array_getItemPointerByIndex(&world_p->musicAreas, i);

			if(checkBodyToBodyCol(playerBodyPair_p->body, musicArea_p->body)){

				if(strcmp(musicArea_p->musicName, "KEEP_CURRENT") == 0){
					newID = world_p->currentMusicID;
					continue;
				}

				for(int j = 0; j < world_p->musicIDs.length; j++){

					size_t ID = *(size_t *)Array_getItemPointerByIndex(&world_p->musicIDs, j);

					if(strcmp(musicArea_p->musicName, Audio_getSoundNameByID(ID)) == 0){
						newID = ID;
					}

				}
			}
		
		}

		if(world_p->currentMusicID != newID){
			Audio_setSoundTimeByID(newID, 0);
		}

		world_p->currentMusicID = newID;
	}

}
