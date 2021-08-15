//#include "glad/glad.h"
//#include "SDL2/SDL.h"
//#include "stdbool.h"
#include "game.h"
#include "levels.h"

#include "engine/renderer2d.h"
#include "engine/array.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "geometry.h"
//#include "openglUtils.h"
//#include "stb_truetype.h"
//#include "text.h"
//#include "utils.h"

void World_init(World *world_p){

	memset(world_p, 0, sizeof(World));

	SaveData_init(&world_p->saveData);

	SaveData_read(&world_p->saveData);

	for(int i = 0; i < NUMBER_OF_LEVEL_HUB_ROOMS; i++){
		Array_init(&world_p->roomLevels[i], sizeof(char *));
	}
	world_p->addedRoomLevels = false;

	Array_init(&world_p->fonts, sizeof(Font));

	Array_init(&world_p->textures, sizeof(Renderer2D_Texture));

	Array_init(&world_p->buttons, sizeof(Button));
	Array_init(&world_p->bodyPairs, sizeof(BodyPair));
	Array_init(&world_p->points, sizeof(Point));
	Array_init(&world_p->obstacles, sizeof(Obstacle));
	Array_init(&world_p->doors, sizeof(Door));
	Array_init(&world_p->doorKeys, sizeof(DoorKey));
	Array_init(&world_p->scaleFields, sizeof(ScaleField));
	Array_init(&world_p->levelDoors, sizeof(LevelDoor));
	Array_init(&world_p->particles, sizeof(Particle));

	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){

		unsigned int maxLength = 32;

		if(i == GAME_LAYER_FURNITURE
		|| i == GAME_LAYER_OBSTACLES
		|| i == GAME_LAYER_PARTICLES){
			maxLength = 1024;
		}

		IndexSafeArray_init(&world_p->spriteLayers[i], sizeof(Sprite), 255);
	}

	world_p->fadeTransitionCounter = 0;
	world_p->initCurrentState = false;

	//load font "times"

	//world.timesFont = getFont("assets/times.ttf", 100);

	//load font "times"
	for(int i = 0; i < 20; i++){

		int fontSize = i * 5;

		Font *font_p = Array_addItem(&world_p->fonts);

		*font_p = getFont("assets/times.ttf", fontSize);

		sprintf(font_p->name, "times%i", fontSize);

	}

	world_p->cameraPos = getVec2f(0, 0);
	world_p->cameraTarget = getVec2f(0, 0);
	world_p->snapCamera = false;

	world_p->quit = false;

	//init scales
	
	//world_p->scaleSpeed = 0.05;
	//world_p->scaleSpeed = 0.045;
	//world_p->scaleSpeed = 0.035;
	world_p->scaleSpeed = 0.025;
	//world_p->scaleSpeed = 10;

	//world_p->scaleSpeed = 0.035 * HEIGHT;

	/*
	world_p->scalesX[ORIGIN_SCALE_INDEX] = 1;
	world_p->scalesY[ORIGIN_SCALE_INDEX] = 1;

	//printf("%f\n", (float)HEIGHT / (float)WIDTH);

	for(int i = ORIGIN_SCALE_INDEX + 1; i < NUMBER_OF_SCALES; i++){
		float lastScaleX = world_p->scalesX[i - 1];
		float lastScaleY = world_p->scalesY[i - 1];
		world_p->scalesX[i] = lastScaleX * (1 + world_p->scaleSpeed * sqrt(sqrt(lastScaleX) * (float)HEIGHT / (float)WIDTH));
		world_p->scalesY[i] = lastScaleY * (1 + world_p->scaleSpeed * sqrt(sqrt(lastScaleY)));
	}
	for(int i = ORIGIN_SCALE_INDEX - 1; i >= 0; i--){
		float lastScaleX = world_p->scalesX[i + 1];
		float lastScaleY = world_p->scalesY[i + 1];
		world_p->scalesX[i] = lastScaleX / (1 + world_p->scaleSpeed * sqrt(sqrt(lastScaleX)) * (float)HEIGHT / (float)WIDTH);
		world_p->scalesY[i] = lastScaleY / (1 + world_p->scaleSpeed * sqrt(sqrt(lastScaleY)));
	}
	for(int i = 0; i < NUMBER_OF_SCALES; i++){
		float accuracy = 1000000;
		//world_p->scalesX[i] = round(world_p->scalesX[i] * accuracy) / accuracy;
		//world_p->scalesY[i] = round(world_p->scalesY[i] * accuracy) / accuracy;
	}
	*/

	World_restore(world_p);

}

