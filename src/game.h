#pragma once
#include "grid.h"
#include "block.h"
#include <ctime>

class Game
{
public:
    Game();
    Block GetRandomBlock();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void Draw() const;
    [[nodiscard]] bool IsBlockOutside() const;
    void RotateBlock();
    void LockBlock();
    [[nodiscard]] bool BlockFits() const;
    void Reset();
private:
    Grid grid;
    Block currentBlock;
    std::vector<Block> blocks;
    bool gameOver;
};

