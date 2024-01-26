#include "rocket3d.h"

RocketModel::RocketModel(){
    camera = { 0 };

    // initializes the camera's fields 
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; 

    // the rocket's initial position 
    rocketPosition = { 0.0f, 0.0f, 0.0f };

    // the rocket's width, height, and length 
    rocketWidth = 1.0f;
    rocketHeight = 4.0f; 
    rocketLength = 1.0f; 

    // sets the size of the map 
    mapSize = 100.0f; 

}

void RocketModel::draw(){
    BeginMode3D(camera);

        DrawCube(rocketPosition,rocketWidth , rocketHeight, rocketLength, RED);

        DrawGrid(mapSize, 1.0f);

    EndMode3D();
}