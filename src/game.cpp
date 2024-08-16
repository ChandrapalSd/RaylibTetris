#include "game.h"
#include <random>
#include <ctime>

inline std::vector<Block> getAllBlocks()
{
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

Game::Game()
{
    blocks = getAllBlocks();
    currentBlock = GetRandomBlock();
}

Block Game::GetRandomBlock()
{
    if(!blocks.size())
        blocks = getAllBlocks();
    const int randomIndex = rand()%blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin()+randomIndex);
    return block;
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
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
    currentBlock.Move(0, -1);
    if(IsBlockOutside())
        currentBlock.Move(0, 1);
}

void Game::MoveBlockRight()
{
    currentBlock.Move(0, 1);
    if(IsBlockOutside())
        currentBlock.Move(0, -1);
}

void Game::MoveBlockDown()
{
    currentBlock.Move(1, 0);
    if(IsBlockOutside())
    {
        currentBlock.Move(-1, 0);
        LockBlock();
    }
}

void Game::Draw()
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
    currentBlock.Rotate();
    if(IsBlockOutside())
        currentBlock.UndoRotation();
}

void Game::LockBlock()
{
    // TODO(CP): Implement
}
