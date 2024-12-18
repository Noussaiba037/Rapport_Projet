#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "maze.h"
#include "theme.h"
#include "menu.h"
#include "scoreboard.h"
#include "goal.h"

// Game state management
enum GameState
{
    MAIN_MENU,
    DIFFICULTY_MENU,
    GAME_PLAY,
    PAUSE_MENU,
    GAMEOVER_MENU
};

class Game
{
private:
    GameState currentState;
    Theme currentTheme;
    Player player;
    Goal goal;
    Maze maze;
    
    int difficulty;
    bool gameWon;
    bool timerStarted; // Flag to track if the timer has started
    float gameTime; // This variable keeps track of the game time
    float winTimer;
    bool exitRequested; // Flag to indicate when the game should exit

public:
    Game();
    ~Game();
    void Run();                     // Main game loop
    void StartGame(int difficulty); // Initializes the game based on difficulty

    // State-specific functions
    void MainMenu();
    void DifficultyMenu();
    void GamePlay();
    void PauseMenu();
    void GameOverMenu();
};

#endif
