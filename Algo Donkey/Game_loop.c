bool quit = false;
SDL_Event event;
while (!quit) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        // Handle other events
    }
    // Update game state
    // Render game
}
