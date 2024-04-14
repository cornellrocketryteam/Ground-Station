#pragma once
#include "serialread.h"
#include <vector>
#include <string>

class DataPoint
{
public:
    /**
     * Creates the Status Light
    */
    DataPoint(std::string title);
    /**
     * Gets the name
    */
    std::string getTitle();
    /**
     * Gets the value
    */
    float getValue();
    /**
     * Sets the Value 
    */
    void setValue(float val); 

private:
    std::string title;
    float value;
};

class DataGrid
{
public:
    /**
     * Intitializes the width, height, and positions. Then, it creates StatusLights for each sensor,
     * and adds those to the vector.
    */
    DataGrid();
    /**
     * Draws the current bar and all of its StatusLights in the statusLights vector
    */
    void draw(int posX, int posY, int width, int height);
    /**
     * Updates all of the values with the Serial Map
    */
    void updateValues();
private:
    /**
     * Vector to store the status lights
    */
    std::vector<DataPoint*> data_points;
};
