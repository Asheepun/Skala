#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "openglUtils.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"

void World_init(World *world_p){

	memset(world_p, 0, sizeof(World));

	world_p->saveData.playerHubPos = getVec2f(1650, 50);

	Array_init(&world_p->fonts, sizeof(Font));

	Array_init(&world_p->textures, sizeof(OpenglUtils_Texture));

	Array_init(&world_p->buttons, sizeof(Button));
	Array_init(&world_p->bodyPairs, sizeof(BodyPair));
	Array_init(&world_p->points, sizeof(Point));
	Array_init(&world_p->obstacles, sizeof(Obstacle));
	Array_init(&world_p->doors, sizeof(Door));
	Array_init(&world_p->doorKeys, sizeof(DoorKey));
	Array_init(&world_p->scaleFields, sizeof(ScaleField));
	Array_init(&world_p->levelDoors, sizeof(LevelDoor));

	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){
		Array_init(&world_p->spriteLayers[i], sizeof(Sprite));
	}

	world_p->fadeTransitionCounter = 0;
	world_p->initCurrentState = false;

	//load font "times"
	for(int i = 0; i < 20; i++){

		int fontSize = i * 5;

		Font *font_p = Array_addItem(&world_p->fonts);

		*font_p = getFont("assets/times.ttf", fontSize);

		sprintf(font_p->name, "times%i", fontSize);

	}

	world_p->quit = false;

	World_restore(world_p);

}

void World_restore(World *world_p){

	world_p->quit = false;

	Vec2f_set(&world_p->scale, 1, 1);
	Vec2f_set(&world_p->lastScale, 1, 1);
	Vec2f_set(&world_p->deltaScale, 0, 0);
	Vec2f_set(&world_p->origin, 0, HEIGHT);

	world_p->scaling = false;
	//world_p->scaleSpeed = 0.05;
	//world_p->scaleSpeed = 0.045;
	world_p->scaleSpeed = 0.035;

	Array_clear(&world_p->buttons);
	Array_clear(&world_p->bodyPairs);
	Array_clear(&world_p->points);
	Array_clear(&world_p->obstacles);
	Array_clear(&world_p->doors);
	Array_clear(&world_p->doorKeys);
	Array_clear(&world_p->scaleFields);
	Array_clear(&world_p->levelDoors);

	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){
		Array_clear(&world_p->spriteLayers[i]);
	}

	world_p->fpsTextID = World_addTextSprite(world_p, getVec2f(10, 10), "", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

}

void World_fadeTransitionToState(World *world_p, enum WorldState nextStateAfterTransition){

	world_p->fadeTransitionCounter = FADE_TRANSITION_TIME;

	world_p->nextStateAfterTransition = nextStateAfterTransition;

}

void World_switchToAndInitState(World *world_p, enum WorldState newState){

	world_p->currentState = newState;

	world_p->initCurrentState = true;

}

void World_initPlayer(World *world_p, Vec2f pos, enum ScaleType scaleType){
	Player *player_p = &world_p->player;

	EntityHeader_init(&player_p->entityHeader);

	int collisionWeight = 0;

	Body body;

	Body_init(&body, pos, getVec2f(14, 20));

	player_p->bodyPairID = World_addBodyPair(world_p, body, scaleType, MOVABLE, PLAYER);

	Physics *physics_p = &World_getBodyPairByID(world_p, player_p->bodyPairID)->physics;

	//physics_p->gravity = 0.35;
	physics_p->gravity = 0.23;
	physics_p->resistance = getVec2f(0.88, 1);

	//p->runAcceleration = 0.8;
	player_p->runAcceleration = 0.33;
	//p->jumpSpeed = -4.5;
	//player_p->jumpSpeed = -4;
	player_p->jumpSpeed = -3.4;

	player_p->facing = RIGHT;

	player_p->spriteID = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[scaleType], "player", 1, GAME_LAYER_FOREGROUND);

}

size_t World_addSprite(World *world_p, Vec2f pos, Vec2f size, Vec4f color, char *texture, float alpha, enum SpriteLayer layer){

	Sprite *sprite_p = Array_addItem(&world_p->spriteLayers[layer]);

	EntityHeader_init(&sprite_p->entityHeader);

	sprite_p->type = REGULAR_SPRITE;

	sprite_p->body.pos = pos;
	sprite_p->body.size = size;
	sprite_p->color = color;
	sprite_p->texture = texture;
	sprite_p->alpha = alpha;

	sprite_p->facing = RIGHT;

	return sprite_p->entityHeader.ID;

}

