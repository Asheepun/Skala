cd generator

gcc generate.c -o generate.exe

cd ..

generator\generate.exe

gcc lib/*/*.c *.c -msse2 -mfpmath=sse -g -I ./include/ -lopengl32 -lgdi32 -o main.exe && main.exe
