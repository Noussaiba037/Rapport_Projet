#include "scoreboard.h"
#include <cstdio>
#include "config.h"

float Scoreboard::bestTimes[3][5] = {
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Easy
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Medium
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}  // Hard
};

void Scoreboard::SaveBestScores()
{
    FILE *file = fopen("scoreboard.txt", "w");
    if (file)
    {
        // Loop over difficulty levels
        for (int i = 0; i < 3; i++) 
        {
            // Loop over the top 5 scores
            for (int j = 0; j < 5; j++)
            {
                fprintf(file, "%.2f\n", bestTimes[i][j]);
            }
        }
        fclose(file);
    }
    else
    {
        printf("Error: Could not open scoreboard.txt for writing");
    }
}

void Scoreboard::LoadBestScores()
{
    FILE *file = fopen("scoreboard.txt", "r");
    if (file)
    {
        // Loop over difficulty levels
        for (int i = 0; i < 3; i++)
        {
            // Loop over the top 5 scores
            for (int j = 0; j < 5; j++)
            {
                fscanf(file, "%f\n", &bestTimes[i][j]);
            }
        }
        fclose(file);
    }
    else
    {
        printf("Error: Could not open scoreboard.txt for reading\n");
    }
}

void Scoreboard::UpdateBestScores(int difficulty, float time)
{
    if (difficulty < 0 || difficulty > 2) // Check for valid difficulty level
    {
        printf("Error: Invalid difficulty level %d\n", difficulty);
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        if (time < bestTimes[difficulty][i] || bestTimes[difficulty][i] == 0) // If the new time is better
        {
            // Shift down all scores after this position
            for (int j = 4; j > i; j--)
            {
                bestTimes[difficulty][j] = bestTimes[difficulty][j - 1];
            }
            // Insert the new time at the correct position
            bestTimes[difficulty][i] = time;
            break;
        }
    }
}
