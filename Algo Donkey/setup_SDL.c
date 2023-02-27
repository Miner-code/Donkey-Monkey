#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Handle error
    }
    // Create game window
    SDL_Window* window = SDL_CreateWindow("Donkey Kong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        // Handle error
    }
    // Quit SDL
    SDL_Quit();
    return 0;
}
