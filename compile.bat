cd generator

gcc generate.c -o generate.exe

cd ..

generator\generate.exe

gcc *.c miniglut\miniglut.c -lopengl32 -lgdi32 -lwinmm -lm -g -o scale.exe
