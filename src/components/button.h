#pragma once

#include <string>

#include "raylib.h"

class Button {
public:
    Button(float x, float y, float width, float height, Color color, std::string text);
    void draw();
    bool isMouseOverButton();
    bool isClicked();

private:
    Rectangle bounds;
    Color color;
    std::string text;
};
