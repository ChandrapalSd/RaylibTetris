#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    void Initialize();
    void Print() const;
    void Draw() const;
    [[nodiscard]] bool IsCellOutside(int r, int c) const;
    [[nodiscard]] bool IsCellEmpty(int r, int c) const;
    int ClearFullRows();
public:
    static const int ROWCOUNT = 20;
    static const int COLCOUNT = 10;
    int grid[ROWCOUNT][COLCOUNT] = {}; // Block::Type
private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    [[nodiscard]] bool IsRowFull(int r) const;
    void ClearRow(int r) ;
    void MoveRowDown(int r, int count) ;
};
