cd generator

gcc generate.c -o generate.exe

cd ..

generator\generate.exe

gcc lib/engine/*.c lib/glad/*.c lib/miniaudio/*.c *.c -msse2 -mfpmath=sse -g -I ./include/ -lopengl32 -lgdi32 -lwinmm -lxinput -o main.exe && main.exe
