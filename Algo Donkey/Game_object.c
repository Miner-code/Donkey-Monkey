// Player
SDL_Rect playerRect = {0, 0, 32, 32};
SDL_Surface* playerSurface = SDL_LoadBMP("player.bmp");
if (playerSurface == NULL) {
    // Handle error
}
SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
if (playerTexture == NULL) {
    // Handle error
}
SDL_FreeSurface(playerSurface);

// Donkey Kong
SDL_Rect donkeyKongRect = {200, 0, 64, 64};
SDL_Surface* donkeyKongSurface = SDL_LoadBMP("donkeykong.bmp");
if (donkeyKongSurface == NULL) {
    // Handle error
}
SDL_Texture* donkeyKongTexture = SDL_CreateTextureFromSurface(renderer, donkeyKongSurface);
if (donkeyKongTexture == NULL) {
    // Handle error
}
SDL_FreeSurface(donkeyKongSurface);
