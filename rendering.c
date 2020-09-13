#include "math.h"
#include "stdio.h"
#include "rendering.h"

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

void Texture_freeData(Texture *texture_p){
	
	free(texture_p->data);

	texture_p->data = NULL;
	
}
