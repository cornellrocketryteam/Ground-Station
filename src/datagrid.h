#pragma once
#include "serialread.h"
#include <vector>
#include <string>

class DataGrid
{
public:
    /**
     * Draws the current bar and all of its StatusLights in the statusLights vector
    */
    void draw(int posX, int posY, int width, int height);
};
