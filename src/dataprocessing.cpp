#include "dataprocessing.h"

std::unordered_map<std::string, float> SerialRead::serialValues;

void SerialRead::updateSerialValues()
{
    serialValues["latitude"] = 0;
    serialValues["longitude"] = 0;
    serialValues["elevation"] = 0;
    serialValues["accel_x"] = 0;
    serialValues["accel_y"] = 0;
    serialValues["accel_z"] = 0;
    serialValues["gyro_x"] = 0;
    serialValues["gyro_y"] = 0;
    serialValues["gyro_z"] = 0;
    serialValues["mag_x"] = 0;
    serialValues["mag_y"] = 0;
    serialValues["mag_z"] = 0;
    serialValues["temp"] = 0;
}