sprite: sprite.o music.o
	gcc -o sprite sprite.o music.o -lSDL2 -lSDL2_image -lSDL2_mixer
sprite.o: sprite.c
	gcc -c sprite.c -lSDL2 -lSDL2_image -lSDL2_mixer
music: music.o
	gcc -o music music.o -lSDL2 -lSDL2_image -lSDL2_mixer
