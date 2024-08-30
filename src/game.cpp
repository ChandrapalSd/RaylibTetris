#include "game.h"
#include <random>
#include <ctime>

inline std::vector<Block> GetAllBlocks()
{
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

Game::Game()
{
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    gameOver = false;
}

Block Game::GetRandomBlock()
{
    if(!blocks.size())
        blocks = GetAllBlocks();
    const int randomIndex = rand()%blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin()+randomIndex);
    return block;
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed)
    {
        gameOver = false;
        Reset();
    }
    
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    
    case KEY_DOWN:
        MoveBlockDown();
        break;
    
    case KEY_UP:
        RotateBlock();
        break;
    
    }
}

void Game::MoveBlockLeft()
{
    if(!gameOver)
    {
        currentBlock.Move(0, -1);
        if(IsBlockOutside() || !BlockFits())
            currentBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight()
{
    if(!gameOver)
    {
        currentBlock.Move(0, 1);
        if(IsBlockOutside() || !BlockFits())
            currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown()
{
    if(!gameOver)
    {
        currentBlock.Move(1, 0);
        if(IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::Draw() const
{
    grid.Draw();
    currentBlock.Draw();
}

bool Game::IsBlockOutside() const
{
    const std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(const Position item: tiles)
    {
        if(grid.IsCellOutside(item.row, item.column))
            return true;
    }
    return false;
}

void Game::RotateBlock()
{
    if(!gameOver)
    {
        currentBlock.Rotate();
        if(IsBlockOutside() || !BlockFits())
            currentBlock.UndoRotation();
    }
}

void Game::LockBlock()
{
    const std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(const Position p: tiles)
    {
        grid.grid[p.row][p.column] = currentBlock.type;
    }
    currentBlock = GetRandomBlock();
    if(BlockFits() == false)
    {
        gameOver = true;
    }
    grid.ClearFullRows();
}

bool Game::BlockFits() const
{
    const std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(const Position p: tiles)
    {
        if(!grid.IsCellEmpty(p.row, p.column))
            return false;
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
}
