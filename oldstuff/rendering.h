#ifndef RENDERING_H_
#define RENDERING_H_

#include "stdbool.h"
#include "geometry.h"
#include "utils.h"

typedef struct Pixel{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}Pixel;

typedef struct Texture{
	unsigned char *data;
	char *name;
	int width;
	int height;
	bool inited;
}Texture;

typedef struct TextureSlice{
	unsigned int x;
	unsigned int width;
}TextureSlice;

typedef struct TextureSliceMap{
	Array *sliceArrays;
	char *name;
}TextureSliceMap;

typedef struct Renderer{

	float width;
	float height;

	Vec2f scale;
	Vec2f offset;

	Pixel *pixels;

	Array textures;

	int singleThreadDrawSizeLimit;

	bool multiThreadingOn;

	float fadeOutAlpha;

}Renderer;

unsigned int getPixelIndexFromTexture(Texture, int, int);

Vec4f getColorFromTexture(Texture, int, int);

Pixel getPixelFromColor(Vec4f);

void Texture_loadData(Texture *, char *);

void Texture_freeData(Texture *);

void TextureSliceMap_init(TextureSliceMap *, Texture);

void Renderer_init(Renderer *);

void Renderer_setSize(Renderer *, float, float);

int Renderer_getPixelIndex(Renderer *, int, int);

void Renderer_fillRect(Renderer *, int, int, int, int, Vec4f);

void Renderer_drawTextureSliceMapInSingleColor(Renderer *, float, float, float, float, TextureSliceMap, float, Vec4f);

void Renderer_drawTextureInSingleColor(Renderer *, float, float, float, float, Texture, float, Vec4f);

void Renderer_testSingleThreadDrawSizeLimit(Renderer *);

//void Renderer_loadTexture(Renderer *, char *);

#endif
