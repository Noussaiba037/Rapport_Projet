#include "maze.h"
#include "raylib.h"
#include "config.h"
#include "theme.h"

Maze::Maze()
{
    Initialize();
}

void Maze::Initialize()
{
    maze.clear(); // Make sure to clear old data before re-initializing 
    maze.resize(GRID_WIDTH);// Resize the outer vector (columns)
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        maze[x].resize(GRID_HEIGHT); // Resize the inner vector (rows)
        for(int y = 0; y < GRID_HEIGHT; y++)
        {
            maze[x][y].visited = false;
            maze[x][y].topWall = true;
            maze[x][y].bottomWall = true;
            maze[x][y].leftWall = true;
            maze[x][y].rightWall = true;
        }
    }
}
void Maze::GenerateDFS(int x, int y)
{
    // Mark the current cell as visited
    maze[x][y].visited = true;
    // Directions array : UP(0), RIGHT(1), DOWN(2), LEFT(3)
    int directions[] = {0, 1, 2, 3};
    // This part randomly shuffles the directions[] array. This ensures that when we move to the neighboring cells, the direction order is randomized.
    // That why, the programe may move UP first, sometimes RIGHT, etc... 
    for(int i=0; i<4 ; i++)
    {
        // Rnadom index between i and 3
        int j = GetRandomValue(i,3);
        // Swap directions[i] and 3
        swap(directions[i], directions[j]);
    }

    // The function now loops over the shuffled directions(directions[0], directions[1], directions[2], directions[3)
    // For each direction, it updates the nx (new x-coordinate) and ny (new y-coordinate) based on the current direction
    for(int i = 0; i < 4; i++)
    {
        // Update coordinates based on direction
        int nx = x, ny = y;
        if (directions[i] == 0)
            ny -= 1;
        if (directions[i] == 1)
            nx += 1;
        if (directions[i] == 2)
            ny += 1;
        if (directions[i] == 3)
            nx -= 1;
        
        // Before moving to new cell (nx, ny). Check if the new position is within bounds and has not been visited
        if (nx >= 0 && ny >= 0 && nx < GRID_WIDTH && ny < GRID_HEIGHT && !maze[nx][ny].visited)
        {
            // Carve the wall between the current cell (x,y) and the new cell (nx,ny).
            if (directions[i] == 0)//Moving UP
            {
                // Remove the top wall of the current cell and the bottom wall of the neighboring cell
                maze[x][y].topWall = false;
                maze[nx][ny].bottomWall = false;
            }
            if (directions[i] == 1)//Moving RIGHT
            {
                //Remove the right wall of the current cell and the left wall of the neighboring cell
                maze[x][y].rightWall = false;
                maze[nx][ny].leftWall = false;
            }
            if (directions[i] == 2)//Moving DOWN
            {
                //Remove the bottom wall of the current cell and the top wall of the neighboring cell
                maze[x][y].bottomWall = false;
                maze[nx][ny].topWall = false;
            }
            if (directions[i] == 3)//Moving LEFT
            {
                // Remove the left wall of the current cell and the right wall of the neighboring cell
                maze[x][y].leftWall = false;
                maze[nx][ny].rightWall = false;
            }

            //After removing the wall, the function recursivly calls itself to generate the maze starting from the new cell (nx,ny).
            // The function will continue to recurse itself until all neighboring cells have been visited and no further moves are possible.

            GenerateDFS(nx,ny);
        }
    }
}

void Maze::Draw(const Theme &theme, float offsetX, float offsetY)
{
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            float cellX = offsetX + x * CELL_SIZE;
            float cellY = offsetY + y * CELL_SIZE;

            if (maze[x][y].topWall)
                DrawLine(cellX, cellY, cellX + CELL_SIZE, cellY, theme.walls);
            if (maze[x][y].bottomWall)
                DrawLine(cellX, cellY + CELL_SIZE, cellX + CELL_SIZE, cellY + CELL_SIZE, theme.walls);
            if (maze[x][y].leftWall)
                DrawLine(cellX, cellY, cellX, cellY + CELL_SIZE, theme.walls);
            if (maze[x][y].rightWall)
                DrawLine(cellX + CELL_SIZE, cellY, cellX + CELL_SIZE, cellY + CELL_SIZE, theme.walls);
        }
    }
}

vector<vector<Cell>> &Maze::GetMaze()
{
    return maze;
}