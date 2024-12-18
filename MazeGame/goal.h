#ifndef GOAL_H
#define GOAL_H

#include "raylib.h"
#include "config.h"
#include "types.h"

class Goal
{
private:
    Position position;  // Position of the goal in grid coordinates
    Texture2D texture;  // Texture of the goal
    bool textureLoaded; // Flag to track if texture is loaded

public:
    // Default constructor
    Goal();

    // Parameterized constructor
    Goal(int x, int y);

    // Destructor
    ~Goal();
    void SetTexture(const Texture2D &tex)
    {
        texture = tex;
        textureLoaded = true;
    }
    // Load the texture
    void LoadTexture(const char *filePath);

    // Unload the texture
    void UnloadTexture();

    // Set the position of the goal
    void SetPosition(int x, int y);

    // Get the position of the goal
    Position GetPosition() const;

    // Draw the goal
    void Draw(int difficulty, float offsetX, float offsetY);
};

#endif 
