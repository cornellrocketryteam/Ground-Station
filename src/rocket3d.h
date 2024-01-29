#include "raylib.h"
#include <iostream> 


class RocketModel {
    private:
        // the 3D camera 
        Camera3D camera; 

        // the rocket's representation 
        Vector3 rocketPosition; 

        float rocketWidth; 
        float rocketHeight; 
        float rocketLength; 

        //Rocket's models and textures. 
        Model rocketModel;
        Texture2D rocketTexture; 

        //Terrain model and textures
        Model terrainModel; 
        Texture2D terrainTexture; 

        // represents how big the map's grid will be 
        float mapSize; 

        float xRotation;
        float yRotation; 
        float zRotation; 


    public:
        /**
         * Draws the components and world of this 3D model. Does not include BeginDrawing() or EndDrawing(). 
        */
        void draw(); 

        /**
         * Initializes the size methods, the camera, and the rocket's position.
        */
       RocketModel(); 

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
       * Loads the terrain
      */
     void loadTerrain(); 

      /**
       * Unloads the terrain
      */
     void unloadTerrain(); 

      /**
       * Loads the rocket models and textures
      */
     void loadRocket(); 

      /**
       * Unloads the rocket models and textures
      */
     void unloadRocket(); 

}; 