// Create game window
SDL_Window* window = SDL_CreateWindow("Donkey Kong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
if (window == NULL) {
    // Handle error
}
// Get window surface
SDL_Surface* surface = SDL_GetWindowSurface(window);
// Fill surface with color
SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
// Update the window surface
SDL_UpdateWindowSurface(window);
