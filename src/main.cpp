/*******************************************************************************************
*
*   Cornell Rocketry Ground Station for 2024. Made by Max Larsson and Benjamin Zou. 
*
********************************************************************************************/

#include "gui.h"
#include "raylib.h"

#define TEST 

#ifndef TEST 
#include <pigpio.h> 
#endif 

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(1600, 1000, "Ground Station"); /*Initialize the raylib window*/
    SetTargetFPS(60);

    #ifndef TEST 
        if (gpioInitialise() < 0)
        {
            printf("Pigpio not initialized."); 
        }
        else
        {
            printf("Pigpio succesffuly initialized.")
        }
    #endif 

    GUI gui; 

    while (!WindowShouldClose())
    {
        gui.processEvents();

        BeginDrawing();
        ClearBackground({56, 55, 52});

        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        gui.draw(0, 0, screenWidth, screenHeight);

        EndDrawing();
    }

    CloseWindow();
    #ifndef TEST 
        gpioTerminate();
    #endif 

    return 0;
}
