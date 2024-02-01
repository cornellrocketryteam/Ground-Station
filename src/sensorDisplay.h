#pragma once

#include "raylib.h"
#include <iostream>

#include "components/textDisplay.h"
#include "components/graph.h"

class SensorScreen {
public:
    // TODO CHANGE THESE
    const int screenWidth = 1600;
    const int screenHeight = 1000;

    /**
     * Initializes the displays. 
    */
    SensorScreen();

    /**
     * Draws all of the displays. 
    */
   void drawComponents(); 

   /**
    * Update serial Values
   */
    void updateValues();

private:
    std::vector<Graph> graphs;

    Graph elevationGraph;
    Graph temperatureGraph;

    /**
     * The text boxes that will display rocket data.
    */
    TextDisplay latitude;
    TextDisplay longitude;
    TextDisplay elevation;
    TextDisplay accel_x;
    TextDisplay accel_y;
    TextDisplay accel_z;
    TextDisplay gyro_x;
    TextDisplay gyro_y;
    TextDisplay gyro_z;
    TextDisplay mag_x;
    TextDisplay mag_y;
    TextDisplay mag_z;
    TextDisplay temp;

    int textDisplayWidth;
    int textDisplayHeight;
    int fontSize;
}; 