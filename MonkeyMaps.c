#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* imageSurface = NULL;
    SDL_Event event;
    bool quit = false;

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
    imageSurface = IMG_Load("Map.png");
    if (imageSurface == NULL) {
        printf("Unable to load image! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);
    SDL_UpdateWindowSurface(window);

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_FreeSurface(imageSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