void World_restore(World *world_p){

	world_p->quit = false;

	//Vec2f_set(&world_p->scale, 1, 1);
	//Vec2f_set(&world_p->lastScale, 1, 1);
	//Vec2f_set(&world_p->deltaScale, 0, 0);
	Vec2f_set(&world_p->origin, 0, HEIGHT);

	world_p->scaling = false;
	world_p->scalingByPlayerPosition = false;
	world_p->playerHasNoLegs = false;

	Array_clear(&world_p->buttons);
	Array_clear(&world_p->bodyPairs);
	Array_clear(&world_p->points);
	Array_clear(&world_p->obstacles);
	Array_clear(&world_p->doors);
	Array_clear(&world_p->doorKeys);
	Array_clear(&world_p->scaleFields);
	Array_clear(&world_p->levelDoors);
	Array_clear(&world_p->particles);

	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){
		//Array_clear(&world_p->spriteLayers[i]);
		IndexSafeArray_clear(&world_p->spriteLayers[i]);
	}

	world_p->fpsTextID = World_addTextSprite(world_p, getVec2f(10, 10), "", "times20", COLOR_WHITE, GAME_LAYER_TEXT);

	world_p->endingFlashAlpha = 0;

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

	player_p->holdingKey = false;

	player_p->facing = RIGHT;

	player_p->spriteIndex = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[scaleType], "player", 1, GAME_LAYER_FOREGROUND);

}

size_t World_addSprite(World *world_p, Vec2f pos, Vec2f size, Renderer2D_Color color, char *texture, float alpha, enum SpriteLayer layer){

	//Sprite *sprite_p = Array_addItem(&world_p->spriteLayers[layer]);
	unsigned int index = IndexSafeArray_addItem(&world_p->spriteLayers[layer]);
	Sprite *sprite_p = IndexSafeArray_getItemPointer(&world_p->spriteLayers[layer], index);

	//EntityHeader_init(&sprite_p->entityHeader);

	sprite_p->type = REGULAR_SPRITE;

	sprite_p->body.pos = pos;
	sprite_p->body.size = size;
	sprite_p->color = color;
	sprite_p->texture = texture;
	sprite_p->alpha = alpha;
	sprite_p->currentLayer = layer;

	sprite_p->facing = RIGHT;
	sprite_p->borderSize = getVec2f(0, 0);

	return index + 1000000 * layer;
	//return sprite_p->entityHeader.ID;

}

size_t World_addTextSprite(World *world_p, Vec2f pos, char *text, char *fontName, Renderer2D_Color color, enum SpriteLayer layer){
	
	//Sprite *sprite_p = Array_addItem(&world_p->spriteLayers[layer]);

	//EntityHeader_init(&sprite_p->entityHeader);

	unsigned int index = IndexSafeArray_addItem(&world_p->spriteLayers[layer]);
	Sprite *sprite_p = IndexSafeArray_getItemPointer(&world_p->spriteLayers[layer], index);

	sprite_p->type = TEXT_SPRITE;

	sprite_p->pos = pos;
	sprite_p->color = color;
	sprite_p->fontName = fontName;
	sprite_p->alpha = 1;

	sprite_p->facing = RIGHT;

	strcpy(sprite_p->text, text);

	return index + 1000000 * layer;
	//return sprite_p->entityHeader.ID;

}

size_t World_addButton(World *world_p, Vec2f pos, Vec2f size, char *texture, enum SpriteLayer layer){

	Button *button_p = Array_addItem(&world_p->buttons);

	EntityHeader_init(&button_p->entityHeader);

	button_p->buttonType = SPRITE_BUTTON;

	button_p->spriteIndex = World_addSprite(world_p, pos, size, COLOR_WHITE, texture, 1, layer);

	return button_p->entityHeader.ID;

}

