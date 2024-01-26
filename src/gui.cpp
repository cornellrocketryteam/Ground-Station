#include "gui.h"

void GUI::drawGUI(){
    BeginDrawing();

    updateSizes(); 

    // paint the background window's color 
    ClearBackground(backgroundColor);

    // Draws to the screen based on the current state 
    switch (currentScreen){
        case TITLE: {
            sensorButton.clicked = false;
            rocket3DButton.clicked = false; 

            DrawText("Welcome to the Cornell Rocketry Ground Station", 10, 10, 50, WHITE);

            drawButton(sensorButton); 
            drawButton(rocket3DButton); 

            // Button press logic 
            if (checkClicked(sensorButton)){
                currentScreen = SENSORVALUES; 
            }
            if (checkClicked(rocket3DButton)){
                currentScreen = ROCKET3D; 
            }
            

        } break; 
        case ROCKET3D: {
            titleButton.clicked = false; 

            // draws the 3d map of the rocket
            rocketModel.draw(); 

            DrawText("Live 3D Model", 20, 20, 60, WHITE);
            drawButton(titleButton); 

            // navigation back to title page 
            if (checkClicked(titleButton)){
                currentScreen = TITLE; 
            }
            
        } break; 
        case SENSORVALUES: {
            titleButton.clicked = false; 

            DrawText("Sensor Readings", 20, 20, 60, WHITE);
            drawButton(titleButton); 

            //draws all of the sensor components
            sensorDisplay.updateSizes(); 
            sensorDisplay.drawComponents(); 

            // navigation back to title page 
            if (checkClicked(titleButton)){
                currentScreen = TITLE; 
            }

        } break; 
        default: break; 

    }
    EndDrawing();
}

void GUI::updateSizes() {
    screenWidth = GetScreenWidth(); 
    screenHeight = GetScreenHeight(); 
}

GUI::GUI(){
    currentScreen = TITLE;

    screenWidth = 1600; 
    screenHeight = 1000;

    // initialize the buttons for the title screen 
    sensorButton = createButton(100, 100, 200, 100, WHITE, "go to sensor page");
    rocket3DButton = createButton(400, 100, 200, 100, WHITE, "go to a 3d model of the rocket");
    titleButton = createButton(100, 100, 200, 100, WHITE, "go back to title");

    // initialize the colors 
    backgroundColor = {56, 55, 52}; 

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT );

    InitWindow(screenWidth, screenHeight, "Ground Station");

    // Set desired framerate (frames-per-second)
    SetTargetFPS(60);
}

void drawButton(Button button){
    DrawRectangleRec(button.bounds, button.color);
    DrawText(button.text, (int)(button.bounds.x + button.bounds.width / 2 - MeasureText(button.text, 20) / 2),
                 (int)(button.bounds.y + button.bounds.height / 2 - 10), 20, BLACK);

}

Button createButton(float x, float y, float width, float height, Color color, const char* text) {
    Button button;
    button.bounds = (Rectangle){x, y, width, height};
    button.color = color;
    button.clicked = false;
    button.text = text;
    return button;
}

bool isMouseOverButton(Button button) {
    Vector2 mousePosition = GetMousePosition();
    return CheckCollisionPointRec(mousePosition, button.bounds);
}

bool checkClicked(Button button){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isMouseOverButton(button)) {
                button.clicked = true;
                return true; 
    }
    return false; 

}