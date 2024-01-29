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
    //Create GUI object
    GUI gui; 

    // Load in textures only once 
    gui.rocketModel.loadTerrain(); 
    gui.rocketModel.loadRocket();
     // Main game loop

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        gui.drawGUI(); 
    }

    // Clean up all data, textures, and models 
    gui.rocketModel.unloadTerrain();
    gui.rocketModel.unloadRocket(); 
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}