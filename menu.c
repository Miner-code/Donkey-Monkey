#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

void drawRectangle(SDL_Renderer* renderer, int x, int y, int w, int h)
{
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    
}

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

    // Render the texture
    SDL_Rect dstRect = { x - w/2, y - h/2, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    
    SDL_DestroyTexture(texture);
}

void affichageMenu(SDL_Renderer* renderer){
	SDL_SetRenderDrawColor(renderer, 153, 81, 43, 255);
	//SDL_SetRenderDrawWidth(renderer, 5); // Set the line width to 5 pixels
	drawRectangle(renderer, 300, 400, 400, 100);
	drawRectangle(renderer, 300, 550, 400, 100);
	drawRectangle(renderer, 300, 700, 400, 100);
	
	SDL_Color color = { 255, 255, 255, 255 };
	writeSmt(renderer, 500, 450, 275, 40, "Commencer une parties", color);
	writeSmt(renderer, 500, 600, 300, 40, "Charger une sauvegarde", color);
	writeSmt(renderer, 500, 750, 150, 40, "Quitter", color);
	
	SDL_Color color2 = { 235, 0, 0, 255 };
	writeSmt(renderer, 500, 250, 450, 75, "Donkey Kong", color2);
	
}

int main(int argc, char* argv[]) {
  // Initialiser SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
    return 1;
  }

  // Créer une fenêtre et un renderer
  SDL_Window* window = SDL_CreateWindow("Menu graphique", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 900, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

 /* // Charger une image et créer une texture avec cette image
  SDL_Surface* image_surface = SDL_LoadBMP("image.bmp");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image_surface);
*/
  // Afficher la texture à l'écran
  //SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_SetRenderDrawColor(renderer, 90, 58, 34, 255); // Set the drawing color to red
  SDL_RenderClear(renderer); // Clear the entire screen with the given color
  SDL_RenderPresent(renderer); // Update the screen


// Initialize TTF
    if (TTF_Init() < 0) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }



  //Fonction afficahge du menu
	affichageMenu(renderer);
	SDL_RenderPresent(renderer);
  // Attendre les événements
  SDL_Event event;
  int quit = 0;
  int x, y;
  while (!quit) {
    SDL_WaitEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          quit = 1;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
      	SDL_GetMouseState(&x, &y);
	if (x >= 300 && x <= 700 && y >= 400 && y <= 500) {
                        printf("Clic dans la zone de clique !\n");
                    }
	if (x >= 300 && x <= 700 && y >= 550 && y <= 650) {
                        printf("Clic 2\n");
                    }
        if (x >= 300 && x <= 700 && y >= 700 && y <= 800) {
                        printf("Clic quitter\n");
                    }
    }
  }

  // Nettoyer la mémoire
  
  //SDL_FreeSurface(image_surface);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
SDL_Quit();

return 0;
}
