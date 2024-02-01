/*******************************************************************************************
*
*   Cornell Rocketry Ground Station for 2024. Made by Max Larsson and Benjamin Zou. 
*
********************************************************************************************/

#include "gui.h"

int main()
{
    auto gui = GUI(1600, 1000);

    while (!gui.shouldClose())
    {
        gui.draw();
    }

    return 0;
}