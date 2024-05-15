#include "gui.h"

void GUI::draw(int posX, int posY, int width, int height)
{
    // Data grid
    data_grid.draw(posX + 0.04*width, posY + 0.04*height, 0.35*width, 0.78*height);

    // Altitude graph
    graph.draw(posX + 0.43*width, posY + 0.43*height, 0.53*width, 0.35*height);
    
    // Status bar
    status_bar.draw(posX + 0.04*width, posY + 0.82*height, 0.92*width, 0.14*height);

    // 3D Model
    rocket.draw(posX + 0.43*width, posY + 0.04*height, 0.53*width, 0.35*height);
}
