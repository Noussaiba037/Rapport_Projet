#include "game.h"

int main()
{

    // Initialize the game window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Game");

    // Limit the game to 60 FPS
    SetTargetFPS(60);
    // Disable ESC to close window (this is key)
    SetExitKey(KEY_NULL);
    // Create the game object
    Game mazeGame;

    // Run the main game loop
    mazeGame.Run();

    return 0;
}