size_t World_addTextSprite(World *world_p, Vec2f pos, char *text, char *fontName, Vec4f color, enum SpriteLayer layer){
	
	Sprite *sprite_p = Array_addItem(&world_p->spriteLayers[layer]);

	EntityHeader_init(&sprite_p->entityHeader);

	sprite_p->type = TEXT_SPRITE;

	sprite_p->pos = pos;
	sprite_p->color = color;
	sprite_p->fontName = fontName;
	sprite_p->alpha = 1;

	sprite_p->facing = RIGHT;

	strcpy(sprite_p->text, text);

	return sprite_p->entityHeader.ID;

}

size_t World_addButton(World *world_p, Vec2f pos, Vec2f size, char *texture, enum SpriteLayer layer){

	Button *button_p = Array_addItem(&world_p->buttons);

	EntityHeader_init(&button_p->entityHeader);

	button_p->buttonType = SPRITE_BUTTON;

	button_p->spriteID = World_addSprite(world_p, pos, size, COLOR_WHITE, texture, 1, layer);

	return button_p->entityHeader.ID;

}

unsigned int World_addTextButton(World *world_p, Vec2f pos, char *text, enum SpriteLayer layer){
	
	Button *button_p = Array_addItem(&world_p->buttons);

	EntityHeader_init(&button_p->entityHeader);

	button_p->buttonType = TEXT_BUTTON;

	button_p->spriteID = World_addTextSprite(world_p, pos, text, "times20", COLOR_WHITE, layer);

	return button_p->entityHeader.ID;

}

size_t World_addBodyPair(World *world_p, Body body, enum ScaleType scaleType, enum CollisionWeight collisionWeight, enum EntityType entityType){

	BodyPair *bodyPair_p = Array_addItem(&world_p->bodyPairs);

	EntityHeader_init(&bodyPair_p->entityHeader);

	bodyPair_p->body = body;
	bodyPair_p->originBody = bodyPair_p->body;

	bodyPair_p->scaleType = scaleType;
	bodyPair_p->originScaleType = scaleType;
	bodyPair_p->collisionWeight = collisionWeight;
	bodyPair_p->entityType = entityType;

	//bodyPair_p->canCollideWithPlayer = canCollideWithPlayer;

	Physics_init(&bodyPair_p->physics);

	return bodyPair_p->entityHeader.ID;

}

size_t World_addObstacle(World *world_p, Vec2f pos, Vec2f size, enum ScaleType scaleType){

	Obstacle *obstacle_p = Array_addItem(&world_p->obstacles);

	EntityHeader_init(&obstacle_p->entityHeader);

	Body body;
	Body_init(&body, pos, size);

	obstacle_p->bodyPairID = World_addBodyPair(world_p, body, scaleType, STATIC, OBSTACLE);

	Physics_init(&obstacle_p->physics);

	obstacle_p->spriteID = World_addSprite(world_p, pos, size, SCALE_TYPE_COLORS[scaleType], "obstacle", 1, GAME_LAYER_BACKGROUND);

	return obstacle_p->entityHeader.ID;

}

size_t World_addPoint(World *world_p, Vec2f pos, enum ScaleType scaleType){

	Point *point_p = Array_addItem(&world_p->points);

	EntityHeader_init(&point_p->entityHeader);

	Body body;
	Body_init(&body, pos, getVec2f(10, 10));

	point_p->bodyPairID = World_addBodyPair(world_p, body, scaleType, STATIC, POINT);

	Physics_init(&point_p->physics);

	point_p->spriteID = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[scaleType], "point", 1, GAME_LAYER_FOREGROUND);

	return point_p->entityHeader.ID;

}

