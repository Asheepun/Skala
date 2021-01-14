#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

int blockerAnimationCount = 25;

size_t levelStateFadeTransitionID = 6900;//så att det inte krockar första gången

void World_initLevelState(World *world_p){

	levels[world_p->currentLevel].generate(world_p);

	//!!!!!!!!!!!
	World_levelState(world_p);//VERY TEMPORARY, JUST MAKE SCALING NOT LOOK BAD FOR A FRAME
	//!!!!!!!!!!!

	//world_p->currentState = World_levelState;

}

void World_levelState(World *world_p){

	if(world_p->fadeTransitionCounter > FADE_TRANSITION_TIME / 2
	&& world_p->points.length == 0){
		return;
	}

	printf("---\n");

	if(world_p->actions[MENU_ACTION].downed){

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

	if(world_p->scaling){
		//control scale

		if(world_p->actions[LEFT_ACTION].down){
			world_p->scale.x *= 1 + world_p->scaleSpeed * HEIGHT / WIDTH;
		}
		if(world_p->actions[RIGHT_ACTION].down){
			world_p->scale.x *= 1 - world_p->scaleSpeed * HEIGHT / WIDTH;
		}
		if(world_p->actions[DOWN_ACTION].down){
			world_p->scale.y *= 1 + world_p->scaleSpeed;
		}
		if(world_p->actions[UP_ACTION].down){
			world_p->scale.y *= 1 - world_p->scaleSpeed;
		}

		if(world_p->scale.x < 0.000001){
			world_p->scale.x = world_p->lastScale.x;
		}
		if(world_p->scale.y < 0.000001){
			world_p->scale.y = world_p->lastScale.y;
		}

	}else{
		//control player

		if(world_p->actions[LEFT_ACTION].down){
			player_p->physics.acceleration.x += -player_p->runAcceleration;
		}
		if(world_p->actions[RIGHT_ACTION].down){
			player_p->physics.acceleration.x += player_p->runAcceleration;
		}

		if((world_p->actions[JUMP_ACTION].down)
		&& player_p->onGround){
			player_p->physics.velocity.y += player_p->jumpSpeed;
		}

	}

	Vec2f_sub(&world_p->deltaScale, &world_p->scale);

	//logic

	Body *playerBody_p = &World_getBodyPairByID(world_p, world_p->player.bodyPairID)->body;

	//check if player is dead
	if(playerBody_p->pos.y > HEIGHT + 20
	|| playerBody_p->size.x < 1
	|| playerBody_p->size.y < 1){

		World_initLevelState(world_p);
		//world_p->
		//world_p->currentState = World_initLevelState;

		return;

	}

	/*
	if(world_p->fadeTransitionCounter == FADE_TRANSITION_TIME / 2
	&& levelStateFadeTransitionID == world_p->currentFadeTransitionID){

		World_initLevelSelect(world_p);

		unlockNearbyLevels();

		world_p->currentState = World_levelSelectState;

		return;
		
	}
	*/

	//check if level is completed
	if(world_p->points.length == 0){

		/*
		if(world_p->fadeTransitionCounter < 0){
			levelStateFadeTransitionID = World_fadeTransition(world_p);
		}

		return;
		*/

		//World_initLevelSelect(world_p);

		unlockNearbyLevels();

		World_fadeTransitionToState(world_p, LEVEL_SELECT_STATE);
		//world_p->fadeTransitionCounter = FADE_TRANSITION_TIME;
		//world_p->nextStateAfterTransition = World_initLevelSelect;//?
		//world_p->nextStateAfterTransition = LEVEL_SELECT_STATE;

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

	World_checkAndHandleBodyPairCollisionsX(world_p, -1, ALL_SWITCH_X_Y, -1, -1);

	World_checkAndHandleBodyPairCollisionsX(world_p, -1, ALL_SWITCH_X_Y, -1, ALL_FROM_TOP);

	World_checkAndHandleBodyPairCollisionsX(world_p, -1, ALL_FROM_TOP, -1, ALL);

	World_checkAndHandleBodyPairCollisionsX(world_p, MOVABLE, -1, STATIC, -1);

	World_checkAndHandleBodyPairCollisionsX(world_p, STATIC, ALL, STATIC, NONE);
	World_checkAndHandleBodyPairCollisionsX(world_p, STATIC, ALL_FROM_TOP, STATIC, NONE);
	World_checkAndHandleBodyPairCollisionsX(world_p, STATIC, ALL_SWITCH_X_Y, STATIC, NONE);

	//check oub x
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		if(bodyPair_p->body.pos.x < 0){
			bodyPair_p->body.pos.x = 0;
		}
	
	}

	//check if x needs rescaling
	bool rescaleX = false;

	for(int i = 0; i < world_p->bodyPairs.length; i++){
		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			&& (bodyPair1_p->canCollideWithPlayer || bodyPair2_p->canCollideWithPlayer)
			//&& !compareFloatToFloat(world_p->deltaScale.x, 0)
			&& i != j){
				rescaleX = true;
			}
		
		}
	}

	//rescale x
	if(rescaleX){

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			bodyPair_p->body.pos.x = bodyPair_p->lastBody.pos.x;
			bodyPair_p->body.size.x = bodyPair_p->lastBody.size.x;

		}

		world_p->scale.x = world_p->lastScale.x;
	
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

	World_checkAndHandleBodyPairCollisionsY(world_p, -1, ALL_SWITCH_X_Y, -1, -1);

	World_checkAndHandleBodyPairCollisionsY(world_p, -1, ALL_SWITCH_X_Y, -1, ALL_FROM_TOP);

	World_checkAndHandleBodyPairCollisionsY(world_p, -1, ALL_FROM_TOP, -1, ALL);

	World_checkAndHandleBodyPairCollisionsY(world_p, MOVABLE, -1, STATIC, -1);

	World_checkAndHandleBodyPairCollisionsY(world_p, STATIC, ALL, STATIC, NONE);
	World_checkAndHandleBodyPairCollisionsY(world_p, STATIC, ALL_FROM_TOP, STATIC, NONE);
	World_checkAndHandleBodyPairCollisionsY(world_p, STATIC, ALL_SWITCH_X_Y, STATIC, NONE);

	//check oub y
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		//player dies if he falls down so he should not col with the bottom of the screen
		if(bodyPair_p->entityHeader.ID == player_p->bodyPairID){
			continue;
		}

		if(bodyPair_p->scaleType == ALL_FROM_TOP
		&& bodyPair_p->body.pos.y < 0){
			bodyPair_p->body.pos.y = 0;
		}

		if((bodyPair_p->scaleType == ALL
		|| bodyPair_p->scaleType == ALL_SWITCH_X_Y)
		&& bodyPair_p->body.pos.y + bodyPair_p->body.size.y > HEIGHT){
			bodyPair_p->body.pos.y = HEIGHT - bodyPair_p->body.size.y;
		}
	
	}

	//check if y needs rescaling
	bool rescaleY = false;

	for(int i = 0; i < world_p->bodyPairs.length; i++){
		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			&& !compareFloatToFloat(world_p->deltaScale.y, 0)
			&& (bodyPair1_p->canCollideWithPlayer || bodyPair2_p->canCollideWithPlayer)
			&& i != j){
				rescaleY = true;
			}
		
		}
	}

	//rescale y
	if(rescaleY){

		for(int i = 0; i < world_p->bodyPairs.length; i++){

			BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

			bodyPair_p->body.pos.y = bodyPair_p->lastBody.pos.y;
			bodyPair_p->body.size.y = bodyPair_p->lastBody.size.y;

		}

		world_p->scale.y = world_p->lastScale.y;
	
	}

	/*
	 * INTE KLAR MÅSTE FIXA LITE PÅ!!!
	 *
	 */

	//calculate player scale for physics
	BodyPair *playerBodyPair_p = World_getBodyPairByID(world_p, world_p->player.bodyPairID);
	playerBody_p = &playerBodyPair_p->body;

	Vec2f playerScale = playerBodyPair_p->originBody.size;
	Vec2f_div(&playerScale, &playerBody_p->size);

	//Body playerOriginBody = *playerBody_p;

	/*
	{
		Vec2f scale = World_getScaleFromScaleType(world_p, playerBody_p->scaleType);
		//Vec2f lastScale = World_getLastScaleFromScaleType(world_p, playerBody_p->scaleType);
		Vec2f origin = World_getOriginFromScaleType(world_p, playerBody_p->scaleType);

		Body_unScale(&playerOriginBody, origin, scale);
	
	}
	*/

	//Vec2f playerScale = World_getScaleFromScaleType(world_p, playerBody_p->scaleType);
	//Vec2f playerScale = playerOriginBody.size;
	//Vec2f_div(&playerScale, &playerBody_p->size);

	//Vec2f_log(playerOriginBody.size);
	//Vec2f_log(playerScale);

	//update player physics

	player_p->physics.acceleration.y += player_p->gravity;

	Vec2f_mul(&player_p->physics.velocity, &player_p->resistance);

	Vec2f_add(&player_p->physics.velocity, &player_p->physics.acceleration);

	//move player y
	playerBody_p->pos.y += player_p->physics.velocity.y / playerScale.y;

	//check player col y
	bool col = false;
	Body colBody;
	for(int i = 0; i < world_p->obstacles.length; i++){

		Obstacle *obstacle_p = Array_getItemPointerByIndex(&world_p->obstacles, i);
		BodyPair *obstacleBodyPair_p = World_getBodyPairByID(world_p, obstacle_p->bodyPairID);

		if(checkBodyPairToBodyPairCollision(*playerBodyPair_p, *obstacleBodyPair_p)){
			col = true;
			colBody = obstacleBodyPair_p->body;
		}
	}

	//handle player col y
	player_p->onGround = false;

	if(col){
		if(player_p->physics.velocity.y < 0){
			playerBody_p->pos.y = colBody.pos.y + colBody.size.y;
		}
		if(player_p->physics.velocity.y > 0){
			playerBody_p->pos.y = colBody.pos.y - playerBody_p->size.y;
			player_p->onGround = true;
		}

		player_p->physics.velocity.y = 0;
	}

	//move player x
	playerBody_p->pos.x += player_p->physics.velocity.x / playerScale.x;
	
	//check player col x
	col = false;
	colBody;
	for(int i = 0; i < world_p->obstacles.length; i++){
		Obstacle *obstacle_p = Array_getItemPointerByIndex(&world_p->obstacles, i);

		Body *obstacleBody_p = &World_getBodyPairByID(world_p, obstacle_p->bodyPairID)->body;
		BodyPair *obstacleBodyPair_p = World_getBodyPairByID(world_p, obstacle_p->bodyPairID);

		if(checkBodyPairToBodyPairCollision(*playerBodyPair_p, *obstacleBodyPair_p)){
			col = true;
			colBody = obstacleBodyPair_p->body;
		}
	}

	//handle player col x
	if(col){
		if(player_p->physics.velocity.x > 0){
			playerBody_p->pos.x = colBody.pos.x - playerBody_p->size.x;
		}
		if(player_p->physics.velocity.x < 0){
			playerBody_p->pos.x = colBody.pos.x + colBody.size.x;
		}
		player_p->physics.velocity.x = 0;
	}

	//check and handle player oub x
	if(playerBody_p->pos.x < 0){
		playerBody_p->pos.x = 0;
	}

	//reset player acceleration
	player_p->physics.acceleration = getVec2f(0, 0);

	//check if player collides with points
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		Body *pointBody_p = &((BodyPair *)Array_getItemPointerByID(&world_p->bodyPairs, point_p->bodyPairID))->body;
	
		if(checkBodyToBodyCol(*playerBody_p, *pointBody_p)){

			World_removePointByID(world_p, point_p->entityHeader.ID);

			i--;

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

	}

	//update point sprites
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		BodyPair *pointBodyPair_p = World_getBodyPairByID(world_p, point_p->bodyPairID);

		Sprite *sprite_p = World_getSpriteByID(world_p, point_p->spriteID);

		sprite_p->body = pointBodyPair_p->body;

		sprite_p->color = SCALE_TYPE_COLORS[pointBodyPair_p->scaleType];

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
	}

	world_p->renderer.offset = getVec2f(0, 0);

}
