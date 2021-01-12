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

	world_p->fonts[0] = getFont("assets/times.ttf", 20);

	Array_init(&world_p->textures, sizeof(OpenglUtils_Texture));

	Array_init(&world_p->buttons, sizeof(Button));
	Array_init(&world_p->bodyPairs, sizeof(BodyPair));
	Array_init(&world_p->points, sizeof(Point));
	Array_init(&world_p->obstacles, sizeof(Obstacle));
	Array_init(&world_p->scaleFields, sizeof(ScaleField));

	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){
		Array_init(&world_p->spriteLayers[i], sizeof(Sprite));
	}

	world_p->fadeTransitionCounter = 0;
	world_p->initCurrentState = false;

	World_restore(world_p);

}

void World_restore(World *world_p){

	world_p->quit = false;

	Vec2f_set(&world_p->scale, 1, 1);
	Vec2f_set(&world_p->lastScale, 1, 1);
	Vec2f_set(&world_p->deltaScale, 0, 0);
	Vec2f_set(&world_p->origin, 0, HEIGHT);

	world_p->scaling = false;
	world_p->scaleSpeed = 0.05;

	Array_clear(&world_p->buttons);
	Array_clear(&world_p->bodyPairs);
	Array_clear(&world_p->points);
	Array_clear(&world_p->obstacles);
	Array_clear(&world_p->scaleFields);

	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){
		Array_clear(&world_p->spriteLayers[i]);
	}

	world_p->fpsTextID = World_addTextSprite(world_p, getVec2f(10, 10), "", 0, COLOR_WHITE, GAME_LAYER_TEXT);

}

void World_fadeTransitionToState(World *world_p, enum WorldState nextStateAfterTransition){

	world_p->fadeTransitionCounter = FADE_TRANSITION_TIME;

	world_p->nextStateAfterTransition = nextStateAfterTransition;

}

void World_switchToAndInitState(World *world_p, enum WorldState newState){

	world_p->currentState = newState;

	world_p->initCurrentState = true;

}

void World_initPlayer(World *w, Vec2f pos, enum ScaleType scaleType){
	Player *p = &w->player;

	EntityHeader_init(&p->entityHeader);

	int collisionWeight = 0;

	Body body;

	Body_init(&body, pos, getVec2f(14, 20), scaleType, MOVABLE);

	p->bodyPairID = World_addBodyPair(w, body);

	//p->runAcceleration = 0.8;
	p->runAcceleration = 0.6;
	//p->jumpSpeed = -4.5;
	p->jumpSpeed = -4;
	//p->resistance = getVec2f(0.8, 1);
	p->resistance = getVec2f(0.8, 1);
	//p->gravity = 0.45;
	p->gravity = 0.35;
	p->onGround = false;

	Physics_init(&p->physics);

	p->spriteID = World_addSprite(w, pos, body.size, SCALE_TYPE_COLORS[body.scaleType], "player", 1, GAME_LAYER_FOREGROUND);

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

	return sprite_p->entityHeader.ID;

}

size_t World_addTextSprite(World *world_p, Vec2f pos, char *text, unsigned int font, Vec4f color, enum SpriteLayer layer){
	
	Sprite *sprite_p = Array_addItem(&world_p->spriteLayers[layer]);

	EntityHeader_init(&sprite_p->entityHeader);

	sprite_p->type = TEXT_SPRITE;

	sprite_p->pos = pos;
	sprite_p->color = color;
	sprite_p->font = font;
	sprite_p->alpha = 1;

	strcpy(sprite_p->text, text);

	return sprite_p->entityHeader.ID;

}

size_t World_addButton(World *world_p, Vec2f pos, Vec2f size, char *texture, enum SpriteLayer layer){

	Button *button_p = Array_addItem(&world_p->buttons);

	EntityHeader_init(&button_p->entityHeader);

	button_p->buttonType = SPRITE_BUTTON;

	button_p->spriteID = World_addSprite(world_p, pos, size, SPRITE_COLORS[SPRITE_COLOR_WHITE], texture, 1, layer);

	return button_p->entityHeader.ID;

}

