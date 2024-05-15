#include "rocket.h"
#include "raymath.h"
#include "sfr.h"

Rocket::Rocket() {
    camera = { 0 };

    // initializes the camera's fields
    camera.position = (Vector3){ 30.0f, 15.0f, 30.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 5.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; 

    // the rocket's initial position
    rocketPosition = { 0.0f, 2.0f, 0.0f };
    terrainPosition = {0.0, -10,0}; 

    //loadRocket();
    rocketModel = LoadModel("img/rocketModel.obj");
    rocketTexture = LoadTexture("img/rocket.png");
    rocketModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = rocketTexture;
}

Rocket::~Rocket()
{
    UnloadModel(rocketModel);
    UnloadTexture(rocketTexture);
}

/**
 * Drawing methods for the rocket
*/
void Rocket::draw(int posX, int posY, int width, int height)
{
    BeginScissorMode(posX, posY, width, height);
        BeginMode3D(camera);
            //TODO: Process Orientation data for our model
            // Check which Axis are being used
            // 270 is used to make the rocket vertical.
            float xRotation = 270 + sfr::serialRead->oriX;
            float yRotation = sfr::serialRead->oriZ;
            float zRotation = sfr::serialRead->oriY;
            rocketModel.transform = MatrixRotateXYZ({ DEG2RAD*xRotation, DEG2RAD*yRotation, DEG2RAD*zRotation });

            camera.position = (Vector3){-6.0f, 5.0f, 30.0f};
            camera.target = (Vector3){-7.0f, -4.5f, 0.0f};
            DrawModel(rocketModel, rocketPosition, 0.003f, WHITE);
        EndMode3D();
    EndScissorMode();
}
