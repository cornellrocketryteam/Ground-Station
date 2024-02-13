#pragma once

#include <iostream>
#include <map> 
#include <unordered_map>

/**
 * The enumeration that will allow a failure mode in case the altimeter fails.
*/
typedef enum ElevationState { ELEVATION_SUCESS, ELEVATION_FAILURE} ElevationState; 
/**
 * The enumeration that will allow a failure mode in case the GPS fails.
*/
typedef enum GPSState { GPS_SUCCESS, GPS_FAILURE} GPSState; 
/**
 * The type of the package
*/
typedef unsigned char uchar;

/**
 * Converts 4 unsigned char bytes to a float value 
*/
float bytesToFloat(uchar b0, uchar b1, uchar b2, uchar b3);


/**
 * The Class that stores the static member function that will read serial data, and then
 * update the serialValues map with said data for the GUI's components to draw accurately. 
*/
class SerialRead {
    private: 
        /**
         * Byte array that we will have to unpack 
        */
       static uchar package[56]; 

        /**
         * Will represent the current altimeter state 
        */
       ElevationState elevationState; 
        /**
         * Will represent the current GPS state
        */
       GPSState gpsState; 
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