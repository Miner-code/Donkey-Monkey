#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include "music.h"
#include "sauvegarde.h"
#include "loading.h"
typedef struct Barrel {
    int x;
    int y;
    int sense;
    int ligne;
    int statusscore;
} Barrel;

Barrel init_barrel(int x, int y, int sense, int ligne) {
    struct Barrel new_barrel;
    new_barrel.x = x;
    new_barrel.y = y;
    new_barrel.sense = sense;
    new_barrel.ligne = ligne;
    new_barrel.statusscore =0;
    return new_barrel;}
Barrel gravite(Barrel B){
	if(B.ligne%2==1){
	
	B.y= 1000-((B.ligne*150)-150+B.x*150/1000);}
	else{
	
	B.y= 1000-((B.ligne*150-150)+(1000-B.x)*150/1000);}
	if(B.x<0){
		B.sense=0;
		B.ligne--;}
	if(B.x>1000){
		B.sense=1;
		B.ligne--;}
	
	return B;}
void draw_filled_circle(SDL_Renderer* renderer, int x, int y, int radius) {
    int x0 = 0;
    int y0 = radius;
    int d = 1 - radius;
    int delta_e = 3;
    int delta_se = -2 * radius + 5;

    while (y0 >= x0) {
        SDL_RenderDrawLine(renderer, x - x0, y - y0, x + x0, y - y0);
        SDL_RenderDrawLine(renderer, x - x0, y + y0, x + x0, y + y0);
        SDL_RenderDrawLine(renderer, x - y0, y - x0, x + y0, y - x0);
        SDL_RenderDrawLine(renderer, x - y0, y + x0, x + y0, y + x0);
        
        if (d < 0) {
            d += delta_e;
            delta_e += 2;
            delta_se += 2;
        } else {
            d += delta_se;
            delta_e += 2;
            delta_se += 4;
            y0--;
        }
        x0++;
    }
}
int barrel_position(SDL_Renderer* renderer,Barrel* list,int x,int y,int diff,int* score,int d,int vitesse){
int i=0;
int g=0;
for(i;i<100+diff*5;i++){
if(list[i].y>0 && list[i].y<1000 ){
draw_filled_circle(renderer,list[i].x,list[i].y-10,8);
if(((x+35-list[i].x)*(x+35-list[i].x) + (y-list[i].y+40)*(y-list[i].y+40)) <= 2000 || ((x+40-list[i].x)*(x+40-list[i].x) + (y-list[i].y+40)*(y-list[i].y+40)) <= 2000)
{
	
    g = 1;
}
if(list[i].sense==0){
list[i].x=list[i].x+5+vitesse/5+d/3;
}
else{
list[i].x=list[i].x-5-vitesse/5-d/3;
}
list[i]=gravite(list[i]);

}
if(list[i].y>y && list[i].statusscore==0){
list[i].statusscore=1;
*score+=200 +100*d;
}}
return g;}


