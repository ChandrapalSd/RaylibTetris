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

void Grid::Print() const
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

void Grid::Draw() const
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

bool Grid::IsCellEmpty(int r, int c) const
{
    return grid[r][c] == 0; // Block::Type::Empty
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for (int r = numRows-1; r >=0; r--)
    {
        if(IsRowFull(r))
        {
            ClearRow(r);
            completed++;    
        } 
        else if(completed>0)
        {
            MoveRowDown(r, completed);
        }
    }
    
    return completed;
}

bool Grid::IsRowFull(int r) const
{
    for(const int e: grid[r])
    {
        if(e == 0)
            return false;
    }
    return true;
}

void Grid::ClearRow(int r)
{
    for(int& e: grid[r])
        e = 0;
}

void Grid::MoveRowDown(int r, int count)
{
    //TODO(CP): assert r+cout < ROWCOUNT
    for (int c = 0; c < COLCOUNT; c++)
    {
        grid[r+count][c] = grid[r][c];
        grid[r][c] = 0;
    }
}

