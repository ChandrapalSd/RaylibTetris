#pragma once
#include "grid.h"
#include "block.h"
#include <ctime>

class Game
{
public:
    Game();
    ~Game();
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
    bool gameOver;
    int score;
private:
    void UpdateScore(int linesCleared, int moveDownPoints);
private:
    Grid grid;
    Block currentBlock;
    Block nextBlock;
    std::vector<Block> blocks;
    Sound rotateSound;
    Sound clearSound;
};

