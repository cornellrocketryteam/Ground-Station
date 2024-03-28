#pragma once

#include "raylib.h"
#include <iostream>
#include <vector>

class Rocket {
public:
    Rocket();
    ~Rocket();

    /**
     * Draws the components and world of this 3D model. Does not include BeginDrawing() or EndDrawing().
    */
    void draw(int posX, int posY, int width, int height);

    /**
     * moves the Rocket based on data
    */
    void processEvents();

    /**
     * Returns a string of the Rocket's elevation in the format "Elevation: x"
    */
    std::string getRocketElevation();

    /**
     * Displays all of the necessary rocket text information
    */
    void displayRocketTexts();

    /**
     * Draws the rocket's path of movement
    */
    void drawRocketPath();
    /**
     * Returns if the display is enlarged 
    */
    bool isEnlarged(); 

private:
    // the 3D camera
    Camera3D camera;

    // the rocket's representation
    Vector3 rocketPosition;

    // the terrain position
    Vector3 terrainPosition; 

    //Rocket's models and textures.
    Model rocketModel;
    Texture2D rocketTexture;

    //Terrain model and textures
    Model terrainModel;
    Texture2D terrainTexture;

    bool enlarged = false; 

    // represents how big the map's grid will be
    float mapSize;

  // The rotation angles of the rocket in degrees
    float xRotation;
    float yRotation;
    float zRotation;

    float cameraXAdded; 
    float cameraYAdded;
    float cameraZAdded; 

  /**
   * Used to determine when a click should be registered
  */
    float drawnX; 
    float drawnY; 
    float drawnWidth; 
    float drawnHeight; 
};