size_t World_addTextButton(World *world_p, Vec2f pos, char *text, enum SpriteLayer layer){
	
	Button *button_p = Array_addItem(&world_p->buttons);

	EntityHeader_init(&button_p->entityHeader);

	button_p->buttonType = TEXT_BUTTON;

	button_p->spriteIndex = World_addTextSprite(world_p, pos, text, "times20", COLOR_WHITE, layer);

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

	//bodyPair_p->scaleIndexX = ORIGIN_SCALE_INDEX;
	//bodyPair_p->scaleIndexY = ORIGIN_SCALE_INDEX;
	//bodyPair_p->lastScaleIndexX = ORIGIN_SCALE_INDEX;
	//bodyPair_p->lastScaleIndexY = ORIGIN_SCALE_INDEX;

	bodyPair_p->playerPositionScale = getVec2f(1, 1);
	bodyPair_p->playerPositionLastScale = getVec2f(1, 1);
	//bodyPair_p->scale = getVec2f(1, 1);
	//bodyPair_p->lastScale = getVec2f(1, 1);
	bodyPair_p->scaleExponent = getVec2f(0, 0);
	bodyPair_p->lastScaleExponent = getVec2f(0, 0);

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

	obstacle_p->spriteIndex = World_addSprite(world_p, pos, size, SCALE_TYPE_COLORS[scaleType], "obstacle", 1, GAME_LAYER_OBSTACLES);

	Sprite *sprite_p = World_getSpriteByIndex(world_p, obstacle_p->spriteIndex);
	//sprite_p->borderSize = getVec2f(5, 5);

	return obstacle_p->entityHeader.ID;

}

size_t World_addPoint(World *world_p, Vec2f pos, enum ScaleType scaleType){

	Point *point_p = Array_addItem(&world_p->points);

	EntityHeader_init(&point_p->entityHeader);

	Body body;
	Body_init(&body, pos, getVec2f(10, 10));

	point_p->bodyPairID = World_addBodyPair(world_p, body, scaleType, STATIC, POINT);

	Physics_init(&point_p->physics);

	point_p->spriteIndex = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[scaleType], "point", 1, GAME_LAYER_FOREGROUND);

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

	door_p->spriteIndex = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[scaleType], "door", 1, GAME_LAYER_OBSTACLES);

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

	doorKey_p->spriteIndex = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[scaleType], "door-key", 1, GAME_LAYER_DOOR_KEYS);

	Physics *physics_p = &World_getBodyPairByID(world_p, doorKey_p->bodyPairID)->physics;

	physics_p->gravity = 0.23;
	physics_p->resistance = getVec2f(0.9, 0.9);

	doorKey_p->facing = RIGHT;

	return doorKey_p->entityHeader.ID;

}

size_t World_addScaleField(World *world_p, Vec2f pos, Vec2f size, enum ScaleType scaleType){

	ScaleField *scaleField_p = Array_addItem(&world_p->scaleFields);

	EntityHeader_init(&scaleField_p->entityHeader);

	Body_init(&scaleField_p->body, pos, size);

	scaleField_p->scaleType = scaleType;

	scaleField_p->spriteIndex = World_addSprite(world_p, pos, scaleField_p->body.size, SCALE_TYPE_COLORS[scaleField_p->scaleType], "obstacle", 0.4, GAME_LAYER_FOREGROUND);

	return scaleField_p->entityHeader.ID;

}

size_t World_addLevelDoor(World *world_p, Vec2f pos, char *levelName, enum LevelHubRoom levelHubRoom){

	LevelDoor *levelDoor_p = Array_addItem(&world_p->levelDoors);

	EntityHeader_init(&levelDoor_p->entityHeader);

	Body_init(&levelDoor_p->body, pos, getVec2f(20, 15));

	levelDoor_p->levelName = levelName;
	levelDoor_p->levelHubRoom = levelHubRoom;
	//levelDoor_p->hoverTextParticleID = -1;

	levelDoor_p->spriteIndex = World_addSprite(world_p, pos, levelDoor_p->body.size, COLOR_WHITE, "level-door", 1, GAME_LAYER_FOREGROUND);

	char *screenName;
	for(int i = 0; i < LEVELS_LENGTH; i++){
		if(strcmp(levels[i].name, levelDoor_p->levelName) == 0){
			screenName = levels[i].screenName;
		}
	}

	levelDoor_p->hoverTextParticleID = World_addFadeInTextParticle(world_p, levelDoor_p->body.pos, screenName, "times15", COLOR_WHITE, 0, 0);
	Particle *hoverTextParticle_p = World_getParticleByID(world_p, levelDoor_p->hoverTextParticleID);
	Sprite *hoverTextSprite_p = World_getSpriteByIndex(world_p, hoverTextParticle_p->spriteIndex);

	hoverTextSprite_p->pos.y -= 20;
	hoverTextSprite_p->pos.x += 10;

	Body hoverTextSpriteBody = World_TextSprite_getBody(world_p, hoverTextSprite_p);
	hoverTextSprite_p->pos.x -= hoverTextSpriteBody.size.x / 2;

	levelDoor_p->hasPlayerBelow = false;

	union ParticleProperty startAlpha;
	startAlpha.alpha = 0;
	Particle_addEvent(hoverTextParticle_p, PARTICLE_SET_EVENT, PARTICLE_ALPHA, startAlpha, 0, 0);

	if(!world_p->addedRoomLevels){

		char **roomName_p = Array_addItem(&world_p->roomLevels[levelHubRoom]);
		*roomName_p = levelName;
		
	}

	return levelDoor_p->entityHeader.ID;

}

