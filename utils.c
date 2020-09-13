#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include "geometry.h"
#include "rendering.h"
#include "stb_truetype.h"
#include "text.h"
#include "utils.h"

static size_t availableID = 0;

void Array_init(Array *array_p,  unsigned int itemSize){

	//array_p->items = malloc(maxLength * itemSize);
	array_p->maxLength = 16;
	array_p->items = malloc(array_p->maxLength * itemSize);
	array_p->itemSize = itemSize;
	array_p->length = 0;

}

void EntityHeader_init(EntityHeader *entityHeader_p){

	entityHeader_p->ID = availableID;
	availableID++;

}

void *Array_addItem(Array *array_p){
	
	array_p->length++;

	if(array_p->length > array_p->maxLength){
		array_p->maxLength += 16;
		array_p->items = realloc(array_p->items, (array_p->maxLength) * array_p->itemSize);
	}

	return Array_getItemPointerByIndex(array_p, array_p->length - 1);

}

void *Array_getItemPointerByIndex(Array *array_p, unsigned int index){

	return (void *)((char *)array_p->items + index * array_p->itemSize);

}

void *Array_getItemPointerByID(Array *array_p, size_t ID){

	for(int i = 0; i < array_p->length; i++){

		void *itemPointer = Array_getItemPointerByIndex(array_p, i);

		if(((EntityHeader *)itemPointer)->ID == ID){
			return itemPointer;
		}

	}

	printf("***\n");
	printf("Array_getItemPointerByID\n");
	printf("COULD NOT FIND ARRAY ITEM WITH ID: %i\n", ID);
	printf("***\n");

	return NULL;

}

unsigned int Array_getItemIndexByID(Array *array_p, size_t ID){

	for(int i = 0; i < array_p->length; i++){

		void *itemPointer = Array_getItemPointerByIndex(array_p, i);

		if(((EntityHeader *)itemPointer)->ID == ID){
			return i;
		}

	}

	printf("***\n");
	printf("Array_getItemIndexByID\n");
	printf("COULD NOT FIND ARRAY ITEM WITH ID: %i\n", ID);
	printf("***\n");

}

void Array_removeItemByIndex(Array *array_p, unsigned int index){

	if(index >= array_p->length){
		printf("***\n");
		printf("TRIED REMOVING ITEM AT AN INDEX BIGGER THAN THE ARRAY LENGTH");
		printf("array pointer: %p\n", array_p);
		printf("index: %i\n", index);
		printf("array length: %i\n", array_p->length);
		printf("***\n");
		return;
	}
	
	memcpy(
		(char *)array_p->items + index * array_p->itemSize,
		(char *)array_p->items + (index + 1) * array_p->itemSize,
		(array_p->length - index) * array_p->itemSize
	);

	array_p->length--;
}

void Array_removeItemByID(Array *array_p, size_t ID){

	unsigned int index = Array_getItemIndexByID(array_p, ID);

	Array_removeItemByIndex(array_p, index);

}

void Array_clear(Array *array_p){

	while(array_p->length > 0){
		Array_removeItemByIndex(array_p, 0);
	}

}
