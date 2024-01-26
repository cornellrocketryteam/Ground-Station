#include "raylib.h"
#include "rocket3d.h"
#include "sensorDisplay.h"
#include <iostream>


/**
 * Used to create a button. 
*/
typedef struct {
    Rectangle bounds;
    Color color;
    bool clicked;
    const char *text;
} Button;

//------------------------------------------------------------------------------------------
// Types and Structures Definition / States 
//------------------------------------------------------------------------------------------
typedef enum GameScreen { TITLE, ROCKET3D, SENSORVALUES } GameScreen;


/*
* creates the buttons that are used to navigate
*/
Button createButton(float x, float y, float width, float height, Color color, const char* text); 

/**
 * Checks if the mouse position is over the current button. 
*/
bool isMouseOverButton(Button button);

/**
 * Draws the button to the screen with its text field. 
*/
void drawButton(Button button); 

/**
 * Checks if this mouse button was clicked. 
*/
bool checkClicked(Button button); 


class GUI {
private:
// Variable Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth;
    int screenHeight;

    int fontSize; 
    int buttonSize; 
    int graphSize; 

    // the Colors for the window 
    Color backgroundColor; 

    Button sensorButton;
    Button rocket3DButton;
    Button titleButton; 

    // the enumeration of game states 
    GameScreen currentScreen; 

    // the rocket gui 
    RocketModel rocketModel; 

    // the sensor gui 
    SensorDisplay sensorDisplay; 


public:
    /**
     * Initializes the width and height, makes the window resizable, and 
     * creates the window. Also sets the target FPS to 60. 
    */
    GUI(); 

    /**
     * Draws the GUI and its respective components. 
    */
    void drawGUI(); 

    /**
     * Updates the variables based on the screen's current width and height
    */
    void updateSizes(); 
}; 