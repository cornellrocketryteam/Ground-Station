#pragma once

#include <vector>

#include "raylib.h"

class Graph {
public:
    /**
     * Creates a graph with the top-left corner being at (x,y) and with a width and height.
    */
    Graph(float x, float y, float width, float height, Color color);
    /**
     * Draws the graph and then plots the line 
    */
    void draw();
    /**
     * Will plot the data values as a line graph, and the 10,000ft line 
    */
    void plotLine();

private:
    /**
     * The bounds of the graph
    */
    Rectangle bounds;
    Color color;
    std::vector<float> dataValues;
};
