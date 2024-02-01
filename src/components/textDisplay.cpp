#include "textDisplay.h"

TextDisplay::TextDisplay(float x, float y, float width, float height, Color color, std::string text) : bounds({x, y, width, height}), color(color), text(text)
{
}

void TextDisplay::draw()
{
    DrawRectangleRec(bounds, color);
    int posX = bounds.x + bounds.width / 2 - MeasureText(text.c_str(), 20) / 2;
    int posY = bounds.y + bounds.height / 2 - 10;
    DrawText(text.c_str(), posX, posY, 20, WHITE);
}

void TextDisplay::setText(std::string newText)
{
    text = newText;
}

