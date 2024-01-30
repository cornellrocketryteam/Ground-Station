#include "dataprocessing.h"

// define the static member serialValues
std::map<std::string, float> SerialRead::serialValues;  


void SerialRead::updateSerialValues(){

    SerialRead::serialValues["latitude"] = 0; 
    SerialRead::serialValues["longitude"] = 0; 
    SerialRead::serialValues["elevation"] = 0; 
    SerialRead::serialValues["accel_x"] = 0; 
    SerialRead::serialValues["accel_y"] = 0; 
    SerialRead::serialValues["accel_z"] = 0; 
    SerialRead::serialValues["gyro_x"] = 0; 
    SerialRead::serialValues["gyro_y"] = 0; 
    SerialRead::serialValues["gyro_z"] = 0; 
    SerialRead::serialValues["mag_x"] = 0; 
    SerialRead::serialValues["mag_y"] = 0; 
    SerialRead::serialValues["mag_z"] = 0; 
    SerialRead::serialValues["temp"] = 0; 
}