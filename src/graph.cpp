#include "graph.h"
#include <string>
#include "sfr.h"

constexpr int lowerGraphYBound = 0;
constexpr int upperGraphYBound = 12000;
constexpr int graphStep = 2000;

/**
 * posY is the top-left Y-coordinate of the graph
 * height is the height of the graph
 * graphY is the real elevation of the graph 
*/
int graphYToScreenY(int posY, int height, int graphY)
{
    float percentageOfHeight = float(graphY - lowerGraphYBound) / (upperGraphYBound - lowerGraphYBound);
    return posY + height - (height * percentageOfHeight);
}

void Graph::draw(int posX, int posY, int width, int height) {

    int fontSize = 20;
    // Text on left-hand side 
    int offsetFromLeft = MeasureText(std::to_string(upperGraphYBound).c_str(), fontSize); //  Offset by the size of our largest possible altitude

    // Outlines of graph
    int altitudeAndGraphSpacing = 5;
    DrawRectangleLines(posX + offsetFromLeft + altitudeAndGraphSpacing, posY, width - offsetFromLeft - altitudeAndGraphSpacing, height, WHITE);

    // Draws Lines 
    for (int i = lowerGraphYBound; i <= upperGraphYBound; i += graphStep) {
        int y = graphYToScreenY(posY, height, i);
        Color color = i == 10000 ? RED : WHITE;
        DrawLine(posX + offsetFromLeft + altitudeAndGraphSpacing, y, posX + width, y, color);
        std::string text = std::to_string(i);
        int textWidth = MeasureText(text.c_str(), fontSize);
        DrawText(text.c_str(), posX + offsetFromLeft - textWidth, y - fontSize / 2, fontSize, color);
    }

//    for (int i = 0; i < 300; i++) {
//        sfr::serialRead.elevationQueue.push_back(i*40);
//    }

    if (sfr::serialRead.elevationQueue.size() > 1) {
        float stepLength = float(width - offsetFromLeft - altitudeAndGraphSpacing) / 300;
        for (auto i = sfr::serialRead.elevationQueue.size() - 1; i > 0; i--) {
            float startPosX = float(posX) + offsetFromLeft + altitudeAndGraphSpacing + (300 - i) * stepLength;
            float startPosY = graphYToScreenY(posY, height, sfr::serialRead.elevationQueue.at(300 - i));
            float endPosX = float(posX) + offsetFromLeft + altitudeAndGraphSpacing + (299 - i) * stepLength;
            float endPosY = graphYToScreenY(posY, height, sfr::serialRead.elevationQueue.at(299 - i));
            DrawLineEx({startPosX, startPosY}, {endPosX, endPosY}, 2, BLUE);
        }
    }

//    sfr::serialRead.elevationQueue.clear();
}
