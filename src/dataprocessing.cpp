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

For the EVENTS:
0: Key armed
1: Altitude armed
2: Alt init failed
3: Alt reading failed
4: Alt turned off
5: IMU init failed
6: IMU reading failed
7: IMU turned off
8: Accel init failed
9: Accel reading failed
10: Accel turned off
11: Therm init failed
12: Therm reading failed
13: Therm turned off
14: SD init failed
15: SD write failed
16: RFM init failed
17: RFM transmit failed

0 means false, 1 means true 
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

    //3 Bytes of MetaData
    u_int8_t metaData1 = digitalRead8(RX); 
    u_int8_t metaData2 = digitalRead8(RX); 

    // Test the right-most bit of metaData1
    for (int i = 0; i < 8; i++){
        if (metaData1 & 0x01){
            // rightmost bit is 1
        }
        metaData1 = metaData1 >> 1; 
    }

    // Test the right-most bit of metaData2
    for (int i = 0; i < 8; i++){
        if (metaData2 & 0x01){
            // rightmost bit is 1
        }
        metaData2 = metaData2 >> 1; 
    }

    float timestamp = digitalRead8(RX); 

    //3 Bytes of Events
    u_int8_t Events1 = digitalRead8(RX); 
    u_int8_t Events2 = digitalRead8(RX); 
    u_int8_t Events3 = digitalRead8(RX); 

    // Test the right-most bit of Events1
    for (int i = 0; i < 8; i++){
        if (Events1 & 0x01){
            // rightmost bit is 1
        }
        Events1 = Events1  >> 1; 
    }

    // Test the right-most bit of Events2
    for (int i = 0; i < 8; i++){
        if (Events2 & 0x01){
            // rightmost bit is 1
        }
        Events2 = Events2 >> 1; 
    }

    // Test the right-most bit of Events3
    for (int i = 0; i < 8; i++){
        if (Events3 & 0x01){
            // rightmost bit is 1
        }
        Events3 = Events3 >> 1; 
    }

    // Read the flaot values 
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
    serialValues["timestamp"] = timestamp; 
    
}

