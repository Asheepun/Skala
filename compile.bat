cd generator

gcc generate.c -o generate.exe

cd ..

generator\generate.exe

gcc *.c miniglut\miniglut.c -lopengll32 -lgdi32 -lwinm -lm -g -o scale.exe
