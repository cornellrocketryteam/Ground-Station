#pragma once
#include <string>

#include "raylib.h"

class TextDisplay {
public:
    TextDisplay(float x, float y, float width, float height, Color color, std::string text);
    void draw();
    void setText(std::string newText);

private:
    Rectangle bounds;
    Color color;
    std::string text;
};
