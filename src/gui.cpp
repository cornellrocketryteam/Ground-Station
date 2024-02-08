#include "gui.h"

GUI::GUI(int screenWidth, int screenHeight) : currentScreen(TITLE),
             sensorButton(100, screenHeight / 2 + 100, 200, 100, WHITE, "Sensor Page"),
             rocket3DButton(400, screenHeight / 2 + 100, 200, 100, WHITE, "3D Model"),
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
        DrawText("Cornell Rocketry Ground Station", 10, screenHeight / 2, 60, WHITE);

        sensorButton.draw();
        rocket3DButton.draw();

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
