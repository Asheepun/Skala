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

void World_initLevel(World *world_p){

	for(int i = 0; i < LEVELS_LENGTH; i++){
		if(strcmp(world_p->currentLevel, levels[i].name) == 0){

			levels[i].generate(world_p);

		}
	}

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

	if(world_p->scaling){
		//control scale

		if(world_p->actions[LEFT_ACTION].down){
			world_p->scale.x *= 1 + world_p->scaleSpeed * (float)HEIGHT / (float)WIDTH * sqrt(sqrt(world_p->scale.x));
			//world_p->scale.x += world_p->scaleSpeed * HEIGHT / WIDTH;
		}
		if(world_p->actions[RIGHT_ACTION].down){
			world_p->scale.x /= 1 + world_p->scaleSpeed * (float)HEIGHT / (float)WIDTH * sqrt(sqrt(world_p->scale.x));
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

		if(world_p->scale.x < 0.000001){
			world_p->scale.x = world_p->lastScale.x;
		}
		if(world_p->scale.y < 0.000001){
			world_p->scale.y = world_p->lastScale.y;
		}

	}else{
		//control player

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

	Vec2f_sub(&world_p->deltaScale, &world_p->scale);

	//logic

	Body *playerBody_p = &World_getBodyPairByID(world_p, world_p->player.bodyPairID)->body;

	//check if player is dead
	if(playerBody_p->pos.y > HEIGHT + 20
	|| playerBody_p->size.x < 1
	|| playerBody_p->size.y < 1){

		World_initLevel(world_p);

		return;

	}

	//check if level is completed
	if(world_p->points.length == 0
	&& world_p->currentState == LEVEL_STATE){

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

	World_checkAndHandleBodyPairCollisionsX(world_p, STATIC, ALL, STATIC, NONE);
	World_checkAndHandleBodyPairCollisionsX(world_p, STATIC, ALL_FROM_TOP, STATIC, NONE);
	World_checkAndHandleBodyPairCollisionsX(world_p, STATIC, ALL_SWITCH_X_Y, STATIC, NONE);

	World_checkAndHandleBodyPairCollisionsX(world_p, -1, ALL_FROM_TOP, -1, ALL);

	World_checkAndHandleBodyPairCollisionsX(world_p, -1, ALL_SWITCH_X_Y, -1, ALL_FROM_TOP);

	World_checkAndHandleBodyPairCollisionsX(world_p, -1, ALL_SWITCH_X_Y, STATIC, -1);

	World_checkAndHandleBodyPairCollisionsX(world_p, MOVABLE, -1, STATIC, -1);

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
			&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
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

	World_checkAndHandleBodyPairCollisionsY(world_p, STATIC, ALL, STATIC, NONE);
	World_checkAndHandleBodyPairCollisionsY(world_p, STATIC, ALL_FROM_TOP, STATIC, NONE);
	World_checkAndHandleBodyPairCollisionsY(world_p, STATIC, ALL_SWITCH_X_Y, STATIC, NONE);

	World_checkAndHandleBodyPairCollisionsY(world_p, -1, ALL_FROM_TOP, -1, ALL);

	World_checkAndHandleBodyPairCollisionsY(world_p, -1, ALL_SWITCH_X_Y, -1, ALL_FROM_TOP);

	World_checkAndHandleBodyPairCollisionsY(world_p, -1, ALL_SWITCH_X_Y, STATIC, -1);

	World_checkAndHandleBodyPairCollisionsY(world_p, MOVABLE, -1, STATIC, -1);

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
			&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)
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

		bodyPair_p->body.pos.x += bodyPair_p->physics.velocity.x / physicsScale.x;
	
	}

	//handle collisions x
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

		bodyPair_p->body.pos.y += bodyPair_p->physics.velocity.y / physicsScale.y;
	
	}

	//handle collisions y
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
	}

	//check if player collides with door keys
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

		if(checkBodyToBodyCol(playerBodyPair_p->body, doorKeyBodyPair_p->body)){
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

			if(checkBodyToBodyCol(doorBodyPair_p->body, doorKeyBodyPair_p->body)){

				World_removeDoorByID(world_p, door_p->entityHeader.ID);
				World_removeDoorKeyByID(world_p, doorKey_p->entityHeader.ID);

				i--;
				j--;

			}

		}
	}

	//check if player collides with points
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		Body *pointBody_p = &((BodyPair *)Array_getItemPointerByID(&world_p->bodyPairs, point_p->bodyPairID))->body;
	
		if(checkBodyToBodyCol(*playerBody_p, *pointBody_p)){

			World_removePointByID(world_p, point_p->entityHeader.ID);

			i--;

		}

	}

	//check if player collides with level doors
	for(int i = 0; i < world_p->levelDoors.length; i++){

		LevelDoor *levelDoor_p = Array_getItemPointerByIndex(&world_p->levelDoors, i);
	
		if(checkBodyToBodyCol(*playerBody_p, levelDoor_p->body)){

			//world_p->currentLevel = 0;
			world_p->currentLevel = levelDoor_p->levelName;

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

		world_p->renderer.offset.x = floor(WIDTH / 2 - playerBodyPair_p->body.pos.x);

		if(world_p->renderer.offset.x > 0){
			world_p->renderer.offset.x = 0;
		}
	
	}


}
