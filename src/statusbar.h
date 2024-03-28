#pragma once

#include <iostream>
#include <vector>
#include <string>

/**
 * Will represent the blinking lights that will be in the bar
*/
class StatusLight
{
public:
    /**
     * Creates the Status Light
    */
    StatusLight(std::string name, float radius);
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
    std::string getName();
    /*Sets the working state of the status light*/
    void setWorking(bool val); 

private:
    std::string name;
    float radius;
    bool isWorking;
};

class StatusBar
{
public:
    /**
     * Intitializes the width, height, and positions. Then, it creates StatusLights for each sensor,
     * and adds those to the vector.
    */
    StatusBar();
    /**
     * Draws the current bar and all of its StatusLights in the statusLights vector
    */
    void draw(int posX, int posY, int width, int height);

private:
    /**
     * Vector to store the status lights
    */
    std::vector<StatusLight> status_lights;

    /*Updates the status lights based on the sfr::serialRead value*/
    void updateStatusLights();
};
