OBJS = *.c

CC = gcc
#CC = tcc
#CC = clang
#CC = i686-w64-mingw32-gcc

COMPILER_FLAGS = -ggdb -w

LINKER_FLAGS = -lSDL2 -ldl -lm

OBJ_NAME = main
#OBJ_NAME = main.exe

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
