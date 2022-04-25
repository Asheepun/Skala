cd generator

gcc generate.c -o generate.exe

cd ..

generator\generate.exe

windres skala.rc -O coff -o skala.res

gcc lib/engine/*.c lib/glad/*.c lib/miniaudio/*.c *.c skala.res -msse2 -mfpmath=sse -g -I ./include/ -lopengl32 -lgdi32 -lwinmm -lxinput1_4 -lpthread -o main.exe && main.exe