size_t World_addDoor(World *world_p, Vec2f pos, Vec2f size, enum ScaleType scaleType){

	Door *door_p = Array_addItem(&world_p->doors);

	EntityHeader_init(&door_p->entityHeader);

	//Physics_init(&doorKey_p->physics);
	//doorKey_p->gravity = 0.35;

	Body body;
	Body_init(&body, pos, size);

	door_p->bodyPairID = World_addBodyPair(world_p, body, scaleType, STATIC, DOOR);

	door_p->spriteID = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[scaleType], "door", 1, GAME_LAYER_FOREGROUND);

	return door_p->entityHeader.ID;

}

size_t World_addDoorKey(World *world_p, Vec2f pos, enum ScaleType scaleType){

	DoorKey *doorKey_p = Array_addItem(&world_p->doorKeys);

	EntityHeader_init(&doorKey_p->entityHeader);

	//Physics_init(&doorKey_p->physics);
	//doorKey_p->gravity = 0.35;

	Body body;
	Body_init(&body, pos, getVec2f(20, 10));

	doorKey_p->bodyPairID = World_addBodyPair(world_p, body, scaleType, MOVABLE, DOOR_KEY);

	doorKey_p->spriteID = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[scaleType], "door-key", 1, GAME_LAYER_FOREGROUND);

	Physics *physics_p = &World_getBodyPairByID(world_p, doorKey_p->bodyPairID)->physics;

	physics_p->gravity = 0.35;
	physics_p->resistance = getVec2f(0.9, 0.9);

	doorKey_p->facing = RIGHT;

	return doorKey_p->entityHeader.ID;

}

size_t World_addScaleField(World *world_p, Vec2f pos, Vec2f size, enum ScaleType scaleType){

	ScaleField *scaleField_p = Array_addItem(&world_p->scaleFields);

	EntityHeader_init(&scaleField_p->entityHeader);

	Body_init(&scaleField_p->body, pos, size);

	scaleField_p->scaleType = scaleType;

	scaleField_p->spriteID = World_addSprite(world_p, pos, scaleField_p->body.size, SCALE_TYPE_COLORS[scaleField_p->scaleType], "obstacle", 0.5, GAME_LAYER_FOREGROUND);

	return scaleField_p->entityHeader.ID;

}

size_t World_addLevelDoor(World *world_p, Vec2f pos, char *levelName){

	LevelDoor *levelDoor_p = Array_addItem(&world_p->levelDoors);

	EntityHeader_init(&levelDoor_p->entityHeader);

	Body_init(&levelDoor_p->body, pos, getVec2f(20, 15));

	levelDoor_p->levelName = levelName;

	levelDoor_p->spriteID = World_addSprite(world_p, pos, levelDoor_p->body.size, COLOR_WHITE, "level-door", 1, GAME_LAYER_FOREGROUND);

	return levelDoor_p->entityHeader.ID;

}

void World_removeSpriteByID(World *world_p, size_t ID){
	
	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){

		Sprite *sprite_p = Array_getItemPointerByID(&world_p->spriteLayers[i], ID);

		if(sprite_p != NULL){
			Array_removeItemByID(&world_p->spriteLayers[i], ID);
		}
	
	}

}

void World_removeButtonByID(World *world_p, size_t ID){

	Button *button_p = Array_getItemPointerByID(&world_p->buttons, ID);

	World_removeSpriteByID(world_p, button_p->spriteID);

	Array_removeItemByID(&world_p->buttons, ID);

}

void World_removePointByID(World *world_p, size_t ID){

	Point *point_p = Array_getItemPointerByID(&world_p->points, ID);
	
	World_removeSpriteByID(world_p, point_p->spriteID);

	Array_removeItemByID(&world_p->bodyPairs, point_p->bodyPairID);

	Array_removeItemByID(&world_p->points, ID);

}

void World_removeDoorByID(World *world_p, size_t ID){

	Door *door_p = Array_getItemPointerByID(&world_p->doors, ID);
	
	World_removeSpriteByID(world_p, door_p->spriteID);

	Array_removeItemByID(&world_p->bodyPairs, door_p->bodyPairID);

	Array_removeItemByID(&world_p->doors, ID);

}

void World_removeDoorKeyByID(World *world_p, size_t ID){

	DoorKey *doorKey_p = Array_getItemPointerByID(&world_p->doorKeys, ID);
	
	World_removeSpriteByID(world_p, doorKey_p->spriteID);

	Array_removeItemByID(&world_p->bodyPairs, doorKey_p->bodyPairID);

	Array_removeItemByID(&world_p->doorKeys, ID);

}

