#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MARIO_WIDTH 32
#define MARIO_HEIGHT 32
#define BAR_WIDTH 400
#define BAR_HEIGHT 30
#define BAR_X (SCREEN_WIDTH - BAR_WIDTH) / 2
#define BAR_Y (SCREEN_HEIGHT - BAR_HEIGHT) / 2

// Define Mario struct
typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
    int xvel;
} Mario;

// Load Mario sprite
Mario loadMario(SDL_Renderer* renderer) {
    SDL_Rect barRect;
    barRect.x = BAR_X;
    barRect.y = BAR_Y;
    barRect.w = BAR_WIDTH;
    barRect.h = BAR_HEIGHT;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &barRect);
    Mario mario;
    SDL_Surface* surface = SDL_LoadBMP("mario.png");
    mario.texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    mario.rect.x = 0;
    mario.rect.y = SCREEN_HEIGHT - MARIO_HEIGHT;
    mario.rect.w = MARIO_WIDTH;
    mario.rect.h = MARIO_HEIGHT;
    mario.xvel = 3;
    return mario;
}

int loadinggame(int argc) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface = NULL;
    SDL_Rect barRect;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create window and renderer
    window = SDL_CreateWindow("Loading Bar",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL || renderer == NULL) {
        printf("Window or renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create surface
    surface = SDL_GetWindowSurface(window);

    // Set color of surface to white
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
    SDL_RenderClear(renderer);

    // Draw loading bar background
    barRect.x = BAR_X;
    barRect.y = BAR_Y;
    barRect.w = BAR_WIDTH;
    barRect.h = BAR_HEIGHT;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &barRect);

    // Load Mario sprite
    Mario mario = loadMario(renderer);

    // Draw loading progress and Mario animation
    bool loadingComplete = false;
    while (!loadingComplete) {
        // Draw loading progress
        for (int i = 0; i <= BAR_WIDTH; i++) {
            barRect.x = BAR_X;
            barRect.y = BAR_Y;
            barRect.w = i;
            barRect.h = BAR_HEIGHT;
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &barRect);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            // Check if loading is complete
            if (i == BAR_WIDTH) {
                loadingComplete = true;
                break;
            }
        }

        // Animate Mario
        mario.rect.x += mario.xvel;
        if (mario.rect.x > SCREEN_WIDTH) {
            (mario.rect.x = 0 - MARIO_WIDTH);
}
    // Clear the screen and draw Mario
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, mario.texture, NULL, &mario.rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}

// Cleanup
SDL_DestroyTexture(mario.texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
}
