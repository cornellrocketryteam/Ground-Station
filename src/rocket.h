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
    void moveRocket();

    /**
     * Reset the rocket position
    */
    void resetRocketPosition();

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


    // represents how big the map's grid will be
    float mapSize;

  // The rotation angles of the rocket in degrees
    float xRotation;
    float yRotation;
    float zRotation;

    // vector to store the past positions of the rocket for drawing
    std::vector<Vector3> pathPositions;
};