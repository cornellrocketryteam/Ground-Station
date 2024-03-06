#include "gui.h"
#include "dataprocessing.h"

#include "raylib.h"

void GUI::processEvents() {
    rocket.processEvents();
}

void GUI::draw(int posX, int posY, int width, int height)
{
    //SerialRead::readPack(); 

    // GPS
    // DrawRectangle(posX + 0.04*width, posY + 0.04*height, 0.35*width, 0.3*height, GRAY);
    gps.draw(posX + 0.04*width, posY + 0.04*height, 0.35*width, 0.3*height);

    // Data grid
    // DrawRectangle(0.04*screenWidth, 0.38*screenHeight, 0.35*screenWidth, 0.4*screenHeight, GRAY);
    data_grid.draw(posX + 0.04*width, posY + 0.38*height, 0.35*width, 0.4*height);

    // Altitude graph
    // DrawRectangle(posX + 0.43*width, posY + 0.43*height, 0.53*width, 0.35*height, GRAY);
    graph.draw(posX + 0.43*width, posY + 0.43*height, 0.53*width, 0.35*height);
    
    // Status bar
    // DrawRectangle(0.04*screenWidth, 0.82*screenHeight, 0.92*screenWidth, 0.14*screenHeight, GRAY);
    status_bar.draw(posX + 0.04*width, posY + 0.82*height, 0.92*width, 0.14*height);

    // 3D Model
    // DrawRectangle(posX + 0.43*width, posY + 0.04*height, 0.53*width, 0.35*height, GRAY);
    if (!rocket.isEnlarged()){
        // Draws the rocket un-enlarged
        rocket.draw(posX + 0.43*width, posY + 0.04*height, 0.53*width, 0.35*height);
    } else {
        // Draws the rocket enlarged 
        rocket.draw(posX , posY , width, height);
    }
}
