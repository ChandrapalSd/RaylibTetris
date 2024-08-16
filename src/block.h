#pragma once
#include <vector>
#include <unordered_map>
#include <raylib.h>
#include "position.h"

class Block
{
public:
    enum Type
    {
        NONE=0,
        L=1,
        J=2,
        I=3,
        O=4,
        S=5,
        T=6,
        Z=7,
        COUNT
    };
public:
    Block();
    void Draw() const;
    void Move(int rows, int cols);
    [[nodiscard]] std::vector<Position> GetCellPositions() const;
    void Rotate();
    void UndoRotation();
    Type type;
    std::unordered_map<int, std::vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    int rowOffset;
    int colOffset;
    std::vector<Color> colors;
};

// Inherited

class LBlock : public Block
{
public:
    LBlock();
};

class JBlock : public Block
{
public:
    JBlock();
};

class IBlock : public Block
{
public:
    IBlock();
};

class OBlock : public Block
{
public:
    OBlock();
};

class SBlock : public Block
{
public:
    SBlock();
};

class TBlock : public Block
{
public:
    TBlock();
};

class ZBlock : public Block
{
public:
    ZBlock();
};
