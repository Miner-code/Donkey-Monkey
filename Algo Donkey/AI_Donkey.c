// Move Donkey Kong
if (donkeyKongRect.x <= 0 || donkeyKongRect.x >= 640) {
// Change direction
}
donkeyKongRect.x += 1;

// Throw barrel
if (rand() % 100 == 0) {
// Create new barrel object
// Set velocity
// Add to game object list
}