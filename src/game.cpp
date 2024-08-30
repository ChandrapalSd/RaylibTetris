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
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    rotateSound = LoadSound("res/rotate.mp3");
    clearSound = LoadSound("res/clear.mp3");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
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
        UpdateScore(0, 1);
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
    currentBlock.Draw(grid.padding, grid.padding);
    nextBlock.Draw(270, 270);
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
        else
            PlaySound(rotateSound);
    }
}

void Game::LockBlock()
{
    const std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(const Position p: tiles)
    {
        grid.grid[p.row][p.column] = currentBlock.type;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
    if(BlockFits() == false)
    {
        gameOver = true;
    }
    int rowsCleared = grid.ClearFullRows();
    if(rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
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
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score+=100;
        break;
    case 2:
        score+=300;
        break;
    case 3:
        score+=500;
        break;
    default:
        break;
    }
    score += moveDownPoints;
}

