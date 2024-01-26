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

        //DrawCube(rocketPosition,rocketWidth , rocketHeight, rocketLength, RED);
        DrawCylinder(rocketPosition,0.01,0.5,5,10,RED);
        DrawGrid(mapSize, 1.0f);

        moveRocket(); 

    EndMode3D();
}

void RocketModel::moveRocket(){
    if (IsKeyDown(KEY_UP)){
        rocketPosition.y += 1; 
        camera.position.y += 1;
        camera.target.y += 1; 
    } else if (IsKeyDown(KEY_DOWN)){
        rocketPosition.y -= 1; 
        camera.position.y -= 1;
        camera.target.y -= 1;
    }
}

void RocketModel::resetRocketPosition(){
    rocketPosition.x = 0.0; 
    rocketPosition.y = 0.0; 
    rocketPosition.z = 0.0; 

    camera.position.x = 0.0; 
    camera.position.y = 0.0; 
    camera.position.z = 0.0; 
}