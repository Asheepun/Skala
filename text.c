#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "geometry.h"
#include "rendering.h"
#include "text.h"

Font getFont(char *fontPath, int fontSize){

	Font font;

	font.size = fontSize;

	long fileSize;
	unsigned char *fontBuffer;

	FILE *fontFile = NULL;

	fontFile = fopen(fontPath, "rb");

	if(fontFile == NULL){
		printf("!!********************!!\n");
		printf("Could not load file: %s\n", fontPath);
		printf("!!********************!!\n");
	}

	fseek(fontFile, 0, SEEK_END);
	fileSize = ftell(fontFile);
	fseek(fontFile, 0, SEEK_SET);

	fontBuffer = malloc(fileSize);

	fread(fontBuffer, fileSize, 1, fontFile);

	fclose(fontFile);

	if(!stbtt_InitFont(&font.info, fontBuffer, 0)){
		printf("!!********************!!\n");
		printf("Could not init font: %s\n", fontPath);
		printf("!!********************!!\n");
	}

	stbtt_GetFontVMetrics(&font.info, &font.ascent, &font.descent, &font.lineGap);

	font.scale = stbtt_ScaleForPixelHeight(&font.info, font.size);

	font.ascent = roundf(font.ascent * font.scale);
	font.descent = roundf(font.descent * font.scale);
	font.lineGap = roundf(font.lineGap * font.scale);

	for(int character = 0; character < 255; character++){

		Glyph *glyph = &font.glyphs[character];

		stbtt_GetCodepointHMetrics(&font.info, character, &glyph->width, &glyph->leastSignificantBit);

		//glyph->height = roundf(fontSize * font.scale);
		//glyph->width = roundf(glyph->width * font.scale);

		stbtt_GetCodepointBitmapBox(
			&font.info,
			character,
			font.scale,
			font.scale,
			&glyph->west,
			&glyph->north,
			&glyph->east,
			&glyph->south
		);

		int hej = stbtt_GetCodepointKernAdvance(&font.info, "a", "b");

	}

	//free(fontBuffer);

	return font;
	
}

Texture getTextureFromFontAndString_mustFree(Font font, char *string){

	Texture texture;

	unsigned char *bitmap;
	texture.width = 0;
	texture.height = font.size;

	for(int i = 0; i < strlen(string); i++){

		texture.width += roundf(font.glyphs[string[i]].width * font.scale);

		int kern;
		kern = stbtt_GetCodepointKernAdvance(&font.info, string[i], string[i + 1]);

		texture.width += roundf(kern * font.scale);
	
	}

	bitmap = calloc(texture.width * texture.height, sizeof(unsigned char));

	int x = 0;
	for(int i = 0; i < strlen(string); i++){

		Glyph glyph = font.glyphs[string[i]];
		
		int y = font.ascent + glyph.north;

		int byteOffset = x + roundf(glyph.leastSignificantBit * font.scale) + (y * texture.width);

		stbtt_MakeCodepointBitmap(
			&font.info,
			bitmap + byteOffset,
			glyph.east - glyph.west,
			glyph.south - glyph.north,
			texture.width,
			font.scale,
			font.scale,
			string[i]
		);

		x += roundf(glyph.width * font.scale);

		int kern;
		kern = stbtt_GetCodepointKernAdvance(&font.info, string[i], string[i + 1]);

		x += roundf(kern * font.scale);

	}

	texture.data = malloc(texture.width * texture.width * 4 * sizeof(unsigned char));

	for(int i = 0; i < texture.width * texture.height; i++){
		if(bitmap[i] == 0){
			texture.data[i * 4 + 0] = 0;
			texture.data[i * 4 + 1] = 0;
			texture.data[i * 4 + 2] = 0;
			texture.data[i * 4 + 3] = 0;
		}else{
			texture.data[i * 4 + 0] = 255;
			texture.data[i * 4 + 1] = 255;
			texture.data[i * 4 + 2] = 255;
			texture.data[i * 4 + 3] = 255;
		}
	}

	free(bitmap);

	return texture;

}
