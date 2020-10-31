#include "SDL2/SDL.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "rendering.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"
#include "levels.h"

Body BodyPair_getDeltaBody(BodyPair bodyPair){

	float west, east, north, south;
	
	Body deltaBody;

	if(bodyPair.body.pos.x < bodyPair.lastBody.pos.x){
		west = bodyPair.body.pos.x;
	}else{
		west = bodyPair.lastBody.pos.x;
	}

	if(bodyPair.body.pos.x + bodyPair.body.size.x > bodyPair.lastBody.pos.x + bodyPair.lastBody.size.x){
		east = bodyPair.body.pos.x + bodyPair.body.size.x;
	}else{
		east = bodyPair.lastBody.pos.x + bodyPair.lastBody.size.x;
	}

	if(bodyPair.body.pos.y < bodyPair.lastBody.pos.y){
		north = bodyPair.body.pos.y;
	}else{
		north = bodyPair.lastBody.pos.y;
	}

	if(bodyPair.body.pos.y + bodyPair.body.size.y > bodyPair.lastBody.pos.y + bodyPair.lastBody.size.y){
		south = bodyPair.body.pos.y + bodyPair.body.size.y;
	}else{
		south = bodyPair.lastBody.pos.y + bodyPair.lastBody.size.y;
	}

	deltaBody.pos.x = west;
	deltaBody.pos.y = north;

	deltaBody.size.x = fabs(west - east);
	deltaBody.size.y = fabs(north - south);

	return deltaBody;

}

bool checkBodyPairToBodyPairCollision(BodyPair bodyPair1, BodyPair bodyPair2){
	if((bodyPair1.body.size.x < fabs(bodyPair1.body.pos.x - bodyPair1.lastBody.pos.x)
	|| bodyPair1.body.size.x < fabs(bodyPair2.body.pos.x - bodyPair2.lastBody.pos.x)
	|| bodyPair1.body.size.y < fabs(bodyPair1.body.pos.y - bodyPair1.lastBody.pos.y)
	|| bodyPair1.body.size.y < fabs(bodyPair2.body.pos.y - bodyPair2.lastBody.pos.y)
	|| bodyPair2.body.size.x < fabs(bodyPair2.body.pos.x - bodyPair2.lastBody.pos.x)
	|| bodyPair2.body.size.x < fabs(bodyPair2.body.pos.x - bodyPair2.lastBody.pos.x)
	|| bodyPair2.body.size.y < fabs(bodyPair1.body.pos.y - bodyPair1.lastBody.pos.y)
	|| bodyPair2.body.size.y < fabs(bodyPair1.body.pos.y - bodyPair1.lastBody.pos.y))
	&& bodyPair1.body.size.x >= 1 && bodyPair2.body.size.x >= 1
	&& bodyPair1.body.size.y >= 1 && bodyPair2.body.size.y >= 1
	&& bodyPair1.lastBody.size.x >= 1 && bodyPair2.lastBody.size.x >= 1
	&& bodyPair1.lastBody.size.y >= 1 && bodyPair2.lastBody.size.y >= 1){
		return checkBodyToBodyColRoundFloats(BodyPair_getDeltaBody(bodyPair1), BodyPair_getDeltaBody(bodyPair2));
	}else{
		return checkBodyToBodyColRoundFloats(bodyPair1.body, bodyPair2.body);
	}
}

int blockerAnimationCount = 25;

void World_initLevelState(World *world_p){

	levels[world_p->currentLevel].generate(world_p);

	//!!!!!!!!!!!
	World_levelState(world_p);//VERY TEMPORARY, JUST MAKE SCALING NOT LOOK BAD FOR A FRAME
	//!!!!!!!!!!!

	world_p->currentState = World_levelState;
}

