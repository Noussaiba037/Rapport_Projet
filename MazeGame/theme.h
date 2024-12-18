#ifndef THEME_H
#define THEME_H

#include "raylib.h"
struct Theme
{
    Color background;
    Color walls;

};

// Function to load themes based on the level
Theme GetThemeForLevel(int level);

#endif