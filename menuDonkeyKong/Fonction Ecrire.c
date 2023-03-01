//C'est la fonction qui permet d'écrire la chaîne mot au coordoné x et y et de largeur w et de longueur h
//Oublié pas d'implémenter la librairie SDL2_ttf dans le include e le makefile
//Attention a pas oublier de déclarer la variable SDL_Color color = { 255, 255, 255, 255 }; juste au de l'appel de la fonction
int writeSmt(SDL_Renderer* renderer, int x, int y, int w, int h, const char * mot, SDL_Color color){
	
	TTF_Font* font = TTF_OpenFont("arial.ttf", 28);
    if (font == NULL) {
        printf("Font could not be loaded! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }
	// Create a surface from the text
    SDL_Surface* surface = TTF_RenderText_Solid(font, mot, color);
    if (surface == NULL) {
        printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Get the dimensions of the texture
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    // Render the texture to the center of the screen
    SDL_Rect dstRect = { x - w/2, y - h/2, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    
    SDL_DestroyTexture(texture);
}