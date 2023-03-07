sprite: sprite.o music.o menu.o sauvegarde.o loading.o
	gcc -o sprite sprite.o music.o menu.o sauvegarde.o loading.o -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
sprite.o: sprite.c
	gcc -c sprite.c -lSDL2 -lSDL2_image -lSDL2_mixer
music.o: music.c
	gcc -c music.c -lSDL2 -lSDL2_image -lSDL2_mixer
menu.o: menu.c
	gcc -c menu.c -lSDL2 -lSDL2_image -lSDL2_ttf
sauvegarde.o:sauvegarde.c
	gcc -c sauvegarde.c
loading.o:loading.c
	gcc -c loading.c -lSDL2 -lSDL2_image