Particle *World_addParticle(World *world_p, unsigned spriteIndex){
	
	Particle *particle_p = Array_addItem(&world_p->particles);

	EntityHeader_init(&particle_p->entityHeader);

	Physics_init(&particle_p->physics);

	particle_p->spriteIndex = spriteIndex;

	particle_p->counter = 0;

	Array_init(&particle_p->events, sizeof(ParticleEvent));

	return particle_p;

}

void Particle_addEvent(Particle *particle_p, enum ParticleEventType eventType, enum ParticlePropertyType propertyType, union ParticleProperty targetValue, int activationTime, int duration){

	ParticleEvent *particleEvent_p = Array_addItem(&particle_p->events);

	particleEvent_p->activationTime = particle_p->counter + activationTime;
	particleEvent_p->duration = duration;
	particleEvent_p->type = eventType;
	particleEvent_p->propertyType = propertyType;
	particleEvent_p->targetValue = targetValue;
	
}

void Particle_addRemoveEvent(Particle *particle_p, int activationTime){
	//printf("%i\n", particle_p->entityHeader.ID);

	ParticleEvent *particleEvent_p = Array_addItem(&particle_p->events);

	//printf("%i\n", particle_p->events.length);

	particleEvent_p->activationTime = particle_p->counter + activationTime;
	particleEvent_p->duration = 0;
	particleEvent_p->type = PARTICLE_REMOVE_EVENT;

}

size_t World_addFadeInTextParticle(World *world_p, Vec2f pos, char *text, char *fontName, Renderer2D_Color color, int activationTime, int durationTime){
	
	size_t spriteIndex = World_addTextSprite(world_p, pos, text, fontName, color, GAME_LAYER_PARTICLES);

	Particle *particle_p = World_addParticle(world_p, spriteIndex);

	union ParticleProperty startAlpha;
	startAlpha.alpha = 0;
	Particle_addEvent(particle_p, PARTICLE_SET_EVENT, PARTICLE_ALPHA, startAlpha, 0, 0);

	union ParticleProperty targetAlpha;
	targetAlpha.alpha = 1;
	Particle_addEvent(particle_p, PARTICLE_LINEAR_FADE_EVENT, PARTICLE_ALPHA, targetAlpha, activationTime, durationTime);

	return particle_p->entityHeader.ID;

}

size_t World_addShadow(World *world_p, Vec2f pos, Vec2f size){

	World_addSprite(world_p, pos, size, COLOR_BLACK, "obstacle", 0.7, GAME_LAYER_SHADOWS);

	//Sprite *sprite_p = 
	
}

void World_removeSpriteByIndex(World *world_p, unsigned int index){

	unsigned int layer = floor(index / 1000000);
	unsigned int relativeIndex = index % 1000000;

	IndexSafeArray_removeItem(&world_p->spriteLayers[layer], relativeIndex);
	
	/*
	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){

		Sprite *sprite_p = Array_getItemPointerByID(&world_p->spriteLayers[i], ID);

		if(sprite_p != NULL){
			Array_removeItemByID(&world_p->spriteLayers[i], ID);
		}
	
	}
	*/

}

void World_removeButtonByID(World *world_p, size_t ID){

	Button *button_p = Array_getItemPointerByID(&world_p->buttons, ID);

	World_removeSpriteByIndex(world_p, button_p->spriteIndex);

	Array_removeItemByID(&world_p->buttons, ID);

}

void World_removePointByID(World *world_p, size_t ID){

	Point *point_p = Array_getItemPointerByID(&world_p->points, ID);
	
	World_removeSpriteByIndex(world_p, point_p->spriteIndex);

	Array_removeItemByID(&world_p->bodyPairs, point_p->bodyPairID);

	Array_removeItemByID(&world_p->points, ID);

}

void World_removeDoorByID(World *world_p, size_t ID){

	Door *door_p = Array_getItemPointerByID(&world_p->doors, ID);
	
	World_removeSpriteByIndex(world_p, door_p->spriteIndex);

	Array_removeItemByID(&world_p->bodyPairs, door_p->bodyPairID);

	Array_removeItemByID(&world_p->doors, ID);

}

