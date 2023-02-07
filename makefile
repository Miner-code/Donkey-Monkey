sprite: sprite.o
	gcc -o sprite sprite.o -lSDL2 -lSDL2_image
sprite.o: sprite.c
	gcc -c sprite.c -lSDL2 -lSDL2_image

