#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>

//Load the music and set the volume
Mix_Music *LoadMusic(char * path, int volume)
{
	Mix_Music *music = Mix_LoadMUS(path);
	if (music == NULL)
	{
		printf("Failed to load music %s\n", path);
		return NULL;
	}
	Mix_VolumeMusic(volume);
	return music;
}