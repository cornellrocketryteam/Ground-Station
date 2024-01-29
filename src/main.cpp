/*******************************************************************************************
*
*   Cornell Rocketry Ground Station for 2024. Made by Max Larsson and Benjamin Zou. 
*
********************************************************************************************/


/**
 * Include statements
*/
#include "gui.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{   
    GUI gui; 
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        gui.drawGUI(); 
    }
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}