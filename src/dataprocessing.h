#pragma once

#include <deque>
#include <iostream>
#include <map> 
#include <unordered_map>
#include <vector> 
#include <fstream>

class SerialRead {
    private: 
        std::unordered_map<std::string, float> serialValues;

        int serialPort; /*The serial port to read from*/

        std::ofstream flightDataFile; /*The file to write flight telemetry*/
    public:
        typedef enum WorkingState {WORKING, FAILURE} WorkingState; 

        typedef enum FlightMode {StartupMode, StandbyMode, AscentMode,DrogueDeployedMode, MainDeployedMode,FaultMode, Armed} FlightMode; 

        WorkingState AltimeterState; 
        WorkingState GpsState; 
        WorkingState IMUState; 
        WorkingState SDCardState; 
        WorkingState AccelerometerState;
        WorkingState TemperatureState;
        WorkingState RadioState; 

        FlightMode FlightState;

        void readPack();  /*Read the packet from RATS with pigpio*/

        float bytesToFloat(); /*Reads 4 bytes then converts to a float*/

        float getValue(std::string name); /*Gets the float value from the serialValues*/

        SerialRead(); /*Open the serial port /dev/ttyACM0*/

        ~SerialRead(); /*Close the serial port*/

        std::deque<float> elevationQueue; /*Stores the elevation points to graph*/


}; 
