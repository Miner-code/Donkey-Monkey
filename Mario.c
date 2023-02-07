#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool climbing = false;
int x = 0;
int y = SCREEN_HEIGHT / 2;

void moveMario(int xVelocity, int yVelocity) {
    x += xVelocity;
    y += yVelocity;
    printf("Mario is moving\n");
}

void jumpMario() {
    if (!climbing) {
        y -= 10;
        printf("Mario is jumping\n");
    }
}

void climbMario() {
    if (!climbing) {
        climbing = true;
        y += 10;
        printf("Mario is climbing\n");
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Donkey Kong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* marioSurface = IMG_Load("mario.png");
    SDL_Texture* marioTexture = SDL_CreateTextureFromSurface(renderer, marioSurface);
    SDL_FreeSurface(marioSurface);

    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        moveMario(-5, 0);
                        break;
                    case SDLK_RIGHT:
                        moveMario(5, 0);
                        break;
                    case SDLK_SPACE:
                        if (climbing) {
                            climbing = false;
                        } else {
                            jumpMario();
                        }
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, marioTexture, NULL, &(SDL_Rect){x, y, marioSurface->w, marioSurface->h});
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(marioTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}