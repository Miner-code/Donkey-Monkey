#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define MAX_NUMS 10

void drawRectangle(SDL_Renderer* renderer, int x, int y, int w, int h)
{
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    
}

int writeSmt(SDL_Renderer* renderer, int x, int y, int w, int h, const char * mot, SDL_Color color){
	
	TTF_Font* font = TTF_OpenFont("arial.ttf", 500);
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
	drawRectangle(renderer, 50, 750, 100, 50);
	
	SDL_Color color = { 255, 255, 255, 255 };
	writeSmt(renderer, 500, 450, 275, 40, "Commencer une partie", color);
	writeSmt(renderer, 500, 600, 300, 40, "Liste highscore", color);
	writeSmt(renderer, 500, 750, 150, 40, "Quitter", color);
	writeSmt(renderer, 100, 775, 50, 20, "Ctrl", color);
	
	SDL_Color color2 = { 235, 0, 0, 255 };
	writeSmt(renderer, 500, 250, 450, 75, "Donkey Kong", color2);
	
}

void affichectrl(SDL_Renderer* renderer, int var){
	if(var == 0){
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		drawRectangle(renderer, 50, 500, 200, 225);
	} 
	else {
		SDL_SetRenderDrawColor(renderer, 153, 81, 43, 255);
		drawRectangle(renderer, 50, 500, 200, 225);
		SDL_Color colorctrl = { 235, 255, 255, 255 };
		writeSmt(renderer, 150, 525, 125, 30, "Deplacement :", colorctrl);
		writeSmt(renderer, 150, 575, 175, 30, "Fleche directionnelle", colorctrl);
		writeSmt(renderer, 150, 625, 125, 30, "Saut : Espace", colorctrl);
		
	}
	
}

void AfficheScore(SDL_Renderer* renderer, int score){
	TTF_Font* font = TTF_OpenFont("arial.ttf", 20);
	if (!font) {
   		printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
    		exit(1);
	}
	char texte[100];
	sprintf(texte, "Score : %d", score);
	SDL_Color couleur = { 255, 255, 255, 255 };
	
	SDL_Surface* texteSurface = TTF_RenderText_Solid(font, texte, couleur);
	if (!texteSurface) {
   		printf("Erreur lors du rendu du texte : %s\n", TTF_GetError());
    		exit(1);
	}
	
	SDL_Texture* texteTexture = SDL_CreateTextureFromSurface(renderer, texteSurface);
    	if (!texteTexture) {
        	printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        	exit(1);
    	}
	
	SDL_Rect destination = { 850, 50, texteSurface->w, texteSurface->h };
    	SDL_RenderCopy(renderer, texteTexture, NULL, &destination);
}
void ecranGO(SDL_Renderer* renderer,int score){
	char* buffer=malloc(sizeof(char)*20);
	 sprintf(buffer, "score:%d", score);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
        SDL_Color colorGO = { 235, 0, 0, 255 };
        writeSmt(renderer, 500, 400, 300, 100, "Game Over", colorGO);
        SDL_Color colorGO2 = { 255, 255, 255, 255 };
        writeSmt(renderer, 500, 500, 500, 50, "Appuyer sur espace pour relancer", colorGO2);
        writeSmt(renderer, 500, 600, 500, 50, buffer, colorGO2);


}
void ecranWIN(SDL_Renderer* renderer,int score){
	char* buffer=malloc(sizeof(char)*20);
	 sprintf(buffer, "score:%d", score);
    SDL_SetRenderDrawColor(renderer, 244, 102, 27, 255);
  SDL_RenderClear(renderer);
        SDL_Color colorWIN = { 235, 200, 0, 255 };
        writeSmt(renderer, 500, 400, 350, 100, "Niveau reussi", colorWIN);
        SDL_Color colorWIN2 = { 255, 255, 255, 255 };
        writeSmt(renderer, 500, 500, 600, 50, "Appuyer sur espace pour retourner au menu", colorWIN2);
        writeSmt(renderer, 500, 600, 500, 50, buffer, colorWIN2);


}
void ecranscore(SDL_Renderer* renderer){ 
	char* buffer=malloc(sizeof(char)*20);
	 
    SDL_SetRenderDrawColor(renderer, 132, 46, 27, 255);
  SDL_RenderClear(renderer);
        SDL_Color colorWIN = { 235, 200, 0, 255 };
        writeSmt(renderer, 500, 200, 350, 100, "Tableau highscore", colorWIN);
        SDL_Color colorWIN2 = { 255, 255, 255, 255 };
         int nums[MAX_NUMS + 1];  // Add an extra slot for the new number
    int num_count = 0;

    FILE *fp = fopen("integers.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file integers.txt\n");
        
    }

    // Read in the existing numbers from the file
    while (fscanf(fp, "%d", &nums[num_count]) == 1) {
        num_count++;
        if (num_count > MAX_NUMS) {
            break;
        }
    }
    fclose(fp);
    

    for (int i = 0; i < num_count; i++) {
        sprintf(buffer, "score:%d", nums[i]);
        if(nums[i]>0){
        writeSmt(renderer, 500, 300+50*i, 800, 75,buffer, colorWIN2);
        }
    }

        writeSmt(renderer, 500, 800, 800, 50, "Appuyer sur espace pour retourner au menu", colorWIN2);
        


}




