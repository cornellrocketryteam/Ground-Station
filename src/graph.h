#pragma once

#include <vector>

#include "raylib.h"

class Graph {
public:
    /**
     * Draws the graph and then plots the line 
    */
    void draw(int posX, int posY, int width, int height);

private:
    /*
    * The data points that will be plotted 
    */
    std::vector<float> dataValues;
};
