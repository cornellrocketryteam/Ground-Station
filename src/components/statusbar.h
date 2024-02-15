#pragma once

#include "raylib.h"
#include <iostream>
#include <vector> 

/**
 * Will represent the blinking lights that will be in the bar 
*/
class StatusLight {
    private:
        const char* name; 
        float radius; 
        bool isWorking; 
    public: 
    /**
     * Creates the Status Light
    */
    StatusLight(const char* _name, float _radius, bool _isWorking);
    /**
     * Gets the sensor's current working state
    */
   bool getWorking(); 
   /**
    * Gets the radius
   */
    float getRadius();
    /**
     * Gets the name
    */
    const char*  getName(); 
}; 

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
       
};