BodyPair *World_getBodyPairByID(World *world_p, size_t ID){
	return Array_getItemPointerByID(&world_p->bodyPairs, ID);
}

Sprite *World_getSpriteByID(World *world_p, size_t ID){

	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){

		Sprite *sprite_p = Array_getItemPointerByID(&world_p->spriteLayers[i], ID);

		if(sprite_p != NULL){
			return sprite_p;
		}
	
	}

	return NULL;

}

Button *World_getButtonByID(World *world_p, size_t ID){
	return Array_getItemPointerByID(&world_p->buttons, ID);
}

Vec2f World_getOriginFromScaleType(World *world_p, enum ScaleType scaleType){
	if(scaleType == NONE){
		return world_p->origin;
	}
	if(scaleType == ALL){
		return world_p->origin;
	}
	if(scaleType == ALL_FROM_TOP){
		return getVec2f(0, 0);
	}
	if(scaleType == ALL_SWITCH_X_Y){
		return world_p->origin;
	}
}

Vec2f World_getScaleFromScaleType(World *world_p, enum ScaleType scaleType){
	if(scaleType == NONE){
		return getVec2f(1, 1);
	}
	if(scaleType == ALL){
		return world_p->scale;
	}
	if(scaleType == ALL_FROM_TOP){
		return world_p->scale;
	}
	if(scaleType == ALL_SWITCH_X_Y){
		return getVec2f(world_p->scale.y, world_p->scale.x);
	}
}

Vec2f World_getLastScaleFromScaleType(World *world_p, enum ScaleType scaleType){
	if(scaleType == NONE){
		return getVec2f(1, 1);
	}
	if(scaleType == ALL){
		return world_p->lastScale;
	}
	if(scaleType == ALL_FROM_TOP){
		return world_p->lastScale;
	}
	if(scaleType == ALL_SWITCH_X_Y){
		return getVec2f(world_p->lastScale.y, world_p->lastScale.x);
	}
}

bool BodyPair_isScalable(BodyPair *bodyPair_p){

	if(bodyPair_p->scaleType == ALL
	|| bodyPair_p->scaleType == ALL_FROM_TOP
	|| bodyPair_p->scaleType == ALL_SWITCH_X_Y){
		return true;
	}

	return false;

}

void Action_init(Action *a){
	a->down = false;
	a->downed = false;
	a->bindingsLength = 0;
}

void Action_addBinding(Action *a, int key){
	a->bindings[a->bindingsLength] = key;
	a->bindingsLength++;
}

/*
void World_BodyPair_scaleBodies(World *world_p, BodyPair *bodyPair_p){

	Array_clear(&bodyPair_p->bodies);
	
	Body *body1_p = Array_addItem(&bodyPair_p->bodies);

	*body1_p = bodyPair_p->originBody;

	Body_scaleX(body1_p, bodyPair_p->originBody.scaleType);

}
*/

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
	
	if(/*checkBodyToBodyColCastToInt(BodyPair_getDeltaBody(bodyPair1), BodyPair_getDeltaBody(bodyPair2))*/true){

		if(checkBodyToBodyColCastToInt(bodyPair1.body, bodyPair2.body)
		&& bodyPair1.lastBody.size.x >= 1 && bodyPair2.lastBody.size.x >= 1//make it so that small things don't appear on the wrong side when they are scaled up
		&& bodyPair1.lastBody.size.y >= 1 && bodyPair2.lastBody.size.y >= 1){
			return true;
		}

		//return true;
	}

	return false;

	/*
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
		return checkBodyToBodyColCastToInt(BodyPair_getDeltaBody(bodyPair1), BodyPair_getDeltaBody(bodyPair2));
	}else{
		return checkBodyToBodyColCastToInt(bodyPair1.body, bodyPair2.body);
	}
	*/
}

