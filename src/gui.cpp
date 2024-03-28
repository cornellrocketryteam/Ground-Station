#include "gui.h"
#include "sfr.h"

#include "raylib.h"

void GUI::processEvents() {
    rocket.processEvents();
}

void GUI::draw(int posX, int posY, int width, int height)
{
    // GPS
    gps.draw(posX + 0.04*width, posY + 0.04*height, 0.35*width, 0.3*height);

    // Data grid
    data_grid.draw(posX + 0.04*width, posY + 0.38*height, 0.35*width, 0.4*height);

    // Altitude graph
    graph.draw(posX + 0.43*width, posY + 0.43*height, 0.53*width, 0.35*height);
    
    // Status bar
    status_bar.draw(posX + 0.04*width, posY + 0.82*height, 0.92*width, 0.14*height);

    // 3D Model
    if (!rocket.isEnlarged()){
        // Draws the rocket un-enlarged
        rocket.draw(posX + 0.43*width, posY + 0.04*height, 0.53*width, 0.35*height);
    } else {
        // Draws the rocket enlarged 
        rocket.draw(posX , posY , width, height);
    }
}
