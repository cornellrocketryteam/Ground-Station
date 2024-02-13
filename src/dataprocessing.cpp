#include "dataprocessing.h"

/**
Format of Data to unpack:

56 bytes in total
6 bytes: Metadata
3 bits: flight mode
10 bits: Sensor statuses (2 bits each)
1 bit: SD state
1 bit: key armed
1 bit: altitude armed
4 bytes: timestamp
2 bytes: Events
(Will come up with enumeration)
52 bytes: Sensor readings (4 bytes each)
Altitude
Latitude
Longitude
Elevation
Accel X
Accel Y
Accel Z
Gyro X
Gyro Y
Gyro Z
Mag X
Mag Y
Mag Z 
*/




std::unordered_map<std::string, float> SerialRead::serialValues;

// Need to read in data from the package 
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

void SerialRead::setPack(){

}

float bytesToFloat(uchar b0, uchar b1, uchar b2, uchar b3)
{
    float output;

    *((uchar*)(&output) + 3) = b0;
    *((uchar*)(&output) + 2) = b1;
    *((uchar*)(&output) + 1) = b2;
    *((uchar*)(&output) + 0) = b3;

    return output;
}
