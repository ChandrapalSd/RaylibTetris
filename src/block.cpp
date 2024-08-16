#include "block.h"
#include "colors.h"

Block::Block()
    :cellSize(30), rotationState(0), rowOffset(0), colOffset(0), colors(GetCellColors())
{
}

void Block::Draw() const
{
    const std::vector<Position>& tiles = cells.at(rotationState);

    for(Position tile: tiles)
    {
        DrawRectangle(tile.column* cellSize+1+colOffset*cellSize, tile.row* cellSize+1+rowOffset*cellSize, cellSize-1, cellSize-1, colors[type]);
    }
}

void Block::Move(int rows, int cols)
{
    rowOffset += rows;
    colOffset += cols;
}

std::vector<Position> Block::GetCellPositions() const
{
    const std::vector<Position>& tiles = cells.at(rotationState);
    std::vector<Position> res;
    res.reserve(tiles.size());

    for(const Position p: tiles)
    {
        res.emplace_back(p.row+rowOffset, p.column+colOffset);
    }

    return res;
}

void Block::Rotate()
{
    rotationState = (rotationState+1)%cells.size();
}

void Block::UndoRotation()
{
    if(--rotationState == -1)
        rotationState = cells.size()-1;
}
