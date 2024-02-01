#include "rocket3d.h"
#include "raymath.h"

RocketScreen::RocketScreen()
{
    //loadTerrain();
    terrainModel = LoadModel("GroundStation2.0/img/desert.obj");
    terrainTexture = LoadTexture("GroundStation2.0/img/as_ao.png");
    terrainModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = terrainTexture;

    //loadRocket();
    rocketModel = LoadModel("GroundStation2.0/img/rocketModel.obj");
    rocketTexture = LoadTexture("GroundStation2.0/img/rocket.png");
    rocketModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = rocketTexture;

    std::cout << "WORKING DIRECTORY = " << GetWorkingDirectory() << std::endl; 

    camera = { 0 };

    // initializes the camera's fields 
    camera.position = (Vector3){ 30.0f, 15.0f, 30.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 5.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; 

    // the rocket's initial position 
    rocketPosition = { 0.0f, 2.0f, 0.0f };

    // sets the size of the map 
    mapSize = 1000.0f; 

    // 270 is used to make the rocket vertical. 
    xRotation = 270;
    yRotation = 0; 
    zRotation = 0; 
}

RocketScreen::~RocketScreen()
{
    UnloadModel(terrainModel);
    UnloadTexture(terrainTexture);
    UnloadModel(rocketModel);
    UnloadTexture(rocketTexture);
}


/**
 * Drawing methods for the rocket
*/
void RocketScreen::draw()
{
    BeginMode3D(camera);
        // rotates the rocket. 
        rocketModel.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*xRotation, DEG2RAD*yRotation, DEG2RAD*zRotation });
        
        //Draw the model of the rocket
        DrawModel(rocketModel, rocketPosition,0.01f,WHITE); 
        DrawModel(terrainModel,(Vector3){0,-10,0},50.0f,WHITE); 

        //Draw the path of the rocket
        drawRocketPath();

        moveRocket(); 
    EndMode3D();

}


void RocketScreen::drawRocketPath()
{
    // TODO: Fix this to push back only the Corners
    //pathPositions.push_back(rocketPosition); 
    pathPositions.push_back(rocketPosition);

    // Draws all of the past path positions
    for (auto i : pathPositions){
        DrawSphere(i,0.15,RED); 
    }
}

/**
 * Movement functions for the rocket
*/

void RocketScreen::moveRocket()
{
    if (IsKeyDown(KEY_UP)){
        rocketPosition.y += 1; 
        camera.position.y += 1;
        camera.target.y += 1; 
    } else if (IsKeyDown(KEY_DOWN)){
        rocketPosition.y -= 1; 
        camera.position.y -= 1;
        camera.target.y -= 1;
    } else if (IsKeyDown(KEY_LEFT)){
        xRotation += 1; 
    } else if (IsKeyDown(KEY_RIGHT)){
        yRotation += 1; 
    } else if (IsKeyDown(KEY_SPACE)){
        zRotation += 1; 
    }
}

void RocketScreen::resetRocketPosition()
{
    rocketPosition.x = 0.0; 
    rocketPosition.y = 0.0; 
    rocketPosition.z = 0.0; 

    camera.position.x = 0.0; 
    camera.position.y = 0.0; 
    camera.position.z = 0.0; 

    xRotation = 270; 
    yRotation = 0;
    zRotation = 0; 

    pathPositions.clear();
}


/**
 * The loading and unloading methods for models and textures
*/
std::string RocketScreen::getRocketElevation()
{
    return "Elevation: " + std::to_string(rocketPosition.y);
}

void RocketScreen::displayRocketTexts()
{
    DrawText(getRocketElevation().c_str(),1300,900,25,BLACK);
}
