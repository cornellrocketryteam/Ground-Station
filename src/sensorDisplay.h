#include "raylib.h"
#include <iostream> 

/**
 * The graph data type that will plot points. 
*/
typedef struct  {
    Rectangle bounds; 
    Color color; 
    std::vector<float> dataValues; 
    } Graph; 

/*
 * Creates a graph that starts at position (x,y) with a width and a height. 
*/
Graph createGraph(float x, float y, float width, float height, Color color); 

/**
 * Draws the graph to the screen
*/
void drawGraph(Graph graph); 

/**
 * The textDisplay data type that will display sensor values. 
*/
typedef struct {
    Rectangle bounds; 
    Color color; 
    const char* text; 
} textDisplay; 

/**
 * Creates a text box with the given bounds, color, and text. 
*/
textDisplay createTextDisplay(float x, float y, float width, float height, Color color, const char* name); 

/**
 * Draws the text display 
*/
void drawTextDisplay(textDisplay textdisplay); 

class SensorDisplay {
    private:
    std::vector<Graph> graphs; 

    Graph elevationGraph; 
    Graph temperatureGraph; 

    std::vector<textDisplay> textdisplays; 

    textDisplay latitude; 
    textDisplay longitude; 
    textDisplay elevation;  
    textDisplay accel_x;
    textDisplay accel_y;
    textDisplay accel_z; 
    textDisplay gyro_x;
    textDisplay gyro_y;
    textDisplay gyro_z; 
    textDisplay mag_x; 
    textDisplay mag_y;
    textDisplay mag_z; 
    textDisplay temp; 

    int textDisplayWidth; 
    int textDisplayHeight; 
    int fontSize; 

    public: 
    /**
     * Initializes the displays. 
    */
    SensorDisplay(); 

    /**
     * Draws all of the displays. 
    */
   void drawComponents(); 

   /**
    * Update the sizes of boxes. 
   */
   void updateSizes(); 
}; 