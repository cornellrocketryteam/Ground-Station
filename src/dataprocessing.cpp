#include "dataprocessing.h"
#include <wiringPi.h>

#define RX 0
#define TX 1

std::unordered_map<std::string, float> SerialRead::serialValues;

/**
 * 6 bytes: Metadata
3 bits: flight mode
10 bits: Sensor statuses (2 bits each)
1 bit: SD state
1 bit: key armed
1 bit: altitude armed
4 bytes: timestamp
3 bytes: Events
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

void SerialRead::readPack(){
    if (wiringPiSetup() == -1) {
        std::cout << "Error initializing WiringPi." << std::endl;     
    }
    // Initializes the pins 
     pinMode(RX, INPUT); 
     pinMode(TX, OUTPUT); 

    // Will read from the RX pin and update the Map

    //BEGIN READ

    //TODO: Process the Metadata 
    u_int32_t metaData = digitalRead(RX); 

    float alt = digitalRead(RX); 
    float lat = digitalRead(RX); 
    float longi = digitalRead(RX); 
    float elev = digitalRead(RX); 
    float accelx = digitalRead(RX); 
    float accely = digitalRead(RX); 
    float accelz = digitalRead(RX); 
    float gyrox = digitalRead(RX); 
    float gyroy = digitalRead(RX); 
    float gyroz = digitalRead(RX); 
    float magx = digitalRead(RX); 
    float magy = digitalRead(RX); 
    float magz = digitalRead(RX); 

    serialValues["altitude"] = alt; 
    serialValues["latitude"] = lat; 
    serialValues["longitude"] = longi; 
    serialValues["elevation"] = elev; 
    serialValues["accel_x"] = accelx; 
    serialValues["accely"] = accely; 
    serialValues["accelz"] = accelz; 
    serialValues["gyro_x"] = gyrox; 
    serialValues["gyro_y"] = gyroy; 
    serialValues["gyro_z"] = gyroz; 
    serialValues["mag_x"] = magx; 
    serialValues["mag_y"] = magy; 
    serialValues["mag_z"] = magz; 
    
}

float bytesToFloat(std::byte b0, std::byte b1, std::byte b2, std::byte b3)
{
    float output;

    *((std::byte*)(&output) + 3) = b0;
    *((std::byte*)(&output) + 2) = b1;
    *((std::byte*)(&output) + 1) = b2;
    *((std::byte*)(&output) + 0) = b3;

    return output;
}
