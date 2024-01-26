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

        // represents how big the map's grid will be 
        float mapSize; 

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
}; 