void World_removeDoorKeyByID(World *world_p, size_t ID){

	DoorKey *doorKey_p = Array_getItemPointerByID(&world_p->doorKeys, ID);
	
	World_removeSpriteByIndex(world_p, doorKey_p->spriteIndex);

	Array_removeItemByID(&world_p->bodyPairs, doorKey_p->bodyPairID);

	Array_removeItemByID(&world_p->doorKeys, ID);

}

void World_removeParticleByID(World *world_p, size_t ID){

	Particle *particle_p = Array_getItemPointerByID(&world_p->particles, ID);
	
	World_removeSpriteByIndex(world_p, particle_p->spriteIndex);

	Array_free(&particle_p->events);

	Array_removeItemByID(&world_p->particles, ID);

}

BodyPair *World_getBodyPairByID(World *world_p, size_t ID){
	return Array_getItemPointerByID(&world_p->bodyPairs, ID);
}

Sprite *World_getSpriteByIndex(World *world_p, unsigned int index){

	unsigned int layer = floor(index / 1000000);
	unsigned int relativeIndex = index % 1000000;

	return IndexSafeArray_getItemPointer(&world_p->spriteLayers[layer], relativeIndex);

	/*
	for(int i = 0; i < NUMBER_OF_SPRITE_LAYERS; i++){

		//if(i == GAME_LAYER_PARTICLES){
			//continue;
		//}

		Sprite *sprite_p = Array_getItemPointerByID(&world_p->spriteLayers[i], ID);

		if(sprite_p != NULL){
			return sprite_p;
		}
	
	}
	*/

	//return NULL;

}

Button *World_getButtonByID(World *world_p, size_t ID){
	return Array_getItemPointerByID(&world_p->buttons, ID);
}

