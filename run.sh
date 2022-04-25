
tcc generator/generate.c -o generator/generate && ./generator/generate

gcc lib/*/*.c *.c -msse2 -mfpmath=sse -g -I ./include/ -ldl -lm -lGL -lX11 -lasound -lpthread -o main && ./main