unsigned int World_addTextButton(World *world_p, Vec2f pos, char *text, enum SpriteLayer layer){
	
	Button *button_p = Array_addItem(&world_p->buttons);

	EntityHeader_init(&button_p->entityHeader);

	button_p->buttonType = TEXT_BUTTON;

	button_p->spriteID = World_addTextSprite(world_p, pos, text, 0, COLOR_WHITE, layer);

	return button_p->entityHeader.ID;

}

size_t World_addBodyPair(World *world_p, Body body){

	BodyPair *bodyPair_p = Array_addItem(&world_p->bodyPairs);

	EntityHeader_init(&bodyPair_p->entityHeader);

	bodyPair_p->body = body;
	bodyPair_p->originBody = bodyPair_p->body;

	bodyPair_p->originScaleType = body.scaleType;

	return bodyPair_p->entityHeader.ID;

}

size_t World_addObstacle(World *world_p, Vec2f pos, Vec2f size, enum ScaleType scaleType){

	Obstacle *obstacle_p = Array_addItem(&world_p->obstacles);

	EntityHeader_init(&obstacle_p->entityHeader);

	Body body;
	Body_init(&body, pos, size, scaleType, STATIC);

	obstacle_p->bodyPairID = World_addBodyPair(world_p, body);

	Physics_init(&obstacle_p->physics);

	obstacle_p->spriteID = World_addSprite(world_p, pos, size, SCALE_TYPE_COLORS[body.scaleType], "obstacle", 1, GAME_LAYER_BACKGROUND);

	return obstacle_p->entityHeader.ID;

}

size_t World_addPoint(World *world_p, Vec2f pos, enum ScaleType scaleType){

	Point *point_p = Array_addItem(&world_p->points);

	EntityHeader_init(&point_p->entityHeader);

	int collisionWeight = 1;
	if(scaleType == NONE){
		collisionWeight = 2;
	}

	Body body;
	Body_init(&body, pos, getVec2f(10, 10), scaleType, STATIC);

	point_p->bodyPairID = World_addBodyPair(world_p, body);

	Physics_init(&point_p->physics);

	point_p->spriteID = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[body.scaleType], "point", 1, GAME_LAYER_FOREGROUND);

	return point_p->entityHeader.ID;

}

size_t World_addScaleField(World *world_p, Vec2f pos, Vec2f size, enum ScaleType scaleType){

	ScaleField *scaleField_p = Array_addItem(&world_p->scaleFields);

	EntityHeader_init(&scaleField_p->entityHeader);

	Body_init(&scaleField_p->body, pos, size, scaleType, STATIC);

	scaleField_p->scaleType = scaleType;

	scaleField_p->spriteID = World_addSprite(world_p, pos, scaleField_p->body.size, SCALE_TYPE_COLORS[scaleField_p->body.scaleType], "obstacle", 0.5, GAME_LAYER_FOREGROUND);

	return scaleField_p->entityHeader.ID;

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

Vec2f World_getOriginFromScaleType(World *w, enum ScaleType scaleType){
	if(scaleType == NONE){
		return w->origin;
	}
	if(scaleType == ALL){
		return w->origin;
	}
	if(scaleType == ALL_FROM_TOP){
		return getVec2f(0, 0);
	}
}

Vec2f World_getScaleFromScaleType(World *w, enum ScaleType scaleType){
	if(scaleType == NONE){
		return getVec2f(1, 1);
	}
	if(scaleType == ALL){
		return w->scale;
	}
	if(scaleType == ALL_FROM_TOP){
		return w->scale;
	}
}

Vec2f World_getLastScaleFromScaleType(World *w, enum ScaleType scaleType){
	if(scaleType == NONE){
		return getVec2f(1, 1);
	}
	if(scaleType == ALL){
		return w->lastScale;
	}
	if(scaleType == ALL_FROM_TOP){
		return w->lastScale;
	}
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

