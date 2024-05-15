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
};