Particle *World_getParticleByID(World *world_p, size_t ID){
	return Array_getItemPointerByID(&world_p->particles, ID);
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

/*
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
*/

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

bool isBetween(float a, float b, float c){
	return a > b && a < c
		|| a > c && a < b;
}

bool checkBodyPairToBodyPairCollision(BodyPair bodyPair1, BodyPair bodyPair2){
	
	if(/*checkBodyToBodyColCastToInt(BodyPair_getDeltaBody(bodyPair1), BodyPair_getDeltaBody(bodyPair2))*/true){

		//if(checkBodyToBodyColRoundFloats(bodyPair1.body, bodyPair2.body)
		//if(checkBodyToBodyCol(bodyPair1.body, bodyPair2.body)
		if(checkBodyToBodyColRoundTo2Dec(bodyPair1.body, bodyPair2.body)

		//|| checkBodyToBodyColRoundFloats(BodyPair_getDeltaBody(bodyPair1), BodyPair_getDeltaBody(bodyPair2))

		//&& !(
			
		//)

		//&& !(bodyPair1.lastBody.pos.x < 
		
		//|| (bodyPair1.body.pos.x + bodyPair1.body.size.x > bodyPair2.body.pos.x
		//&& bodyPair1.body.pos.x < bodyPair2.body.pos.x + bodyPair2.body.size.x
		//&& bodyPair1.body.size.x >= 1 && bodyPair2.body.size.x >= 1
		//&& bodyPair1.body.size.y >= 1 && bodyPair2.body.size.y >= 1)
//
		//&& (bodyPair1.body.pos.y > bodyPair2.body.pos.y && bodyPair1.body.pos.y > bodyPair2.lastBody.pos.y
			//
		//)
			){
		//&& bodyPair1.lastBody.size.x >= 1 && bodyPair2.lastBody.size.x >= 1//make it so that small things don't appear on the wrong side when they are scaled up
		//&& bodyPair1.lastBody.size.y >= 1 && bodyPair2.lastBody.size.y >= 1){
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
	Vec2f_div(&physicsScale, bodyPair_p->body.size);

	return physicsScale;

}

Body World_TextSprite_getBody(World *world_p, Sprite *textSprite_p){

	Body body;
	body.pos = textSprite_p->pos;

	Font font;
	for(int i = 0; i < world_p->fonts.length; i++){

		Font *font_p = Array_getItemPointerByIndex(&world_p->fonts, i);

		if(strcmp(font_p->name, textSprite_p->fontName) == 0){
			font = *font_p;
			break;
		}
	
	}

	int width, height;
	char *data = getImageDataFromFontAndString_mustFree(font, textSprite_p->text, &width, &height);
	free(data);

	body.size.x = (float)width;
	body.size.y = (float)height;

	return body;

}

Sprite *World_Sprite_setToLayer_returnsNewPointerAndUpdatesIndex(World *world_p, Sprite *sprite_p, unsigned int *index, enum SpriteLayer newLayer){

	if(sprite_p->currentLayer != newLayer){

		Sprite spriteCopy = *sprite_p;
		spriteCopy.currentLayer = newLayer;

		World_removeSpriteByIndex(world_p, *index);

		*index = World_addSprite(world_p, getVec2f(0, 0), getVec2f(0, 0), COLOR_WHITE, "", 0, newLayer);

		Sprite *newSprite_p = World_getSpriteByIndex(world_p, *index);
		*newSprite_p = spriteCopy;

		return newSprite_p;

	}

	return sprite_p;

}

/*
void BodyPair_World_setBodyFromScaleX(BodyPair *bodyPair_p, World *world_p){

	Vec2f scale = bodyPair_p->scale;
	//Vec2f lastScale = bodyPair_p->lastScale;
	Vec2f origin = world_p->origin;

	if(bodyPair_p->scaleType == NONE){
		scale = getVec2f(1, 1);
		//lastScale = getVec2f(1, 1);
	}
	if(bodyPair_p->scaleType == ALL_FROM_TOP){
		origin = getVec2f(world_p->origin.x, world_p->origin.y - world_p->levelHeight);
	}

	float lastScaleX = bodyPair_p->originBody.size.x / bodyPair_p->body.size.x;

	Body_unScaleX(&bodyPair_p->body, origin, getVec2f(lastScaleX, 1));
	//Body_unScaleX(&bodyPair_p->body, origin, lastScale);

	Body_scaleX(&bodyPair_p->body, origin, scale);

}

void BodyPair_World_setBodyFromScaleY(BodyPair *bodyPair_p, World *world_p){

	Vec2f scale = bodyPair_p->scale;
	Vec2f origin = world_p->origin;

	if(bodyPair_p->scaleType == NONE){
		scale = getVec2f(1, 1);
	}
	if(bodyPair_p->scaleType == ALL_FROM_TOP){
		origin = getVec2f(world_p->origin.x, world_p->origin.y - world_p->levelHeight);
	}

	float lastScaleY = bodyPair_p->originBody.size.y / bodyPair_p->body.size.y;

	Body_unScaleY(&bodyPair_p->body, origin, getVec2f(1, lastScaleY));

	Body_scaleY(&bodyPair_p->body, origin, scale);

}

float BodyPair_getScaleFromBodyX(BodyPair *bodyPair_p){
	return bodyPair_p->originBody.size.x / bodyPair_p->body.size.x;
}

float BodyPair_getScaleFromBodyY(BodyPair *bodyPair_p){
	return bodyPair_p->originBody.size.y / bodyPair_p->body.size.y;
}
*/

//float exponent1 = 1.035;
float exponent1 = 1.040;
float exponent2 = 1.000001;

float exponent3 = 1.004;

Vec2f World_BodyPair_getScaleFromExponent(World *world_p, BodyPair *bodyPair_p){

	Vec2f scale = { 
   		pow(1 + (exponent1 - 1) * (float)HEIGHT / (float)WIDTH, bodyPair_p->scaleExponent.x * pow(exponent2, bodyPair_p->scaleExponent.x)),
   		pow(exponent1, bodyPair_p->scaleExponent.y * pow(exponent2, bodyPair_p->scaleExponent.y)),
	};

	if(world_p->currentState == LEVEL_HUB_STATE){
		scale.x = pow(exponent3, bodyPair_p->scaleExponent.x * pow(exponent2, bodyPair_p->scaleExponent.x));
	}

	return scale;

}

Vec2f World_BodyPair_getLastScaleFromExponent(World *world_p, BodyPair *bodyPair_p){

	Vec2f scale = { 
   		pow(1 + (exponent1 - 1) * (float)HEIGHT / (float)WIDTH, bodyPair_p->lastScaleExponent.x * pow(exponent2, bodyPair_p->lastScaleExponent.x)),
   		pow(exponent1, 											bodyPair_p->lastScaleExponent.y * pow(exponent2, bodyPair_p->lastScaleExponent.y)),
	};

	if(world_p->currentState == LEVEL_HUB_STATE){
		scale.x = pow(exponent3, bodyPair_p->lastScaleExponent.x * pow(exponent2, bodyPair_p->lastScaleExponent.x));
	}

	return scale;

}

