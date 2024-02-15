#include "graph.h"

Graph::Graph(float x, float y, float width, float height, Color color) : bounds({x, y, width, height}), color(color)
{
}

void Graph::draw()
{
    DrawRectangleRec(bounds, color);
    DrawRectangleLinesEx(bounds, 3,BLACK); 
    plotLine();
}

void Graph::plotLine(){
    // The Bounds of this graph are from 0 to 12,000 ft in the y direction. 

    int tenThousandLine = bounds.y + (bounds.height /6); // will draw the line at the partition
    DrawLine(bounds.x, tenThousandLine, bounds.x + bounds.width, tenThousandLine, RED);

    // Temporarily draw the line
    int i = bounds.x; 
    int j = bounds.y+bounds.height; 
    while (i < bounds.x + bounds.width){
        DrawCircle(i, j,0.1, BLACK) ;
        i += 1; 
        j -= 1; 
    }
}
