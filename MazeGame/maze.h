#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "config.h"
#include "raylib.h"
#include "theme.h"

using namespace std;
struct Cell
{
    bool visited;
    bool topWall;
    bool rightWall;
    bool bottomWall;
    bool leftWall;
};

class Maze
{
private:
    vector<vector<Cell>> maze;

public:
    Maze();
    void Initialize();
    void GenerateDFS(int x, int y);
    void Draw(const Theme &theme, float offsetX, float offsetY);
    vector<vector<Cell>> &GetMaze(); // Accessor for maze
};

#endif