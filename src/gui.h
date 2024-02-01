#pragma once

#include "raylib.h"
#include "rocket3d.h"
#include "sensorDisplay.h"
#include "components/button.h"

typedef enum GameScreen { TITLE, ROCKET3D, SENSORVALUES } GameScreen;

class GUI {
public:
    GUI(int screenWidth, int screenHeight);
    ~GUI();
    void draw();
    bool shouldClose();

private:
    // the Colors for the window
    Color backgroundColor;

    Button sensorButton;
    Button rocket3DButton;
    Button titleButton;

    RocketScreen rocketModel;
    SensorScreen sensorDisplay;

    // the enumeration of game states
    GameScreen currentScreen;
};