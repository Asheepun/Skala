#include "engine/strings.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"

void String_set(char *destString, char *sourceString, int size){

	memset(destString, 0, size);

	memcpy(destString, sourceString, strlen(sourceString));
	
}

void String_append(char *baseString, char *appendString){

	memcpy(baseString + strlen(baseString), appendString, strlen(appendString));

}

void String_append_int(char *baseString, int value){

	char buff[STRING_SIZE];
	memset(buff, 0, STRING_SIZE);
	
	sprintf(buff, "%i", value);

	memcpy(baseString + strlen(baseString), buff, strlen(buff));

}

void String_append_float(char *baseString, float value){

	char buff[STRING_SIZE];
	memset(buff, 0, STRING_SIZE);
	
	sprintf(buff, "%f", value);

	memcpy(baseString + strlen(baseString), buff, strlen(buff));

}

/*
void String_append_formatted(char *baseString, const char *format, ...){

	va_list args;
    va_start(args, format);

	char buff[STRING_SIZE];
	memset(buff, 0, STRING_SIZE);

	sprintf(buff, format, args);

	printf(format, args);

	memcpy(baseString + strlen(baseString), buff, strlen(buff));

    va_end(args);

}
*/

void String_clearRange(char *string, int startIndex, int stopIndex){

	memset(string + startIndex, 0, stopIndex - startIndex);

}
