#include "menu.h"
#include "raylib.h"
#include "config.h"
#include "scoreboard.h"
#include <iostream>

void Menu::MainMenu()
{
    // Measure string width for default font
    const int titleWidth = MeasureText("MazeGame", 40);
    const int startTextWidth = MeasureText("Press ENTER to start", 20);
    const int quitTextWidth = MeasureText("Press ESC to quit", 20);

    // Centering X positions based on screen width
    int titleX = (SCREEN_WIDTH - titleWidth) / 2;
    int startTextX = (SCREEN_WIDTH - startTextWidth) / 2;
    int quitTextX = (SCREEN_WIDTH - quitTextWidth) / 2;

    // Centering Y positions based on screen height
    int titleY = SCREEN_HEIGHT / 4;
    int startTextY = SCREEN_HEIGHT / 2;
    int quitTextY = SCREEN_HEIGHT / 2 + 30;

    DrawText("Maze Game", titleX, titleY, 40, DARKBLUE);
    DrawText("Press ENTER to start", startTextX, startTextY, 20, DARKGREEN);
    DrawText("Press ESC to quit", quitTextX, quitTextY, 20, RED);
}

void Menu::DifficultyMenu()
{
    const int titleWidth = MeasureText("Choose Difficulty", 30);
    const int easyTextWidth = MeasureText("1: Easy (Small Maze)", 20);
    const int mediumTextWidth = MeasureText("2: Medium (Medium Maze)", 20);
    const int hardTextWidth = MeasureText("3: Hard (Large Maze)", 20);
    const int backTextWidth = MeasureText("Press B to go back", 20);

    // Centering X positions based on screen width
    int titleX = (SCREEN_WIDTH - titleWidth) / 2;
    int easyTextX = (SCREEN_WIDTH - easyTextWidth) / 2;
    int mediumTextX = (SCREEN_WIDTH - mediumTextWidth) / 2;
    int hardTextX = (SCREEN_WIDTH - hardTextWidth) / 2;
    int backTextX = (SCREEN_WIDTH - backTextWidth) / 2;

    // Centering Y positions based on screen height
    int titleY = SCREEN_HEIGHT / 4;
    int easyTextY = SCREEN_HEIGHT / 2 - 30;
    int mediumTextY = SCREEN_HEIGHT / 2;
    int hardTextY = SCREEN_HEIGHT / 2 + 30;
    int backTextY = SCREEN_HEIGHT / 2 + 60;

    DrawText("Choose Difficulty", titleX, titleY, 30, DARKBLUE);
    DrawText("1: Easy (Small Maze)", easyTextX, easyTextY, 20, DARKGREEN);
    DrawText("2: Medium (Medium Maze)", mediumTextX, mediumTextY, 20, DARKGREEN);
    DrawText("3: Hard (Large Maze)", hardTextX, hardTextY, 20, DARKGREEN);
    DrawText("Press B to go back", backTextX, backTextY, 20, RED);
}

void Menu::GameOverMenu(float timeTaken, int difficulty)
{
    char timeText[50];
    sprintf(timeText, "Time: %.2f seconds", timeTaken);

    // Calculate width of the text for centering
    const int titleWidth = MeasureText("Game Over", 30);
    const int timeTextWidth = MeasureText(timeText, 20);
    const int restartTextWidth = MeasureText("Press R to restart", 20);
    const int quitTextWidth = MeasureText("Press Q to quit", 20);

    // Centering X positions based on screen width
    int titleX = (SCREEN_WIDTH - titleWidth) / 2;
    int timeTextX = (SCREEN_WIDTH - timeTextWidth) / 2;
    int restartTextX = (SCREEN_WIDTH - restartTextWidth) / 2;
    int quitTextX = (SCREEN_WIDTH - quitTextWidth) / 2;

    // Centering Y positions based on screen height
    int titleY = SCREEN_HEIGHT / 4;
    int timeTextY = SCREEN_HEIGHT / 2;
    int restartTextY = SCREEN_HEIGHT / 2 + 30;
    int quitTextY = SCREEN_HEIGHT / 2 + 60;

    // Draw the game over message and the player's time
    DrawText("Game Over", titleX, titleY, 30, DARKBLUE);
    DrawText(timeText, timeTextX, timeTextY, 20, DARKGREEN);
    DrawText("Press R to restart", restartTextX, restartTextY, 20, DARKGREEN);
    DrawText("Press Q to quit", quitTextX, quitTextY, 20, RED);

    // Display the scoreboard for the current difficulty
    const char *difficultyNames[3] = {"Easy", "Medium", "Hard"};
    int currentDifficulty = difficulty - 1; // Adjust difficulty to zero-based index

    // Display header for scoreboard
    char header[50];
    sprintf(header, "Top Scores (%s)", difficultyNames[currentDifficulty]);
    int headerWidth = MeasureText(header, 20);
    int headerX = (SCREEN_WIDTH - headerWidth) / 2;
    int headerY = SCREEN_HEIGHT / 2 + 100;
    DrawText(header, headerX, headerY, 20, DARKBROWN);

    // Draw top 5 scores
    for (int i = 0; i < 5; i++)
    {
        char scoreText[50];
        sprintf(scoreText, "%d. %.2f", i + 1, Scoreboard::bestTimes[currentDifficulty][i]);

        int scoreTextWidth = MeasureText(scoreText, 20);
        int scoreTextX = (SCREEN_WIDTH - scoreTextWidth) / 2;
        int scoreTextY = SCREEN_HEIGHT / 2 + 130 + (i * 30); // Increment Y for each score
        DrawText(scoreText, scoreTextX, scoreTextY, 20, DARKBROWN);
    }
}

void Menu::PauseMenu()
{
    // Measure string width for default font
    const int titleWidth = MeasureText("Game Paused", 40);
    const int resumeTextWidth = MeasureText("Press R to resume", 20);
    const int returnTextWidth = MeasureText("Press B to return to difficulty menu", 20);

    // Centering X positions based on screen width
    int titleX = (SCREEN_WIDTH - titleWidth) / 2;
    int resumeTextX = (SCREEN_WIDTH - resumeTextWidth) / 2;
    int returnTextX = (SCREEN_WIDTH - returnTextWidth) / 2;

    // Centering Y positions based on screen height
    int titleY = SCREEN_HEIGHT / 4;
    int resumeTextY = SCREEN_HEIGHT / 2;
    int returnTextY = SCREEN_HEIGHT / 2 + 30;

    DrawText("Game Paused", titleX, titleY, 30, DARKGRAY);
    DrawText("Press R to resume", resumeTextX, resumeTextY, 20, DARKGRAY);
    DrawText("Press B to return to difficulty menu", returnTextX, returnTextY, 20, DARKGRAY);
}