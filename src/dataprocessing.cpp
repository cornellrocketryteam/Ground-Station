#include "dataprocessing.h"
#include <wiringPi.h>

#define RX 0
#define TX 1
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

void SerialRead::readPack(){
    //Checks if WiringPi was set up correctly 
    if (wiringPiSetup() == -1) {
        std::cout << "Error initializing WiringPi." << std::endl;     
    }
    // Initializes the pins 
     pinMode(RX, INPUT); 
     pinMode(TX, OUTPUT); 

    // Will read from the RX pin 
     while(1){
        int temp = digitalRead(RX); 
     }
    
}
// try (float) casting 
float bytesToFloat(std::byte b0, std::byte b1, std::byte b2, std::byte b3)
{
    float output;

    *((std::byte*)(&output) + 3) = b0;
    *((std::byte*)(&output) + 2) = b1;
    *((std::byte*)(&output) + 1) = b2;
    *((std::byte*)(&output) + 0) = b3;

    return output;
}

// FlightMode SerialRead::getFlightState(){
//     return FlightState; 
// }

// void SerialRead::initializeSensorEnums(){
//     AltimeterState = WORKING; 
//     GpsState = WORKING; 
//     IMUState = WORKING; 
//     SDCardState = WORKING; 
//     AccelerometerState = WORKING;
//     TemperatureState = WORKING;

//     FlightState = StartupMode;

// }