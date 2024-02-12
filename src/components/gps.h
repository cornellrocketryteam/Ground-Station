#pragma once

#include "raylib.h"

class GPS {
    private:
    /**
     * The Image variable to store the image of the launch site
    */
    Image launchSiteImage; 

    /**
     * The current longitude and latitude position of the rocket 
    */
    int currentLongitude; 
    int currentLatitude; 

    /**
     * The longitude and latitude of the image used to calculate where the 
    rocket's position should be drawn 
    */
    int imageLongitude;
    int imageLatitude; 

    public: 
    /**
     * Draws the launch site image
    */
    void drawLaunchSite(); 
    /**
     * Draws the rocket's current longitude and latitude 
    */
    void drawRocketPosition(); 
    /**
     * Updates the position of the rocket's longitude and latitude 
    */
    void updatePosition(); 

    /**
     * Sets the path and loads the image, and initializes the current longitude and lattitude values
    */
    GPS(); 

}; 