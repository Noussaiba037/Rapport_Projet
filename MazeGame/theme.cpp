#include "theme.h"

Theme GetThemeForLevel(int level)
{
    Theme theme;
    switch (level)
    {
    case 1:                                             // Easy Level
        theme.background = (Color){180, 230, 255, 150}; //{176, 196, 222, 255}; // Light Steel Blue
        theme.walls = (Color){47, 79, 79, 255};         // Dark Slate Gray
        break;
    case 2:
        theme.background = (Color){100, 100, 100, 255}; // Gray background color
        theme.walls = (Color){50, 50, 50, 255};         // Dark gray walls
        break; // Medium Level

    case 3:                                            // Hard Level
        theme.background = (Color){255, 140, 0, 150};
        theme.walls = (Color){75, 0, 130, 255};        // Indigo
        break;
    default: // Fallback to a neutral theme if level is invalid

        theme.background = (Color){255, 239, 213, 255}; // Light Peach
        theme.walls = (Color){205, 133, 63, 255};       // Peru
        break;
    }
    return theme;
}
