#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Rect platform1 = { 0, SCREEN_HEIGHT - 50, 100, 50 };
    SDL_Rect platform2 = { 150, SCREEN_HEIGHT - 100, 100, 50 };
    SDL_Rect platform3 = { 300, SCREEN_HEIGHT - 150, 100, 50 };

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Donkey Kong Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

    SDL_FillRect(screenSurface, &platform1, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    SDL_FillRect(screenSurface, &platform2, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    SDL_FillRect(screenSurface, &platform3, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

    SDL_UpdateWindowSurface(window);
    SDL_SaveBMP(screenSurface, "map.bmp");

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
