sprite: sprite.o music.o menu.o
	gcc -o sprite sprite.o music.o menu.o -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
sprite.o: sprite.c
	gcc -c sprite.c -lSDL2 -lSDL2_image -lSDL2_mixer
music.o: music.c
	gcc -c music.c -lSDL2 -lSDL2_image -lSDL2_mixer
menu.o: menu.c
	gcc -c menu.c -lSDL2 -lSDL2_image -lSDL2_ttf
