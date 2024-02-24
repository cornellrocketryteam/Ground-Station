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
 * Flight Mode State
*/
typedef enum FlightMode {StartupMode, StandbyMode, AscentMode,DrogueDeployedMode, MainDeployedMode,FaultMode} FlightMode; 

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
         * Will represent the states of each sensor, six in total
        */
       static WorkingState AltimeterState; 
       static WorkingState GpsState; 
       static WorkingState IMUState; 
       static WorkingState SDCardState; 
       static WorkingState AccelerometerState;
       static WorkingState TemperatureState;

       static FlightMode FlightState;

    public: 
        /**
         * Stores the values that are read from RATS. 
        */
        static std::unordered_map<std::string, float> serialValues;
        /**
         * Will read the package received from RATS to be the [package] member 
         * via reading serial data  
        */
        static void readPack();  
        /**
         * Return the current FlightState
        */
        static FlightMode getFlightState();
        /**
         * Initializes the enumerations for sensors 
        */
       //static void initializeSensorEnums(); 

}; 