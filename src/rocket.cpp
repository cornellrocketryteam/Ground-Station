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

    // sets the size of the map
    mapSize = 1000.0f;

    // 270 is used to make the rocket vertical.
    xRotation = 270;
    yRotation = 0;
    zRotation = 0;

    //loadTerrain();
    terrainModel = LoadModel("img/desert.obj");
    terrainTexture = LoadTexture("img/as_ao.png");
    terrainModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = terrainTexture;

    //loadRocket();
    rocketModel = LoadModel("img/rocketModel.obj");
    rocketTexture = LoadTexture("img/rocket.png");
    rocketModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = rocketTexture;
}

Rocket::~Rocket()
{
    UnloadModel(terrainModel);
    UnloadTexture(terrainTexture);
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

            drawnX = posX; 
            drawnY = posY; 
            drawnWidth = width; 
            drawnHeight = height; 

            // rotates the rocket.
            rocketModel.transform = MatrixRotateXYZ({ DEG2RAD*xRotation, DEG2RAD*yRotation, DEG2RAD*zRotation });

            //Draw the model of the rocket when ENLARGED
            if (enlarged){
                // Reset the camera position  
                camera.position = (Vector3){ 0.0f, 15.0f + cameraYAdded, 30.0f};
                camera.target = (Vector3){ 0.0f, 5.0f+ cameraYAdded, 0.0f }; 

                // Clear the screen 
                ClearBackground({56, 55, 52});

                DrawModel(rocketModel, rocketPosition, 0.008f, WHITE);
                DrawModel(terrainModel, terrainPosition, 50.0f, WHITE);

            } else {
                //Draw the UN-ENLARGED rocket
                camera.position = (Vector3){-6.0f, 5.0f+ cameraYAdded, 30.0f}; 
                camera.target = (Vector3){-7.0f, -4.5f + cameraYAdded, 0.0f}; 

                DrawModel(rocketModel, rocketPosition, 0.003f, WHITE);
                DrawModel(terrainModel, terrainPosition, 25.0f, WHITE);
            }
        EndMode3D();
    EndScissorMode();
}

/**
 * Movement functions for the rocket
*/

void Rocket::processEvents()
{
    // if (IsKeyDown(KEY_UP)){
    //     rocketPosition.y += 1; 
    //     cameraYAdded += 1; 
    // } else if (IsKeyDown(KEY_DOWN)){
    //     rocketPosition.y -= 1; 
    //     cameraYAdded -= 1; 
    // } else if (IsKeyDown(KEY_LEFT)){
    //     xRotation += 1; 
    // } else if (IsKeyDown(KEY_RIGHT)){
    //     yRotation += 1; 
    // } else if (IsKeyDown(KEY_SPACE)){
    //     zRotation += 1; 
    // }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        float mouseX = GetMousePosition().x;
        float mouseY = GetMousePosition().y;

        // Make sure the mouse click is in bounds
        if (mouseX >= drawnX && mouseX <= drawnX + drawnWidth && mouseY >= drawnY && mouseY <= drawnY + drawnHeight){
            if (isEnlarged()){
                enlarged = false;
            } else {
                enlarged = true;
            }
            // Wait to stop constant key press
            WaitTime(0.1);
        }
    }
    cameraYAdded = sfr::serialRead->getValue("Altitude"); 
    rocketPosition.y = sfr::serialRead->getValue("Altitude"); 

    // TODO: Process longitude and latitude data for our model 
    
    //TODO: Process Orientation data for our model 
    // Check which Axis are being used 
    xRotation = sfr::serialRead->getValue("Orientation X"); 
    yRotation = sfr::serialRead->getValue("Orientation Z"); 
    zRotation = sfr::serialRead->getValue("Orientation Y"); 

    
}

/**
 * The loading and unloading methods for models and textures
*/
std::string Rocket::getRocketElevation()
{
    return "Elevation: " + std::to_string(rocketPosition.y);
}

void Rocket::displayRocketTexts()
{
    DrawText(getRocketElevation().c_str(),1300,900,25,BLACK);
}

bool Rocket::isEnlarged(){
    return enlarged; 
}
