#include "goal.h"

Goal::Goal() : position{0, 0}, texture{}, textureLoaded(false) {}

Goal::Goal(int x, int y) : position{x, y}, texture{}, textureLoaded(false) {}

Goal::~Goal()
{
    if (textureLoaded)
        UnloadTexture();
}

void Goal::LoadTexture(const char *filePath)
{
    if (!textureLoaded)
    {
        texture = ::LoadTexture(filePath); // Use the global LoadTexture function
        textureLoaded = true;
    }
}

void Goal::UnloadTexture()
{
    if (textureLoaded)
    {
        ::UnloadTexture(texture); // Use the global UnloadTexture function
        textureLoaded = false;
    }
}

void Goal::SetPosition(int x, int y)
{
    position = {x, y};
}

Position Goal::GetPosition() const
{
    return position;
}

void Goal::Draw(int difficulty, float offsetX, float offsetY)
{
    float scaleFactor;

    switch (difficulty)
    {
    case 1:
        scaleFactor = 1.0f;
        break;
    case 2:
        scaleFactor = 0.6f;
        break;
    case 3:
        scaleFactor = 0.4f;
        break;
    default:
        scaleFactor = 1.0f;
        break;
    }

    // Adjust position with offsets
    float posX = offsetX + position.x * CELL_SIZE + (CELL_SIZE - texture.width * scaleFactor) / 2.0f;
    float posY = offsetY + position.y * CELL_SIZE + (CELL_SIZE - texture.height * scaleFactor) / 2.0f;

    Rectangle sourceRect = {0, 0, (float)texture.width, (float)texture.height};
    Rectangle destRect = {posX, posY, texture.width * scaleFactor, texture.height * scaleFactor};

    DrawTexturePro(texture, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
}
