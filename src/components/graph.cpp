#include "graph.h"

Graph::Graph(float x, float y, float width, float height, Color color) : bounds({x, y, width, height}), color(color)
{
}

void Graph::draw()
{   // This will draw a rounded border 
    // DrawRectangleRounded(bounds, 0.5, 1, color);
    // DrawRectangleRoundedLines(bounds, 0.5,1,3, BLACK); 

    // Draw a Rectangle 
    DrawRectangleRec(bounds, color); 
    DrawRectangleLinesEx(bounds,3,BLACK);
    plotLine();
}

void Graph::plotLine(){
    // The Bounds of this graph are from 0 to 12,000 ft in the y direction. 

    int tenThousandLine = bounds.y + (bounds.height /6); // will draw the line at the partition
    DrawLine(bounds.x, tenThousandLine, bounds.x + bounds.width, tenThousandLine, RED);

    // Temporarily draw the line
    float i = bounds.x; 
    float j = bounds.y+bounds.height; 
    while (i < bounds.x + bounds.width){
        DrawCircle(i, j,1, BLACK) ;
        i += 2; 
        j -= 1; 
    }
}