bool checkIfBodyPairsCanCollide(BodyPair bodyPair1, BodyPair bodyPair2){
	return !(bodyPair1.entityType == PLAYER && bodyPair2.entityType == POINT)
		&& !(bodyPair1.entityType == PLAYER && bodyPair2.entityType == DOOR_KEY)
		&& !(bodyPair1.entityType == POINT && bodyPair2.entityType == PLAYER)
		&& !(bodyPair1.entityType == DOOR_KEY && bodyPair2.entityType == PLAYER)

		&& !(bodyPair1.entityType == DOOR && bodyPair2.entityType == DOOR_KEY)
		&& !(bodyPair1.entityType == DOOR_KEY && bodyPair2.entityType == DOOR)

		&& bodyPair1.entityType != SCALE_FIELD
		&& bodyPair2.entityType != SCALE_FIELD;
}

void World_checkAndHandleBodyPairCollisionsX(World *world_p, enum CollisionWeight collisionWeight1, enum ScaleType scaleType1, enum CollisionWeight collisionWeight2, enum ScaleType scaleType2){

	for(int i = 0; i < world_p->bodyPairs.length; i++){
		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			&& i != j
			//&& (bodyPair1_p->canCollideWithPlayer || bodyPair2_p->canCollideWithPlayer)
			&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)

			&& (bodyPair1_p->collisionWeight == collisionWeight1 || collisionWeight1 == -1)
			&& (bodyPair2_p->collisionWeight == collisionWeight2 || collisionWeight2 == -1)
			&& (bodyPair1_p->scaleType == scaleType1 || scaleType1 == -1)
			&& (bodyPair2_p->scaleType == scaleType2 || scaleType2 == -1)){

				float bodyPairCenterX = bodyPair1_p->lastBody.pos.x + bodyPair1_p->lastBody.size.x / 2;
				float bodyPair2CenterX = bodyPair2_p->lastBody.pos.x + bodyPair2_p->lastBody.size.x / 2;

				if(bodyPairCenterX < bodyPair2CenterX){
					bodyPair1_p->body.pos.x = bodyPair2_p->body.pos.x - bodyPair1_p->body.size.x;
				}
				if(bodyPairCenterX > bodyPair2CenterX){
					bodyPair1_p->body.pos.x = bodyPair2_p->body.pos.x + bodyPair2_p->body.size.x;
				}

			}
		
		}
	}

}

void World_checkAndHandleBodyPairCollisionsY(World *world_p, enum CollisionWeight collisionWeight1, enum ScaleType scaleType1, enum CollisionWeight collisionWeight2, enum ScaleType scaleType2){

	for(int i = 0; i < world_p->bodyPairs.length; i++){
		for(int j = 0; j < world_p->bodyPairs.length; j++){

			BodyPair *bodyPair1_p = Array_getItemPointerByIndex(&world_p->bodyPairs, i);
			BodyPair *bodyPair2_p = Array_getItemPointerByIndex(&world_p->bodyPairs, j);

			if(checkBodyPairToBodyPairCollision(*bodyPair1_p, *bodyPair2_p)
			&& i != j
			//&& (bodyPair_p->canCollideWithPlayer || bodyPair2_p->canCollideWithPlayer)
			&& checkIfBodyPairsCanCollide(*bodyPair1_p, *bodyPair2_p)

			&& (bodyPair1_p->collisionWeight == collisionWeight1 || collisionWeight1 == -1)
			&& (bodyPair2_p->collisionWeight == collisionWeight2 || collisionWeight2 == -1)
			&& (bodyPair1_p->scaleType == scaleType1 || scaleType1 == -1)
			&& (bodyPair2_p->scaleType == scaleType2 || scaleType2 == -1)){

				float bodyPair1CenterY = bodyPair1_p->lastBody.pos.y + bodyPair1_p->lastBody.size.y / 2;
				float bodyPair2CenterY = bodyPair2_p->lastBody.pos.y + bodyPair2_p->lastBody.size.y / 2;

				if(bodyPair1CenterY < bodyPair2CenterY){
					bodyPair1_p->body.pos.y = bodyPair2_p->body.pos.y - bodyPair1_p->body.size.y;
				}
				if(bodyPair1CenterY > bodyPair2CenterY){
					bodyPair1_p->body.pos.y = bodyPair2_p->body.pos.y + bodyPair2_p->body.size.y;
				}

			}
		
		}
	}

}

Vec2f BodyPair_getPhysicsScale(BodyPair *bodyPair_p){

	Vec2f physicsScale = bodyPair_p->originBody.size;
	Vec2f_div(&physicsScale, &bodyPair_p->body.size);

	return physicsScale;

}
