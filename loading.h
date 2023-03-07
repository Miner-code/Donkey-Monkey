typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
    int xvel;
} Mario;
Mario loadMario(SDL_Renderer* renderer);
int loadinggame(int argc);