int limiteperso(int ligne,int x){
if(ligne%2==1){

return 1000-((ligne*150)-150+x*150/1000);}
else{

return 1000-((ligne*150-150)+(1000-x)*150/1000);}

};
int main(int argc, char *argv[])
{
	int diff=-1;
	while(diff<0 || diff>99){;
	printf("choix de la difficluté : ");
	scanf("%d",&diff);
	printf("\n");}
	loadinggame(1);
 	srand(time(NULL));
	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	// Initialize TTFz
    if (TTF_Init() < 0) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }

	SDL_Window* win = SDL_CreateWindow("Donkey_kong", // creates a window
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									1000, 1000, 0);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

	Mix_Music *music = LoadMusic("Musique/musique.mp3", 20);
	
	// creates a surface to load an image into the main memory
	SDL_Surface* surface;
	SDL_Surface* surfaces;

	// please provide a path for your image
	surface = IMG_Load("mario.png");
	surfaces = IMG_Load("kong.png");
	int a[11];
	
	
	TTF_Font* font = TTF_OpenFont("arial.ttf", 500);
    if (font == NULL) {
        printf("Font could not be loaded! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }

	// loads image to our graphics hardware memory.
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_Texture* text = SDL_CreateTextureFromSurface(rend, surfaces);

	// clears main-memory
	SDL_FreeSurface(surface);
	SDL_FreeSurface(surfaces);

	// let us control our image position
	// so that we can move it with our keyboard.
	SDL_Rect dest;
	SDL_Rect destk;

	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
	SDL_QueryTexture(tex, NULL, NULL, &destk.w, &destk.h);

	// adjust height and width of our image box.
	dest.w /= 18;
	dest.h /= 18;
	destk.w /= 14;
	destk.h /= 14;
	

	// sets initial x-position of object
	dest.x = 900;
	destk.x = 100;

	// sets initial y-position of object
	dest.y = 1000;
	destk.y = 20;
	

	// controls animation loop
	int close = 0;
	 

	// speed of box
	Barrel* list_tonneau = malloc(((100+diff*5) * sizeof(Barrel)));
	for(int z=0;z<(100+diff*5);z++){
	list_tonneau[z]=init_barrel(0,0,0,0);}
	list_tonneau[0]=init_barrel(1,500,0,6);
	char buffer[20];
	int compteur=1;
	int rota=3;
	int speed = 200;
	int jump=-10;
	int horizontal=0;
	int vertical=0;
	int etatctrl = 0;
	int ligne=1;
	int senseM=1;
	int aleatoire=0;
	int timeur=200;
	int game=-1;
	int x, y;
	int vitesse=0;
	int score=0;
	int debug=0;
	Mix_PlayMusic(music, -1);
	affichageMenu(rend);
	SDL_Rect rect = { 850, 100, surface->w, surface->h };
	SDL_Color colori = {255, 255, 255};
	SDL_Rect recscore ={850,1000,100};
	
	SDL_RenderPresent(rend);
	
	// animation loop
	
	while (!close) {
		
		SDL_Event event;
		
		
			

		// Events management
		while (SDL_PollEvent(&event)) {
			
			switch (event.type) {

			case SDL_QUIT:
				// handling of close button
				close = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
					if(game==-1){
				      	SDL_GetMouseState(&x, &y);
				      	
				      	//Création des zone de clique
				      	
					if (x >= 300 && x <= 700 && y >= 400 && y <= 500) {
							game=0;
						    }
					if (x >= 300 && x <= 700 && y >= 550 && y <= 650) {
							game=-6;
						    }
					if (x >= 300 && x <= 700 && y >= 700 && y <= 800) {
							close = 1;
						    }
					if (x >= 50 && x <= 150 && y >= 750 && y <= 800) {
							if(etatctrl == 0)
								etatctrl = 1;
							else
								etatctrl = 0;
						    }
				    }
				    break;

			case SDL_KEYDOWN:
				// keyboard API for key pressed
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					
					
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					horizontal = -speed / 30;
					senseM=1;
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					horizontal=0;
					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
				
					horizontal=speed/30;
					senseM=2;
					break;
				case SDL_SCANCODE_SPACE:
					if(game==0){
					if(jump==-10 || jump==-9){
					jump=10;}}
					if(game==-3){
					// sets initial x-position of object
					dest.x = 900;

					// sets initial y-position of object
					dest.y = 1000;
					
					for(int z=0;z<(100+diff*5);z++){
					list_tonneau[z]=init_barrel(0,0,0,0);}
					list_tonneau[0]=init_barrel(1,500,0,6);
					timeur=200;
					compteur=1;
					horizontal=0;
					game=-0;}
					if(game==-5){
					// sets initial x-position of object
					dest.x = 900;
					horizontal=0;
					// sets initial y-position of object
					dest.y = 1000;
					for(int z=0;z<(100+diff*5);z++){
					SDL_RenderClear(rend);
					list_tonneau[z]=init_barrel(0,0,0,0);}
					list_tonneau[0]=init_barrel(1,500,0,6);
					affichageMenu(rend);
					score=0;
					timeur=200;
					compteur=1;
					game=-1;}
					if(game==-7){
					game=-1;
					SDL_RenderClear(rend);
					SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		
					affichageMenu(rend);}
					
					break; 
				
					
				default: 
					
					break;
				}
			}
		}
		if(game==-1){
		
		
		affichectrl(rend, etatctrl);}
		
		
		if(jump>-9){
				jump--;
				dest.y=dest.y-jump;
				}
		if(horizontal!=0){
		dest.x += horizontal;
		}
		if(dest.y +dest.h > 100){
			ligne=6;}
		if(dest.y + dest.h > 250){
			ligne=5;}
		if(dest.y+dest.h  > 400){
			ligne=4;}
		if(dest.y + dest.h > 550){
			ligne=3;}
		if(dest.y+dest.h > 700){
			ligne=2;}
		if(dest.y + dest.h > 850){
			ligne=1;}	
		// right boundary
		if (dest.x /*+ dest.w*/ > 1000)
			dest.x = 1000 /*- dest.w*/;

		// left boundary
		if (dest.x < 0)
			dest.x = 0;
		if(game==0){
		// bottom boundary
		if (dest.y + dest.h > limiteperso(ligne,dest.x)+10)		 
			dest.y = limiteperso(ligne,dest.x)- dest.h;

		// upper boundary
		if (dest.y < limiteperso(ligne,dest.x) && (jump==-9 ||jump==-10))
			dest.y = limiteperso(ligne,dest.x)- dest.h;}
		
			
			
		
		// clears the screen
		
		if(game>-1 ){SDL_RenderClear(rend);}
		

		// triggers the double buffers
		// for multiple rendering
		// Draw a diagonal line
		if(game==0|| game==1){
		if(game==1){
		SDL_SetRenderDrawColor(rend, 128, 0, 128, 255);
		}
		
		
		else{
		
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);} // set color to red
		for(int j=0;j<3;j++){
		SDL_RenderDrawLine(rend, 0, 1000+j, 1000, 850+j); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 1000, 850+j, 0, 700+j); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 0, 700+j, 1000, 550+j); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 1000, 550+j, 0, 400+j); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 0, 400+j, 1000, 250+j); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 1000, 250+j, 0, 100+j);
		SDL_RenderDrawLine(rend, 1000, 100+j, 0, 100+j);}
		SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
		
		
		aleatoire = rand() % 100 + 1;
		
		if(game==0){
		game=barrel_position(rend,list_tonneau,dest.x,dest.y,diff,&score,diff,vitesse);
		}
		else{
		dest.y=dest.y+4;
		if(barrel_position(rend,list_tonneau,dest.x,dest.y,diff,&debug,diff,vitesse)){
		jump=14;
		}}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		if(timeur<0){
		
		if(aleatoire>90-diff){
		timeur=200-diff*2;
		vitesse++;
		
		list_tonneau[compteur]=init_barrel(1,500,0,6);
		if(compteur!=99+diff*5){
		compteur++;}
		else{
		compteur=0;}}
		}
		else{timeur--;}
		if(game==0){
		if(senseM==2){
		SDL_RenderCopy(rend, tex, NULL, &dest);
		SDL_RenderCopy(rend, text, NULL, &destk);}
		if(senseM==1){
		SDL_RenderCopyEx(rend, tex, NULL, &dest,0,NULL,SDL_FLIP_HORIZONTAL);
		SDL_RenderCopy(rend, text, NULL, &destk);}}
		if(game==1){
		
		
		SDL_RenderCopyEx(rend, tex, NULL, &dest,rota,NULL,SDL_FLIP_NONE);
		rota+=14+diff*2;}
		if(dest.y>950 ){
		game=-2;}
		}
		if(dest.y<50 && game==0){
		replace(score);	
		game=-4;}
		if(game==-2){
		
		replace(score/3);	
		ecranGO(rend,score/3);
		score=0;
		game=-3;
		}
		if(game==-4){
		
		
		ecranWIN(rend,score);
		
		game=-5;}
		if(game==-6){
		ecranscore(rend);
		game=-7;}
		
		
		
	
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(1000 / 80);
	}
	
	// destroy texture
	SDL_DestroyTexture(tex);

	// destroy renderer
	SDL_DestroyRenderer(rend);

	// destroy window
	SDL_DestroyWindow(win);
	
	// close SDL
	SDL_Quit();

	return 0;
}


