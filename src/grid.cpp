#include "grid.h"
#include "colors.h"
#include <cstring>
#include <iostream>

Grid::Grid()
    :numRows(20), numCols(10), cellSize(30)
{
    Initialize();
}

void Grid::Initialize()
{
    memset(grid, 0, sizeof(int)*numCols*numRows);

    
    colors = GetCellColors();
}

void Grid::Print()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << '\n';
    }
    
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            DrawRectangle(column*cellSize +1, row*cellSize +1, cellSize-1, cellSize-1, colors[grid[row][column]]);
        }
        std::cout << '\n';
    }
    
}

bool Grid::IsCellOutside(int r, int c) const
{
    return !(r>=0 && r <numRows && c>=0 && c<numCols);
}
