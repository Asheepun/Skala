tcc generator/generate.c -o generator/generate && ./generator/generate

gcc *.c -I ./include/ -ggdb -w -L ./lib/ -lSDL2 -lGL -ldl -lm -lpthread -o main
