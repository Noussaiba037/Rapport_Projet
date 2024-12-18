#ifndef MENU_H
#define MENU_H

class Menu
{
public:
    static void MainMenu();
    static void DifficultyMenu();
    static void PauseMenu();
    static void GameOverMenu(float timeTaken, int difficulty);
};

#endif