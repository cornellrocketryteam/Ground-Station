#pragma once

#include "raylib.h"
#include <iostream>
#include <vector> 

/**
 * Will represent the blinking lights that will be in the bar 
*/
typedef struct  {
    // the name of this light that will appear in a text box above the light
    const char* name; 
    // radius of this circle
    float radius; 
    // if isWorking color green else red
    bool isWorking; 
} StatusLight; 

class StatusBar {
    private:

        /**
         * Vector to store the status lights 
        */
        std::vector<StatusLight> statusLights; 

        /**
         * The position of the top left corner of the bar 
        */
        int barPositionX; 
        int barPositionY; 
        /**
         * The width of the bar
        */
        int width; 
        /**
         * The height of the bar
        */
        int height; 
    public: 
        /**
         * Intitializes the width, height, and positions. Then, it creates StatusLights for each sensor,
         * and adds those to the vector. 
        */
        StatusBar(int posX, int posY, int wid, int hght); 
        /**
         * Draws the current bar and all of its StatusLights in the statusLights vector
        */
       void drawBar(); 
       /**
        * Updates current sensor colors
       */
        void updateSensor(const char* name);
};