#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "rendering.h"
#include "values.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"
#include "game.h"

void World_init(World *world_p){

	memset(world_p, 0, sizeof(World));

	world_p->fonts[0] = getFont("times.ttf", 20);

	Array_init(&world_p->textures, sizeof(Texture));

	Renderer_init(&world_p->renderer);

	Array_init(&world_p->buttons, sizeof(Button));
	Array_init(&world_p->bodyPairs, sizeof(BodyPair));
	Array_init(&world_p->points, sizeof(Point));
	Array_init(&world_p->obstacles, sizeof(Obstacle));
	Array_init(&world_p->textSprites, sizeof(TextSprite));
	Array_init(&world_p->scaleFields, sizeof(ScaleField));

	World_restore(world_p);

}

void World_restore(World *world_p){

	//RENDERING
	world_p->renderer.offset = getVec2f(0, 0);
	//RENDERING

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
		/*
	while(world_p->buttons.length > 0){
		Array_removeItemByIndex(&world_p->buttons, 0);
	}
	while(world_p->bodyPairs.length > 0){
		Array_removeItemByIndex(&world_p->bodyPairs, 0);
	}
	while(world_p->points.length > 0){
		Array_removeItemByIndex(&world_p->points, 0);
	}
	while(world_p->obstacles.length > 0){
		Array_removeItemByIndex(&world_p->obstacles, 0);
	}
	*/
	while(world_p->textSprites.length > 0){
		TextSprite *textSprite_p = Array_getItemPointerByIndex(&world_p->textSprites, 0);
		World_removeTextSpriteByID(world_p, textSprite_p->entityHeader.ID);
	}

	for(int i = 0; i < world_p->spritesLength + world_p->spritesGaps; i++){
		world_p->sprites[i].active = false;
	}
	world_p->spritesLength = 0;
	world_p->spritesGaps = 0;

	world_p->fpsTextID = World_addTextSprite(world_p, getVec2f(10, 10), "", 0, COLOR_WHITE);

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

	p->spriteIndex = World_addSprite(w, pos, body.size, SCALE_TYPE_COLORS[body.scaleType], "player", 1);

}

size_t World_addSprite(World *w, Vec2f pos, Vec2f size, enum SpriteColor color, char *texture, float alpha){
	size_t index;

	for(int i = 0; i < w->spritesLength + 1; i++){
		if(!w->sprites[i].active){
			index = i;
			if(i < w->spritesLength){
				w->spritesGaps--;
			}
		}
	}

	w->spritesLength++;

	Sprite *s = &w->sprites[index];

	s->active = true;

	s->body.pos = pos;
	s->body.size = size;
	s->color = color;
	s->texture = texture;
	s->alpha = alpha;

	return index;
}

size_t World_addTextSprite(World *world_p, Vec2f pos, char *text, unsigned int font, Vec4f color){
	
	TextSprite *textSprite_p = Array_addItem(&world_p->textSprites);

	EntityHeader_init(&textSprite_p->entityHeader);

	//textSprite_p->texture = getTextureFromFontAndString_mustFree(world_p->fonts[font], text);

	//textSprite_p->body.size.x = textSprite_p->texture.width;
	//textSprite_p->body.size.y = textSprite_p->texture.height;
	textSprite_p->pos = pos;
	textSprite_p->color = color;
	//textSprite_p->text = text;
	textSprite_p->font = font;
	textSprite_p->alpha = 1;

	strcpy(textSprite_p->text, text);

	//String_init(textSprite_p->text, )

	//World_TextSprite_updateText(world_p, textSprite_p, text);

	return textSprite_p->entityHeader.ID;

}

size_t World_addButton(World *world_p, Vec2f pos, Vec2f size, char *texture){

	Button *button_p = Array_addItem(&world_p->buttons);

	EntityHeader_init(&button_p->entityHeader);

	button_p->buttonType = SPRITE_BUTTON;

	button_p->spriteIndex = World_addSprite(world_p, pos, size, SPRITE_COLOR_WHITE, texture, 1);

	return button_p->entityHeader.ID;

}

unsigned int World_addTextButton(World *world_p, Vec2f pos, char *text){
	
	Button *button_p = Array_addItem(&world_p->buttons);

	EntityHeader_init(&button_p->entityHeader);

	button_p->buttonType = TEXT_BUTTON;

	button_p->textSpriteID = World_addTextSprite(world_p, pos, text, 0, COLOR_WHITE);

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

	obstacle_p->spriteIndex = World_addSprite(world_p, pos, size, SCALE_TYPE_COLORS[body.scaleType], "obstacle", 1);

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

	point_p->spriteIndex = World_addSprite(world_p, pos, body.size, SCALE_TYPE_COLORS[body.scaleType], "point", 1);

	return point_p->entityHeader.ID;

}

size_t World_addScaleField(World *world_p, Vec2f pos, Vec2f size, enum ScaleType scaleType){

	ScaleField *scaleField_p = Array_addItem(&world_p->scaleFields);

	EntityHeader_init(&scaleField_p->entityHeader);

	Body_init(&scaleField_p->body, pos, size, scaleType, STATIC);

	scaleField_p->scaleType = scaleType;

	scaleField_p->spriteIndex = World_addSprite(world_p, pos, scaleField_p->body.size, SCALE_TYPE_COLORS[scaleField_p->body.scaleType], "obstacle", 0.5);

	return scaleField_p->entityHeader.ID;

}

void World_removeTextSpriteByID(World *world_p, size_t ID){
	
	TextSprite *textSprite_p = Array_getItemPointerByID(&world_p->textSprites, ID);

	if(textSprite_p == NULL){
		
		return;
	}

	Texture_freeData(&textSprite_p->texture);

	Array_removeItemByID(&world_p->textSprites, ID);

}

void World_removeSprite(World *w, size_t index){

	w->sprites[index].active = false;

	if(index < w->spritesLength - 1){
		w->spritesGaps++;
	}

	w->spritesLength--;

}

void World_removeButtonByID(World *world_p, size_t ID){

	Button *button_p = Array_getItemPointerByID(&world_p->buttons, ID);

	if(button_p->buttonType == SPRITE_BUTTON){
		World_removeSprite(world_p, button_p->spriteIndex);
	}

	if(button_p->buttonType == TEXT_BUTTON){
		World_removeTextSpriteByID(world_p, button_p->textSpriteID);
	}

	Array_removeItemByID(&world_p->buttons, ID);

}

void World_removePointByID(World *world_p, size_t ID){

	Point *point_p = Array_getItemPointerByID(&world_p->points, ID);
	
	World_removeSprite(world_p, point_p->spriteIndex);

	Array_removeItemByID(&world_p->bodyPairs, point_p->bodyPairID);

	Array_removeItemByID(&world_p->points, ID);

}

BodyPair *World_getBodyPairByID(World *world_p, size_t ID){
	return Array_getItemPointerByID(&world_p->bodyPairs, ID);
};

TextSprite *World_getTextSpriteByID(World *world_p, size_t ID){
	return Array_getItemPointerByID(&world_p->textSprites, ID);
};

/*
void World_TextSprite_updateText(World *world_p, TextSprite *textSprite_p, char *text){
	textSprite_p->texture = getTextureFromFontAndString_mustFree(world_p->fonts[textSprite_p->font], text);
}
*/

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
