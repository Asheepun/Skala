#ifndef RENDERING_H_
#define RENDERING_H_

#include "stdbool.h"
#include "geometry.h"
#include "utils.h"

typedef struct Pixel{
	unsigned char b;
	unsigned char g;
	unsigned char r;
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
}TextureSliceMap;

typedef struct Renderer{

	int windowWidth;
	int windowHeight;

	Pixel *screenPixels;

}Renderer;

unsigned int getPixelIndexFromTexture(Texture, int, int);

Vec4f getColorFromTexture(Texture, int, int);

Pixel getPixelFromColor(Vec4f);

void Texture_freeData(Texture *);

void TextureSliceMap_init(TextureSliceMap *, Texture);

#endif
