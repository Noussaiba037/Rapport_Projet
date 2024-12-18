#ifndef PLAYER_H
#define PLAYER_H

#include "maze.h"
#include "types.h"

#define MOVE_DELAY 0.2f

class Player
{
private:
    Position playerPos;        // Player's current position
    Maze *maze = nullptr;      // Pointer to the Maze object
    float lastMoveTime = 0.0f; // Store the last time player moved
    int playerDirection;       // 1 for right, -1 for left
    Texture2D texture;
    bool textureLoaded;

public:
    Player();
    ~Player();
    void SetTexture(const Texture2D &tex)
    {
        texture = tex;
        textureLoaded = true;
    }

    void SetPosition(int x, int y);
    Position GetPosition() const;

    void LoadTexture(const char *filePath);
    void UnloadTexture();
    void Draw(int difficulty, float offsetX, float offsetY);
    void AttachMaze(Maze &mazeRef);
    void Move(int dx, int dy);
};

#endif // PLAYER_H
