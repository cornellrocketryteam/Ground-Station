#include "graph.h"
#include <math.h>
#include <string>

constexpr int lowerGraphYBound = 0;
constexpr int upperGraphYBound = 12000;

// graphY is between lower bounds and upper bouns
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
    int offsetFromLeft = MeasureText(std::to_string(upperGraphYBound).c_str(), fontSize); //  Offset by the size of our largest possible altitude
    int altitudeAndGraphSpacing = 5;
    DrawRectangleLines(posX+offsetFromLeft+altitudeAndGraphSpacing, posY, width-offsetFromLeft-altitudeAndGraphSpacing, height, WHITE);

    for (int i = 0; i <= upperGraphYBound; i += 2000) {
        int y = graphYToScreenY(posY, height, i);
        Color color = i == 10000 ? RED : WHITE;
        DrawLine(posX+offsetFromLeft+altitudeAndGraphSpacing, y, posX+width, y, color);
        std::string text = std::to_string(i);
        int textWidth = MeasureText(text.c_str(), fontSize);
        DrawText(text.c_str(), posX+offsetFromLeft-textWidth, y-fontSize/2, fontSize, color);
    }

    // plotLine();
}
