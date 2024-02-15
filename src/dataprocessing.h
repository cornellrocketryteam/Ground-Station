#pragma once

#include <iostream>
#include <map> 
#include <unordered_map>
#include <vector> 


/**
 * TODO: Log sensor Data in SD card 
*/
/**
 * Will represent is a sensor is working or failing. If a sensor is failing, it is 
 * in fail mode, and we will display "FAILURE" for that sensor. 
*/
typedef enum WorkingState {WORKING, FAILURE} WorkingState; 

/**
 * Converts 4 unsigned char bytes to a float value 
*/
float bytesToFloat(std::byte b0, std::byte b1, std::byte b2, std::byte b3); 


/**
 * The Class that stores the static member function that will read serial data, and then
 * u pdate the serialValues map with said data for the GUI's components to draw accurately. 
*/
class SerialRead {
    private: 
        /**
         * Byte array that we will have to unpack 
        */
       static std::byte package[56]; 

        /**
         * Will represent the current altimeter state 
        */
       WorkingState elevationState; 
        /**
         * Will represent the current GPS state
        */
       WorkingState gpsState; 

        
    public: 
        /**
         * Stores the values that are read from RATS. 
        */
        static std::unordered_map<std::string, float> serialValues;
        /**
         * Updates the serialValues map by reading in data from the package 
        */
        static void updateSerialValues(); 
        /**
         * Will set the package received from RATS to be the [package] member 
         * via reading serial data  
        */
        static void setPack();  
        

}; 