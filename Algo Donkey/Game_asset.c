// Load image
SDL_Surface* imageSurface = SDL_LoadBMP("image.bmp");
if (imageSurface == NULL) {
    // Handle error
}
// Load sound effect
Mix_Chunk* soundEffect = Mix_LoadWAV("sound.wav");
if (soundEffect == NULL) {
    // Handle error
}
// Load music
Mix_Music* music = Mix_LoadMUS("music.mp3");
if (music == NULL) {
    // Handle error
}
