#include "math.h"
#include "stdio.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "rendering.h"

#define __WINDOW_LAYER_GL__

unsigned int getPixelIndexFromTexture(Texture texture, int x, int y){
	return (texture.width * y + x) * 4;
}

Vec4f getColorFromTexture(Texture texture, int x, int y){
	return getVec4f(
		(float)(texture.data[(texture.width * y + x) * 4 + 0] / 255),
		(float)(texture.data[(texture.width * y + x) * 4 + 1] / 255),
		(float)(texture.data[(texture.width * y + x) * 4 + 2] / 255),
		(float)(texture.data[(texture.width * y + x) * 4 + 3] / 255)
	);
}

Pixel getPixelFromColor(Vec4f color){
	Pixel pixel = { color.z * 255, color.y * 255, color.x * 255 };

	return pixel;
}

void Texture_init(Texture *texture_p){

	if(texture_p->inited){
		printf("***\n");
		printf("TEXTURE IS INITED TWICE, MUST FIRST DE INIT!\n");
		printf("***\n");
	}

	texture_p->data = NULL;
	texture_p->width = 0;
	texture_p->height = 0;
	texture_p->inited = true;
}

void TextureSliceMap_init(TextureSliceMap *textureSliceMap_p, Texture texture){

	textureSliceMap_p->sliceArrays = malloc(texture.height * sizeof(Array));

	for(int y = 0; y < texture.height; y++){

		Array_init(&textureSliceMap_p->sliceArrays[y], sizeof(TextureSlice));

		TextureSlice *currentSlice_p;
		bool transparent = true;

		for(int x = 0; x < texture.width; x++){

			unsigned int pixelIndex = getPixelIndexFromTexture(texture, x, y);

			if(texture.data[pixelIndex + 3] != 0){

				if(transparent == true){
					currentSlice_p = Array_addItem(&textureSliceMap_p->sliceArrays[y]);
					currentSlice_p->x = x;
					currentSlice_p->width = 0;
				}

				currentSlice_p->width++;


				transparent = false;
			}
			if(texture.data[pixelIndex + 3] == 0){

				transparent = true;

			}
		
		}
	
	}

	int slices = 0;
	for(int i = 0; i < texture.height; i++){
		slices += textureSliceMap_p->sliceArrays[i].length;
	}

}

void Texture_loadData(Texture *texture_p, char *imagePath){

	int *comp;

	texture_p->data = stbi_load(imagePath, &texture_p->width, &texture_p->height, &comp, 4);

	if(texture_p->data == NULL){
		printf("Failed to load texture %s\n", imagePath);
	}

}

void Texture_freeData(Texture *texture_p){
	
	free(texture_p->data);

	texture_p->data = NULL;
	
}

void Renderer_init(Renderer *renderer_p){

	renderer_p->pixels = NULL;
	renderer_p->width = 0;
	renderer_p->height = 0;

	renderer_p->scale = getVec2f(1, 1);

	Array_init(&renderer_p->textures, sizeof(Texture));

}

void Renderer_setSize(Renderer *renderer_p, int width, int height){

	renderer_p->width = width;
	renderer_p->height = height;

	if(renderer_p->pixels != NULL){
		free(renderer_p->pixels);
	}

	renderer_p->pixels = malloc(renderer_p->width * renderer_p->height * sizeof(Pixel));

}

int Renderer_getPixelIndex(Renderer *renderer_p, int x, int y){

	/*
	if(x < 0
	|| y < 0
	|| x >= renderer_p->width
	|| y >= renderer_p->height){
		return -1;
	}
	*/

#ifdef __WINDOW_LAYER_GL__
	return (renderer_p->height - 1 - y) * renderer_p->width + x;
#else
	return y * renderer_p->width + x;
#endif

}

void Renderer_fillRect(Renderer *renderer_p, int posX, int posY, int width, int height, Vec4f color){

	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){

			int pixelIndex = Renderer_getPixelIndex(renderer_p, posX + x, posY + y);

			renderer_p->pixels[pixelIndex].r = (int)(color.x * 255);
			renderer_p->pixels[pixelIndex].g = (int)(color.y * 255);
			renderer_p->pixels[pixelIndex].b = (int)(color.z * 255);

		}
	}

}

void Renderer_drawTextureInSingleColor(Renderer *renderer_p, float inputPosX, float inputPosY, float inputWidth, float inputHeight, Texture texture, float alpha, Vec4f color){

	if(inputWidth < 1
	|| inputHeight < 1){
		return;
	}

	float posX = (int)((inputPosX + renderer_p->offset.x) * renderer_p->scale.x);
	float posY = (int)((inputPosY + renderer_p->offset.y) * renderer_p->scale.y);

	float width = (int)(inputWidth * renderer_p->scale.x);
	float height = (int)(inputHeight * renderer_p->scale.y);

	float screenPosX = posX;
	float screenPosY = posY;
	float screenWidth = width;
	float screenHeight = height;

	if(screenPosX + screenWidth < 0
	|| screenPosX > renderer_p->width
	|| screenPosY + screenHeight < 0
	|| screenPosY > renderer_p->height){
		return;
	}

	if(screenPosX + screenWidth > renderer_p->width){
		screenWidth = renderer_p->width - screenPosX;
	}

	if(screenPosX < 0){
		screenWidth += screenPosX;
		screenPosX = 0;
	}

	if(screenPosY + screenHeight > renderer_p->height){
		screenHeight = renderer_p->height - screenPosY;
	}

	if(screenPosY < 0){
		screenHeight += screenPosY;
		screenPosY = 0;
	}

	for(int y = 0; y < screenHeight; y++){
		for(int x = 0; x < screenWidth; x++){

			int texturePosX = (int)((x + (screenPosX - posX)) * texture.width / width);
			int texturePosY = (int)((y + (screenPosY - posY)) * texture.height / height);

			int texturePixelIndex = getPixelIndexFromTexture(texture, texturePosX, texturePosY);
			int pixelIndex = Renderer_getPixelIndex(renderer_p, screenPosX + x, screenPosY + y);

			float textureAlpha = texture.data[texturePixelIndex + 3] / 255;

			renderer_p->pixels[pixelIndex].r = (int)((1 - (1 - color.x * alpha * textureAlpha) * (1 - renderer_p->pixels[pixelIndex].r / 255)) * 255);
			renderer_p->pixels[pixelIndex].g = (int)((1 - (1 - color.y * alpha * textureAlpha) * (1 - renderer_p->pixels[pixelIndex].g / 255)) * 255);
			renderer_p->pixels[pixelIndex].b = (int)((1 - (1 - color.z * alpha * textureAlpha) * (1 - renderer_p->pixels[pixelIndex].b / 255)) * 255);
		
		}
	}

}
