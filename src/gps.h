#pragma once

#include "raylib.h"

// LAUNCH SITE COORDINATES: (32.9398594, -106.9115652)
class GPS {
public:
    /**
     * Unloads the texture
    */
    ~GPS();
    /**
     * Draws the launch site and the rocket's current longitude and latitude
    */
    void draw(int posX, int posY, int width, int height);
    /**
     * Updates the position of the rocket's longitude and latitude
    */
    void updatePosition();

private:
    /**
     * The texture variable to store the image of the launch site
    */
    Texture launchSiteTexture;

    /**
     * The current longitude and latitude position of the rocket 
    */
    int currentLongitude; 
    int currentLatitude; 
};