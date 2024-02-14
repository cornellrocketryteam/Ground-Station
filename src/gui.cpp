#include "gui.h"

GUI::GUI(int screenWidth, int screenHeight) : currentScreen(TITLE),
             sensorButton(100, screenHeight / 2 , 200, 100, WHITE, "Sensor Page"),
             rocket3DButton(screenWidth - 210, screenHeight - 110 , 200, 100, WHITE, "3D Model"),
             titleButton(100, 100, 200, 100, WHITE, "Back to Title Page"),
             backgroundColor({56, 55, 52})
{
}

void GUI::draw()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    BeginDrawing();

    // paint the background window's color
    ClearBackground(backgroundColor);

    // Draws to the screen based on the current state
    switch (currentScreen)
    {
    case TITLE:
        DrawText("Cornell Rocketry Ground Station", 10, 10, 60, WHITE);

        // toggles the mini state. Starts as true 
        if (rocketModel.isMini == false){
        rocketModel.toggleMiniState();
        } 

        sensorButton.draw();
        rocket3DButton.draw();

        rocketModel.drawMiniVersion();
        // Button press logic
        if (sensorButton.isClicked())
        {
            currentScreen = SENSORVALUES;
        }
        if (rocket3DButton.isClicked())
        {
            currentScreen = ROCKET3D;
        }
        break;
    case ROCKET3D:
        if (rocketModel.isMini == true){
        rocketModel.toggleMiniState();
        } 

        // draws the 3d map of the rocket
        rocketModel.draw();

        DrawText("Live 3D Model", 20, 20, 60, WHITE);
        titleButton.draw();

        //Draw the rocket data in the bottom right of the screen
        rocketModel.displayRocketTexts();

        // navigation back to title page
        if (titleButton.isClicked())
        {
            currentScreen = TITLE;
        }
        break;
    case SENSORVALUES:
        {
            DrawText("Sensor Readings", 20, 20, 60, WHITE);
            titleButton.draw();

            //draws all of the sensor components
            sensorDisplay.drawComponents();


            // navigation back to title page
            if (titleButton.isClicked())
            {
                currentScreen = TITLE;
            }
        }
        break;
    default:
        break;
    }

    EndDrawing();
}
