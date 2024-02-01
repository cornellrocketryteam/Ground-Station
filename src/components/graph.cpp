#include "graph.h"

Graph::Graph(float x, float y, float width, float height, Color color) : bounds({x, y, width, height}), color(color)
{
}

void Graph::draw()
{
    DrawRectangleRec(bounds, color);
    //DrawRectangle(bounds.x,bounds.y,bounds.width,bounds.height,color);
}

