//#include "stdbool.h"
#include "game.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "geometry.h"
//#include "stb_truetype.h"
//#include "text.h"
//#include "utils.h"

void Body_init(Body *b, Vec2f pos, Vec2f size){
	b->pos = pos;
	b->size = size;
	//b->scaleType = scaleType;
	//b->collisionWeight = collisionWeight;
}

Vec2f Body_getCenter(Body b){
	Vec2f center = { b.pos.x + b.size.x / 2, b.pos.y + b.size.y / 2 };
	return center;
}

void Body_scale(Body *b, Vec2f origin, Vec2f scale){
	b->pos.x = origin.x + b->pos.x / scale.x;
	b->pos.y = origin.y - b->pos.y / scale.y;

	b->size.x /= scale.x;
	b->size.y /= scale.y;

	/*
	b->pos.x = (int)b->pos.x;
	b->size.x = (int)b->size.x;
	b->pos.y = (int)b->pos.y;
	b->size.y = (int)b->size.y;
	*/
}

void Body_unScale(Body *b, Vec2f origin, Vec2f scale){
	b->pos.x = (b->pos.x - origin.x) * scale.x;
	b->pos.y = -(b->pos.y - origin.y) * scale.y;

	b->size.x *= scale.x;
	b->size.y *= scale.y;

	/*
	b->pos.x = (int)b->pos.x;
	b->size.x = (int)b->size.x;
	b->pos.y = (int)b->pos.y;
	b->size.y = (int)b->size.y;
	*/
}

void Body_scaleX(Body *b, float origin, float scale){
	b->pos.x = origin + b->pos.x / scale;

	b->size.x /= scale;

	/*
	b->pos.x = (int)b->pos.x;
	b->size.x = (int)b->size.x;
	*/
}

void Body_scaleY(Body *b, float origin, float scale){
	b->pos.y = origin - b->pos.y / scale;

	b->size.y /= scale;

	/*
	b->pos.y = (int)b->pos.y;
	b->size.y = (int)b->size.y;
	*/
}

void Body_unScaleX(Body *b, float origin, float scale){
	b->pos.x = (b->pos.x - origin) * scale;

	b->size.x *= scale;

	/*
	b->pos.x = (int)b->pos.x;
	b->size.x = (int)b->size.x;
	*/
}

void Body_unScaleY(Body *b, float origin, float scale){
	b->pos.y = -(b->pos.y - origin) * scale;

	b->size.y *= scale;

	/*
	b->pos.y = (int)b->pos.y;
	b->size.y = (int)b->size.y;
	*/
}

bool Body_checkOub(Body b){
	return (floor(b.pos.x + b.size.x) > WIDTH
		|| floor(b.pos.x < 0)
		|| floor(b.pos.y + b.size.y) > HEIGHT
		|| floor(b.pos.y) < 0);
		//&& b.size.x != 0 
		//&& b.size.y != 0;
}

bool checkBodyToBodyColRoundFloats(Body b1, Body b2){
	return roundf(b1.pos.x + b1.size.x) > roundf(b2.pos.x)
		&& roundf(b1.pos.x) < roundf(b2.pos.x + b2.size.x)
		&& roundf(b1.pos.y + b1.size.y) > roundf(b2.pos.y)
		&& roundf(b1.pos.y) < roundf(b2.pos.y + b2.size.y)
		&& b1.size.x >= 1 && b2.size.x >= 1
		&& b1.size.y >= 1 && b2.size.y >= 1;
}

bool checkBodyToBodyColCastToInt(Body b1, Body b2){
	return (int)(b1.pos.x + b1.size.x) > (int)b2.pos.x
		&& (int)b1.pos.x < (int)(b2.pos.x + b2.size.x)
		&& (int)(b1.pos.y + b1.size.y) > (int)b2.pos.y
		&& (int)b1.pos.y < (int)(b2.pos.y + b2.size.y)
		&& b1.size.x >= 1 && b2.size.x >= 1
		&& b1.size.y >= 1 && b2.size.y >= 1;
}

float roundTo2Dec(float a){
	//return a;
	return roundf(a * 100) / 100;
}

/*
float roundTo2Dec(float a){

	char buff[32];
	memset(buff, 0, 32);

	sprintf(buff, "%0.2f", a);

	return atof(buff);

}
*/

bool checkBodyToBodyColRoundTo2Dec(Body b1, Body b2){
	return roundTo2Dec(b1.pos.x + b1.size.x) > roundTo2Dec(b2.pos.x)
		&& roundTo2Dec(b1.pos.x) < roundTo2Dec(b2.pos.x + b2.size.x)
		&& roundTo2Dec(b1.pos.y + b1.size.y) > roundTo2Dec(b2.pos.y)
		&& roundTo2Dec(b1.pos.y) < roundTo2Dec(b2.pos.y + b2.size.y)
		&& b1.size.x >= 1 && b2.size.x >= 1
		&& b1.size.y >= 1 && b2.size.y >= 1;
}

bool checkBodyToBodyCol(Body b1, Body b2){
	return (b1.pos.x + b1.size.x) > b2.pos.x
		&& b1.pos.x < (b2.pos.x + b2.size.x)
		&& (b1.pos.y + b1.size.y) > b2.pos.y
		&& b1.pos.y < (b2.pos.y + b2.size.y)
		&& b1.size.x >= 1 && b2.size.x >= 1
		&& b1.size.y >= 1 && b2.size.y >= 1;
}

void Physics_init(Physics *physics_p){
	Vec2f_set(&physics_p->velocity, 0, 0);
	Vec2f_set(&physics_p->acceleration, 0, 0);
	physics_p->resistance = getVec2f(1, 1);
	physics_p->onGround = false;
	physics_p->gravity = 0;
}
