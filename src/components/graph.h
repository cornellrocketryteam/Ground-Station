#pragma once

#include <vector>

#include "raylib.h"

class Graph {
public:
    Graph(float x, float y, float width, float height, Color color);
    void draw();

private:
    Rectangle bounds;
    Color color;
    std::vector<float> dataValues;
};
