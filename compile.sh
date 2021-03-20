tcc generator/generate.c -o generator/generate && ./generator/generate

#for headerFile in *.h
#do
	#echo "$headerFile -> ${headerFile}.gcf"
	#gcc -c "$headerFile" -I ./include/ -w -O0 -lSDL2 -lGL -ldl -lm -lpthread -o "${headerFile}.gcf"
#done

gcc *.c -I ./include/ -O0 -L ./lib -lSDL2 -lSDL2_mixer -lGL -ldl -lm -lpthread -o main
