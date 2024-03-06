#include "graph.h"
#include <math.h>
#include <string>
#include "dataprocessing.h"
#include <random> 

constexpr int lowerGraphYBound = 0;
constexpr int upperGraphYBound = 12000;

/**
 * posY is the top-left Y-coordinate of the graph
 * height is the height of the graph
 * graphY is the real elevation of the graph 
*/
int graphYToScreenY(int posY, int height, int graphY)
{
    int input_start = lowerGraphYBound;
    int input_end = upperGraphYBound;
    int output_start = posY + height;
    int output_end = posY;
    double slope = 1.0 * (output_end - output_start) / (input_end - input_start);
    return output_start + round(slope * (graphY - input_start));
}

void Graph::draw(int posX, int posY, int width, int height)
{

    int fontSize = 20;
    // Text on left-hand side 
    int offsetFromLeft = MeasureText(std::to_string(upperGraphYBound).c_str(), fontSize); //  Offset by the size of our largest possible altitude

    // Outlines of graph
    int altitudeAndGraphSpacing = 5;
    DrawRectangleLines(posX+offsetFromLeft+altitudeAndGraphSpacing, posY, width-offsetFromLeft-altitudeAndGraphSpacing, height, WHITE);

    // Draws Lines 
    for (int i = 0; i <= upperGraphYBound; i += 2000) {
        int y = graphYToScreenY(posY, height, i);
        Color color = i == 10000 ? RED : WHITE;
        DrawLine(posX+offsetFromLeft+altitudeAndGraphSpacing, y, posX+width, y, color);
        std::string text = std::to_string(i);
        int textWidth = MeasureText(text.c_str(), fontSize);
        DrawText(text.c_str(), posX+offsetFromLeft-textWidth, y-fontSize/2, fontSize, color);
    }

    // Draw the elements of the elevationQueue
    int track = 0; 
    float stepLength = (width - offsetFromLeft) / 300.0; 

    // change loop guard to (300 - track >= 0)
    while (SerialRead::elevationQueue.size() - track >= 0){
        DrawCircle((posX + width) - track*stepLength, graphYToScreenY(posY,height,SerialRead::elevationQueue.at(SerialRead::elevationQueue.size()-track)), 0.1, RED); 
        
        // Random circle tester 
        // DrawCircle((posX + width) - track*stepLength, graphYToScreenY(posY, height, rand() % 12000),1,RED);
        track += 1; 
    }



}
