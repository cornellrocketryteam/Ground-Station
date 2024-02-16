/*******************************************************************************************
*
*   Cornell Rocketry Ground Station for 2024. Made by Max Larsson and Benjamin Zou. 
*
********************************************************************************************/

#include "gui.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(1600, 1000, "Ground Station");
    SetTargetFPS(60);


    auto gui = GUI(1600, 1000);

    while (!WindowShouldClose())
    {
        gui.draw();
    }

    CloseWindow();

    return 0;
}