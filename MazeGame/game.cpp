#include "game.h"
#include "raylib.h"
#include <algorithm> // For std::min
#include <cstdio>

Game::Game()
    : currentState(MAIN_MENU), difficulty(0), gameTime(0.0f), winTimer(0.0f), gameWon(false), timerStarted(false), exitRequested(false)
{

    // Load best scores
    Scoreboard::LoadBestScores();
}

Game::~Game()
{
    goal.UnloadTexture(); // Unload the goal texture
    player.UnloadTexture();
    Scoreboard::SaveBestScores();
    CloseWindow();
}

void Game::StartGame(int difficulty)
{
    this->difficulty = difficulty;
    currentTheme = GetThemeForLevel(difficulty);

    // Set grid dimensions based on difficulty
    switch (difficulty)
    {
    case 1:
        GRID_WIDTH = 10;
        GRID_HEIGHT = 10;
        break;
    case 2:
        GRID_WIDTH = 20;
        GRID_HEIGHT = 20;
        break;
    case 3:
        GRID_WIDTH = 30;
        GRID_HEIGHT = 30;
        break;
    }

    float widthCellSize = static_cast<float>(SCREEN_WIDTH) / GRID_WIDTH;
    float heightCellSize = static_cast<float>(SCREEN_HEIGHT - 40) / GRID_HEIGHT;
    CELL_SIZE = static_cast<int>(std::min(widthCellSize, heightCellSize));

    // Initialize the maze
    maze.Initialize();
    maze.GenerateDFS(0, 0);

    // Attach the maze reference to the player
    player.AttachMaze(maze);
    player.SetPosition(0, 0); // Initialize the player position

    Texture2D playerTexture = LoadTexture("assets/frame_6.png");
    Texture2D goalTexture = LoadTexture("assets/door.png");

    goal.SetTexture(goalTexture);     // Assign the texture to the goal
    player.SetTexture(playerTexture); // Assign the texture to the player

    // Initialize the goal object with position and texture
    goal.SetPosition(GRID_WIDTH - 1, GRID_HEIGHT - 1);

    // Reset game variables
    gameWon = false;
    gameTime = 0.0f;
    timerStarted = false;
}

void Game::MainMenu()
{
    Menu::MainMenu();
    if (IsKeyPressed(KEY_ENTER))
        currentState = DIFFICULTY_MENU;
    else if (IsKeyPressed(KEY_ESCAPE))
        exitRequested = true; // Signal to exit, but do not call CloseWindow()
}

void Game::DifficultyMenu()
{
    Menu::DifficultyMenu();

    if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1))
        StartGame(1), currentState = GAME_PLAY;
    else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2))
        StartGame(2), currentState = GAME_PLAY;
    else if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3))
        StartGame(3), currentState = GAME_PLAY;
    else if (IsKeyPressed(KEY_B))
        currentState = MAIN_MENU;
}

void Game::GamePlay()
{

    float availableHeight = SCREEN_HEIGHT - 40; // Leave space for HUD
    float offsetX = (SCREEN_WIDTH - GRID_WIDTH * CELL_SIZE) / 2.0f;
    float offsetY = (availableHeight - GRID_HEIGHT * CELL_SIZE) / 2.0f;
    if (gameWon)
    {
        winTimer += GetFrameTime();
        if (winTimer > 0.5f)
        {
            Scoreboard::UpdateBestScores(difficulty - 1, gameTime);
            currentState = GAMEOVER_MENU;
        }
    }
    else
    {
        if (!timerStarted && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) ||
                              IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)))
            timerStarted = true;

        if (timerStarted)
            gameTime += GetFrameTime();

        if (IsKeyDown(KEY_RIGHT))
        {
            player.Move(1, 0); // Move right
        }
        if (IsKeyDown(KEY_LEFT))
        {
            player.Move(-1, 0); // Move left
        }
        if (IsKeyDown(KEY_UP))
        {
            player.Move(0, -1);
        }
        if (IsKeyDown(KEY_DOWN))
        {
            player.Move(0, 1);
        }


        if (player.GetPosition().x == goal.GetPosition().x && player.GetPosition().y == goal.GetPosition().y)
            gameWon = true;

        if (IsKeyPressed(KEY_ESCAPE))
            currentState = PAUSE_MENU;
        
        ClearBackground(currentTheme.background);
        maze.Draw(currentTheme, offsetX, offsetY);
        player.Draw(difficulty, offsetX, offsetY);

        // Drawing the goal

        goal.Draw(difficulty, offsetX, offsetY);

        // Draw HUD (head-up display)
        DrawRectangle(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 40, GRAY);
        char timeText[50];
        sprintf(timeText, "Time: %.2f seconds", gameTime);
        DrawText(timeText, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 30, 20, WHITE);
        
    }
}

void Game::PauseMenu()
{
    Menu::PauseMenu();

    if (IsKeyPressed(KEY_R))
        currentState = GAME_PLAY;
    else if (IsKeyPressed(KEY_B))
        currentState = DIFFICULTY_MENU;
}

void Game::GameOverMenu()
{
    Menu::GameOverMenu(gameTime, difficulty);

    if (IsKeyPressed(KEY_R))
        currentState = DIFFICULTY_MENU;
    else if (IsKeyPressed(KEY_Q))
        exitRequested = true; // Signal to exit the game
}

void Game::Run()
{
    while (!exitRequested && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState)
        {
        case MAIN_MENU:
            MainMenu();
            break;
        case DIFFICULTY_MENU:
            DifficultyMenu();
            break;
        case GAME_PLAY:
            GamePlay();
            break;
        case PAUSE_MENU:
            PauseMenu();
            break;
        case GAMEOVER_MENU:
            GameOverMenu();
            break;
        }

        EndDrawing();
    }
}
