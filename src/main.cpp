#include <raylib.h>
#include <iostream>
#include "grid.h"
#include "block.h"
#include "game.h"

int main()
{
    Color darkBlue = {255, 0, 0, 255};
    InitWindow(300, 600, "Raylib Tetris");
    SetTargetFPS(60);

    srand(time(NULL)*time(NULL));

    Game g;
    double lastUpdateTime = 0;
    while (!WindowShouldClose())
    {
        g.HandleInput();

        const double currentTime = GetTime();
        if(currentTime-lastUpdateTime > 0.2)
        {
            lastUpdateTime = currentTime;
            g.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        g.Draw();
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}