void World_levelState(World *world_p){

	printf("---\n");

	if(world_p->actions[MENU_ACTION].downed){
		world_p->currentState = World_initMenuState;
		return;
	}

	world_p->scaling = false;
	if(world_p->actions[DO_ACTION].down){
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

	}else{
		//control player

		if(world_p->actions[LEFT_ACTION].down){
			player_p->physics.acceleration.x += -player_p->runAcceleration;
		}
		if(world_p->actions[RIGHT_ACTION].down){
			player_p->physics.acceleration.x += player_p->runAcceleration;
		}

		if((world_p->actions[UP_ACTION].down)
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

		world_p->currentState = World_initLevelState;

		return;

	}

	//check if level is completed
	if(world_p->points.length == 0){

		unlockNearbyLevels();
		world_p->currentState = World_initLevelSelectState;

		return;

	}
	
	//update bodyPairs last bodies
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->lastBody = bodyPair_p->body;
		
	}

	//scale y
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		Vec2f scale = World_getScaleFromScaleType(world_p, bodyPair_p->body.scaleType);
		Vec2f lastScale = World_getLastScaleFromScaleType(world_p, bodyPair_p->body.scaleType);
		Vec2f origin = World_getOriginFromScaleType(world_p, bodyPair_p->body.scaleType);

		Body_unScaleY(&bodyPair_p->body, origin, lastScale);

		//bodyPair_p->body.size.y = roundf(bodyPair_p->body.size.y);
		//bodyPair_p->body.size.x = (int)bodyPair_p->body.size.x;
		//bodyPair_p->body.size.y = (int)bodyPair_p->body.size.y;

		Body_scaleY(&bodyPair_p->body, origin, scale);
	
	}

	//check if player collides with points y
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		Body *pointBody_p = &((BodyPair *)Array_getItemPointerByID(&world_p->bodyPairs, point_p->bodyPairID))->body;
	
		if(checkBodyToBodyCol(*playerBody_p, *pointBody_p)){

			World_removePointByID(world_p, point_p->entityHeader.ID);

			i--;

		}

	}

	//handle y collisions scalable and none scalable
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair_p, *bodyPair2_p)
			&& i != j
			&& bodyPair_p->body.scaleType != NONE
			&& bodyPair2_p->body.scaleType == NONE
			&& bodyPair2_p->body.collisionWeight == STATIC){

				float bodyPairCenterY = bodyPair_p->lastBody.pos.y + bodyPair_p->lastBody.size.y / 2;
				float bodyPair2CenterY = bodyPair2_p->lastBody.pos.y + bodyPair2_p->lastBody.size.y / 2;

				if(bodyPairCenterY < bodyPair2CenterY){
					bodyPair_p->body.pos.y = bodyPair2_p->body.pos.y - bodyPair_p->body.size.y;
				}
				if(bodyPairCenterY > bodyPair2CenterY){
					bodyPair_p->body.pos.y = bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y;
				}

			}
		
		}
	
	}

	//handle y collisions static and none static
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair_p, *bodyPair2_p)
			&& i != j
			&& bodyPair_p->body.collisionWeight == MOVABLE
			&& bodyPair2_p->body.collisionWeight == STATIC){

				float bodyPairCenterY = bodyPair_p->lastBody.pos.y + bodyPair_p->lastBody.size.y / 2;
				float bodyPair2CenterY = bodyPair2_p->lastBody.pos.y + bodyPair2_p->lastBody.size.y / 2;

				if(bodyPairCenterY < bodyPair2CenterY){
					bodyPair_p->body.pos.y = bodyPair2_p->body.pos.y - bodyPair_p->body.size.y;
				}
				if(bodyPairCenterY > bodyPair2CenterY){
					bodyPair_p->body.pos.y = bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y;
				}

			}

		}

	}

	//handle y collisions scalble and static 
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair_p, *bodyPair2_p)
			&& i != j
			&& bodyPair_p->body.collisionWeight == STATIC
			&& bodyPair2_p->body.collisionWeight == STATIC
			&& bodyPair_p->body.scaleType == ALL
			&& bodyPair2_p->body.scaleType == ALL){

				float bodyPairCenterY = bodyPair_p->lastBody.pos.y + bodyPair_p->lastBody.size.y / 2;
				float bodyPair2CenterY = bodyPair2_p->lastBody.pos.y + bodyPair2_p->lastBody.size.y / 2;

				if(bodyPairCenterY < bodyPair2CenterY){
					bodyPair_p->body.pos.y = bodyPair2_p->body.pos.y - bodyPair_p->body.size.y;
				}
				if(bodyPairCenterY > bodyPair2CenterY){
					bodyPair_p->body.pos.y = bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y;
				}

			}

		}

	}

	//check oub y
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		//player dies if he falls down so he should not col with the bottom of the screen
		if(bodyPair_p->entityHeader.ID == player_p->bodyPairID){
			continue;
		}

		if(bodyPair_p->body.scaleType == ALL_FROM_TOP
		&& bodyPair_p->body.pos.y < 0){
			bodyPair_p->body.pos.y = 0;
		}

		if(bodyPair_p->body.scaleType == ALL
		&& bodyPair_p->body.pos.y + bodyPair_p->body.size.y > HEIGHT){
			bodyPair_p->body.pos.y = HEIGHT - bodyPair_p->body.size.y;
		}
	
	}

	//check if y needs rescaling
	bool rescaleY = false;

	for(int i = 0; i < world_p->bodyPairs.length; i++){

		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair1 = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
			BodyPair *bodyPair2 = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyToBodyColRoundFloats(bodyPair1->body, bodyPair2->body)
			&& bodyPair1->lastBody.size.x >= 1 && bodyPair2->lastBody.size.x >= 1
			&& bodyPair1->lastBody.size.y >= 1 && bodyPair2->lastBody.size.y >= 1
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

	//scale x
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		Vec2f scale = World_getScaleFromScaleType(world_p, bodyPair_p->body.scaleType);
		Vec2f lastScale = World_getLastScaleFromScaleType(world_p, bodyPair_p->body.scaleType);
		Vec2f origin = World_getOriginFromScaleType(world_p, bodyPair_p->body.scaleType);

		Body_unScaleX(&bodyPair_p->body, origin, lastScale);

		//bodyPair_p->body.size.x = roundf(bodyPair_p->body.size.x);
		//bodyPair_p->body.size.x = (int)bodyPair_p->body.size.x;
		//bodyPair_p->body.size.y = (int)bodyPair_p->body.size.y;

		Body_scaleX(&bodyPair_p->body, origin, scale);
	
	}

	//check if player collides with points x
	for(int i = 0; i < world_p->points.length; i++){

		Point *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		Body *pointBody_p = &((BodyPair *)Array_getItemPointerByID(&world_p->bodyPairs, point_p->bodyPairID))->body;
	
		if(checkBodyToBodyCol(*playerBody_p, *pointBody_p)){

			World_removePointByID(world_p, point_p->entityHeader.ID);

			i--;
		}

	}

	//handle x collisions scalable and none scalable
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair_p, *bodyPair2_p)
			&& i != j
			&& bodyPair_p->body.scaleType != NONE
			&& bodyPair2_p->body.scaleType == NONE
			&& bodyPair2_p->body.collisionWeight == STATIC){

				printf("COLLED HRE!\n");
				printf("pos1: %f\n", bodyPair_p->body.pos.x);
				printf("size1: %f\n", bodyPair_p->body.size.x);
				printf("pos2: %f\n", bodyPair2_p->body.pos.x);
				printf("size2: %f\n", bodyPair2_p->body.size.x);

				float bodyPairCenterX = bodyPair_p->lastBody.pos.x + bodyPair_p->lastBody.size.x / 2;
				float bodyPair2CenterX = bodyPair2_p->lastBody.pos.x + bodyPair2_p->lastBody.size.x / 2;

				if(bodyPairCenterX < bodyPair2CenterX){
					bodyPair_p->body.pos.x = bodyPair2_p->body.pos.x - bodyPair_p->body.size.x;
				}
				if(bodyPairCenterX > bodyPair2CenterX){
					bodyPair_p->body.pos.x = bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x;
				}

			}
		
		}
	
	}

	//handle x collisions static and none static
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair_p, *bodyPair2_p)
			&& i != j
			&& bodyPair_p->body.collisionWeight == MOVABLE
			&& bodyPair2_p->body.collisionWeight == STATIC){

				float bodyPairCenterX = bodyPair_p->lastBody.pos.x + bodyPair_p->lastBody.size.x / 2;
				float bodyPair2CenterX = bodyPair2_p->lastBody.pos.x + bodyPair2_p->lastBody.size.x / 2;

				if(bodyPairCenterX < bodyPair2CenterX){
					bodyPair_p->body.pos.x = bodyPair2_p->body.pos.x - bodyPair_p->body.size.x;
				}
				if(bodyPairCenterX > bodyPair2CenterX){
					bodyPair_p->body.pos.x = bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x;
				}

			}

		}

	}

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

			BodyPair *bodyPair1 = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
			BodyPair *bodyPair2 = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyToBodyColRoundFloats(bodyPair1->body, bodyPair2->body)
			&& bodyPair1->lastBody.size.x >= 1 && bodyPair2->lastBody.size.x >= 1
			&& bodyPair1->lastBody.size.y >= 1 && bodyPair2->lastBody.size.y >= 1
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
		Body *obstacleBody_p = &World_getBodyPairByID(world_p, obstacle_p->bodyPairID)->body;

		if(checkBodyToBodyColRoundFloats(*playerBody_p, *obstacleBody_p)){
			col = true;
			colBody = *obstacleBody_p;
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

		if(checkBodyToBodyColRoundFloats(*playerBody_p, *obstacleBody_p)){
			col = true;
			colBody = *obstacleBody_p;
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

	//check collision with scale fields
	for(int i = 0; i < world_p->bodyPairs.length; i++){

		BodyPair *bodyPair_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);

		bodyPair_p->body.scaleType = bodyPair_p->originScaleType;

		for(int j = 0; j < world_p->scaleFields.length; j++){

			ScaleField *scaleField_p = Array_getItemPointerByIndex(&world_p->scaleFields, j);

			if(checkBodyToBodyColRoundFloats(bodyPair_p->body, scaleField_p->body)){

				bodyPair_p->body.scaleType = scaleField_p->scaleType;
				
			}
		
		}
	
	}

	player_p->physics.acceleration = getVec2f(0, 0);

	//update sprites

	//update obstacle sprites
	for(int i = 0; i < world_p->obstacles.length; i++){

		Obstacle *obstacle_p = Array_getItemPointerByIndex(&world_p->obstacles, i);

		Body *obstacleBody_p = &World_getBodyPairByID(world_p, obstacle_p->bodyPairID)->body;

		world_p->sprites[obstacle_p->spriteIndex].body = *obstacleBody_p;

		world_p->sprites[obstacle_p->spriteIndex].color = SCALE_TYPE_COLORS[obstacleBody_p->scaleType];

	}

	//update point sprites
	for(int i = 0; i < world_p->points.length; i++){

		Obstacle *point_p = Array_getItemPointerByIndex(&world_p->points, i);

		Body *pointBody_p = &World_getBodyPairByID(world_p, point_p->bodyPairID)->body;

		world_p->sprites[point_p->spriteIndex].body = *pointBody_p;

		world_p->sprites[point_p->spriteIndex].color = SCALE_TYPE_COLORS[pointBody_p->scaleType];

	}

	//update player sprite
	playerBody_p = &World_getBodyPairByID(world_p, world_p->player.bodyPairID)->body;
	world_p->sprites[player_p->spriteIndex].body = *playerBody_p;
	world_p->sprites[player_p->spriteIndex].color = SCALE_TYPE_COLORS[playerBody_p->scaleType];

}
