#include <raylib.h>
#include <iostream>
#include "grid.h"
#include "block.h"
#include "game.h"
#include "colors.h"

int main()
{
    InitWindow(500, 620, "Raylib Tetris");
    SetTargetFPS(60);

    srand(time(NULL)*time(NULL));

    Font font = LoadFontEx("res/monogram.ttf",64 ,0, 0);

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
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {365, 175}, 38, 2, WHITE);
        if(g.gameOver)
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        std::string scoreStr = std::to_string(g.score);
        Vector2 textSize = MeasureTextEx(font, scoreStr.c_str(), 38, 2);
        DrawTextEx(font, scoreStr.c_str(), {320+(170-textSize.x)/2, 65}, 38, 2, WHITE);


        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        g.Draw();
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}