#include "raylib.h"
#include <iostream> 


class RocketModel {
    private:
        // the 3D camera 
        Camera3D camera; 

        // the rocket's representation 
        Vector3 rocketPosition; 

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

        Vector3 rocketModelCorner; // store the rocket model's corner

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

     /**
      * Draws the rocket's path of movement
     */
    void drawRocketPath(); 

    /**
     * updates the corners of the rocket's current position
    */
   void updateCorners(); 
}; 