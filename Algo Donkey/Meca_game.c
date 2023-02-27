// Player movement
const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
if (keyboardState[SDL_SCANCODE_LEFT]) {
    playerRect.x -= 5;
}
if (keyboardState[SDL_SCANCODE_RIGHT]) {
    playerRect.x += 5;
}
if (keyboardState[SDL_SCANCODE_UP]) {
    playerRect.y -= 5;
}
if (keyboardState[SDL_SCANCODE_DOWN]) {
playerRect.y += 5;
}

// Collision detection
if (SDL_HasIntersection(&playerRect, &donkeyKongRect)) {
// Handle collision
}

// Gravity
playerRect.y += 1;