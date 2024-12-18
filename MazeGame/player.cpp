#include "player.h"
#include "maze.h"
#include "raylib.h"

Player::Player() : playerPos{0, 0}, maze(nullptr), playerDirection(1), textureLoaded(false) {}

Player::~Player()
{
    if (textureLoaded)
        UnloadTexture();
}

void Player::LoadTexture(const char *filePath)
{
    if (!textureLoaded)
    {
        texture = ::LoadTexture(filePath); // Use the global LoadTexture function
        textureLoaded = true;
    }
}

void Player::UnloadTexture()
{
    if (textureLoaded)
    {
        ::UnloadTexture(texture); // Use the global UnloadTexture function
        textureLoaded = false;
    }
}
void Player::SetPosition(int x, int y)
{
    playerPos.x = x;
    playerPos.y = y;
}

void Player::Draw(int difficulty, float offsetX, float offsetY)
{
    float scaleFactor;

    // Adjust scaling factor based on difficulty
    switch (difficulty)
    {
    case 1:
        scaleFactor = 1.0f;
        break;
    case 2:
        scaleFactor = 0.7f;
        break;
    case 3:
        scaleFactor = 0.45f;
        break;
    default:
        scaleFactor = 1.0f;
        break;
    }

    // Calculate the center of the cell where the player is positioned
    float cellCenterX = offsetX + playerPos.x * CELL_SIZE + CELL_SIZE / 2;
    float cellCenterY = offsetY + playerPos.y * CELL_SIZE + CELL_SIZE / 2;

    // Calculate the player texture's position by centering it within the cell
    float posX = cellCenterX - (texture.width * scaleFactor) / 2.0f;
    float posY = cellCenterY - (texture.height * scaleFactor) / 2.0f;

    // Define source rectangle for the player texture
    Rectangle sourceRect = (playerDirection == 1)
                               ? Rectangle{0, 0, (float)texture.width, (float)texture.height}
                               : Rectangle{(float)texture.width, 0, -(float)texture.width, (float)texture.height};

    // Define destination rectangle for drawing
    Rectangle destRect = {posX, posY, texture.width * scaleFactor, texture.height * scaleFactor};

    // Define origin for rotation (if any, currently unused)
    Vector2 origin = {0.0f, 0.0f};


    // Draw the player texture
    DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
}

void Player::AttachMaze(Maze &mazeRef)
{
    maze = &mazeRef; // Store the reference to the maze
}

void Player::Move(int dx, int dy)
{
    // Get the current time
    float currentTime = GetTime();

    // Check if enough time has passed since the last move
    if (currentTime - lastMoveTime >= MOVE_DELAY)
    {
        lastMoveTime = currentTime; // Update the last move time

        if (!maze)
            return; // Ensure maze is attached before moving

        int newX = playerPos.x + dx;
        int newY = playerPos.y + dy;

        if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT)
        {
            // Cache maze reference to avoid repeated GetMaze calls
            auto &mazeData = maze->GetMaze();

            auto &currentCell = mazeData[playerPos.x][playerPos.y];

            if (dx == -1 && !currentCell.leftWall)
            {
                playerPos.x = newX;
                playerDirection = -1; // Facing left
            }
            else if (dx == 1 && !currentCell.rightWall)
            {
                playerPos.x = newX;
                playerDirection = 1; // Facing right
            }
            else if (dy == -1 && !currentCell.topWall)
                playerPos.y = newY;
            else if (dy == 1 && !currentCell.bottomWall)
                playerPos.y = newY;
        }
    }
}

Position Player::GetPosition() const
{
    return playerPos;
}
