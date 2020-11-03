#ifndef TEXT_H_
#define TEXT_H_

typedef struct Glyph{

	unsigned char *data;

	int width;
	int height;

	int west;
	int east;
	int north;
	int south;

	int leastSignificantBit;

}Glyph;

typedef struct Font{

	Glyph glyphs[255];

	int size;

	stbtt_fontinfo info;

	int ascent;
	int descent;
	int lineGap;

	float scale;

}Font;

Font getFont(char *, int);

Texture getTextureFromFontAndString_mustFree(Font, char *);

#endif