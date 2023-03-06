#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
typedef struct Barrel {
    int x;
    int y;
    int sense;
    int ligne;
} Barrel;
Barrel init_barrel(int x, int y, int sense, int ligne) {
    struct Barrel new_barrel;
    new_barrel.x = x;
    new_barrel.y = y;
    new_barrel.sense = sense;
    new_barrel.ligne = ligne;
    return new_barrel;}
Barrel gravite(Barrel B){
	if(B.ligne%2==1){
	//printf("%d\n",1000-((ligne*150)-150+x*150/1000));
	B.y= 1000-((B.ligne*150)-150+B.x*150/1000);}
	else{
	//printf("%d\n",1000-((ligne*150-150)+(1000-x)*150/1000));
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
void barrel_position(SDL_Renderer* renderer,Barrel* list){
int i=0;
for(i;i<10;i++){
if(list[i].y!=0){
draw_filled_circle(renderer,list[i].x,list[i].y-10,8);
if(list[i].sense==0){
list[i].x=list[i].x+2;
}
else{
list[i].x=list[i].x-2;
}
list[i]=gravite(list[i]);

}}}


int limiteperso(int ligne,int x){
if(ligne%2==1){
//printf("%d\n",1000-((ligne*150)-150+x*150/1000));
return 1000-((ligne*150)-150+x*150/1000);}
else{
//printf("%d\n",1000-((ligne*150-150)+(1000-x)*150/1000));
return 1000-((ligne*150-150)+(1000-x)*150/1000);}

};
int main(int argc, char *argv[])
{
 	srand(time(NULL));
	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
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

	// creates a surface to load an image into the main memory
	SDL_Surface* surface;

	// please provide a path for your image
	surface = IMG_Load("mario.png");

	// loads image to our graphics hardware memory.
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

	// clears main-memory
	SDL_FreeSurface(surface);

	// let us control our image position
	// so that we can move it with our keyboard.
	SDL_Rect dest;

	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	// adjust height and width of our image box.
	dest.w /= 18;
	dest.h /= 18;

	// sets initial x-position of object
	dest.x = 0;

	// sets initial y-position of object
	dest.y = 1000;
	

	// controls animation loop
	int close = 0;

	// speed of box
	Barrel* list_tonneau = malloc(100 * sizeof(Barrel));
	list_tonneau[0]=init_barrel(1,500,0,6);
	//list_tonneau[1]=init_barrel(1,500,1,5);
	int compteur=1;
	int speed = 200;
	int jump=-10;
	int horizontal=0;
	int vertical=0;
	int ligne=1;
	int senseM=1;
	int aleatoire=0;

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
					if(jump==-10 || jump==-9){
					jump=10;}
					
					break;
					
				default: 
					
					break;
				}
			}
		}
		
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
		printf("%d\n",limiteperso(ligne,dest.x)-dest.h);
		if (dest.x /*+ dest.w*/ > 1000)
			dest.x = 1000 /*- dest.w*/;

		// left boundary
		if (dest.x < 0)
			dest.x = 0;

		// bottom boundary
		if (dest.y + dest.h > limiteperso(ligne,dest.x)+10)		 
			dest.y = limiteperso(ligne,dest.x)- dest.h;

		// upper boundary
		if (dest.y < limiteperso(ligne,dest.x) && (jump==-9 ||jump==-10))
			dest.y = limiteperso(ligne,dest.x)- dest.h;
			
		
		// clears the screen
		SDL_RenderClear(rend);
		

		// triggers the double buffers
		// for multiple rendering
		// Draw a diagonal line
		
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); // set color to red
		
		SDL_RenderDrawLine(rend, 0, 1000, 1000, 850); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 1000, 850, 0, 700); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 0, 700, 1000, 550); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 1000, 550, 0, 400); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 0, 400, 1000, 250); // draw a line from top-left to bottom-right
		SDL_RenderDrawLine(rend, 1000, 250, 0, 100);
		SDL_RenderDrawLine(rend, 1000, 100, 0, 100);
		SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
		aleatoire = rand() % 100 + 1;
		if(aleatoire==100){
		list_tonneau[compteur]=init_barrel(1,500,0,6);
		if(compteur!=9){
		compteur++;}
		else{
		compteur=0;}}
		barrel_position(rend,list_tonneau);
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		if(senseM==2){
		SDL_RenderCopy(rend, tex, NULL, &dest);}
		if(senseM==1){
		SDL_RenderCopyEx(rend, tex, NULL, &dest,0,NULL,SDL_FLIP_HORIZONTAL);}
		

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


