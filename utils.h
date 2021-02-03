#ifndef UTILS_H_
#define UTILS_H_

typedef struct Array{
	void *items;
	unsigned int length;
	unsigned int maxLength;
	unsigned int itemSize;
}Array;

typedef struct EntityHeader{
	size_t ID;
}EntityHeader;

typedef struct String{
	char *characters;
}String;

void Array_init(Array *, unsigned int);

void Array_free(Array *);

void EntityHeader_init(EntityHeader *);

void *Array_addItem(Array *);

void *Array_getItemPointerByIndex(Array *, unsigned int);

void *Array_getItemPointerByID(Array *, size_t);

unsigned int Array_getItemIndexByID(Array *, size_t);

void Array_removeItemByIndex(Array *, unsigned int);

void Array_removeItemByID(Array *, size_t);

void Array_clear(Array *);

void String_init(String *, char *);

void String_setText(String *, char *);

void String_concatText(String *, char *);

void String_concatString(String *, String);

void String_concatInt(String *, int);

unsigned int String_getLength(String *);

void String_free(String *);

bool compareFloatToFloat(float, float);

#endif
