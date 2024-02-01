#include "button.h"

#include <iostream>

Button::Button(float x, float y, float width, float height, Color color, std::string text) : bounds({x, y, width, height}), color(color), text(text)
{
}

void Button::draw()
{
    DrawRectangleRec(bounds, color);
    const int posX = bounds.x + bounds.width / 2 - MeasureText(text.c_str(), 20) / 2;
    const int posY = bounds.y + bounds.height / 2 - 10;
    DrawText(text.c_str(), posX, posY, 20, BLACK);
}

bool Button::isMouseOverButton()
{
    const Vector2 mousePosition = GetMousePosition();
    return CheckCollisionPointRec(mousePosition, bounds);
}

bool Button::isClicked()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isMouseOverButton())
    {
        return true;
    }
    return false;
}
