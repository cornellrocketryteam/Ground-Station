#include "dataprocessing.h"
#include <iostream>
#include <fstream>

#define RX 0
#define TX 1

std::unordered_map<std::string, float> SerialRead::serialValues;

std::deque<float> SerialRead::elevationQueue; 

#define APPLE 
#ifndef APPLE 
#include <wiringPi.h>


// The file which we will write Data to 
std::fstream writeFile("data/flightData.txt", std::ios::out); 

// Initialize all sensors to working 
WorkingState AltimeterState = WORKING;
WorkingState GpsState = WORKING;
WorkingState IMUState = WORKING;
WorkingState SDCardState = WORKING;
WorkingState AccelerometerState = WORKING; 
WorkingState TemperatureState = WORKING; 
WorkingState RadioState = WORKING;

FlightMode FlightState = StartupMode; 

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

    for (int i = 0; i < 8; i++){
        if (metaData1 & 0x01){
            switch(i){
                case 0: // Flight Mode
                case 1: // Flight Mode
                case 2: // Flight Mode
                case 3: // Do 3 -> 7 matter, because we are getting event data?
                case 4:
                case 5:
                case 6:
                case 7: 
            }
        }
        metaData1 = metaData1 >> 1; 
    }

    for (int i = 0; i < 8; i++){
        if (metaData2 & 0x01){
            switch(i){
                case 0: 
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7: 
            }
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
            switch(i){
                case 0: //IMUState = FAILURE; 
                case 1: //IMUState = FAILURE; 
                case 2: //IMUState = FAILURE; 
                case 3: //AltimeterState = FAILURE; 
                case 4: //AltimeterState = FAILURE; 
                case 5: //AltimeterState = FAILURE; 
                case 6: // When altitude is armed 
                case 7: // When key is armed 
            }
        }
        Events1 = Events1  >> 1; 
    }

    // Test the right-most bit of Events2
    for (int i = 0; i < 8; i++){
        if (Events2 & 0x01){
            switch(i){
                case 0: //SDCardState = FAILURE; 
                case 1: //SDCardState = FAILURE; 
                case 2: //TemperatureState = FAILURE; 
                case 3: //TemperatureState = FAILURE; 
                case 4: //TemperatureState = FAILURE; 
                case 5: //AccelerometerState = FAILURE;
                case 6: //AccelerometerState = FAILURE; 
                case 7: //AccelerometerState = FAILURE;
            }
        }
        Events2 = Events2 >> 1; 
    }

    // Test the right-most bit of Events3
    for (int i = 0; i < 8; i++){
        if (Events3 & 0x01){
            switch(i){
                // 0 through 5 are unimportant 
                case 6: //RadioState = FAILURE; 
                case 7: //RadioState = FAILURE; 
            }
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

    // If the queue does not yet have 300 elements, then do not remove anything 
    if (elevationQueue.size() < 300){
        elevationQueue.push_back(timestamp); 
    } else {
    // Once 300 elements have been reached, begin to take off oldest element and add newest element 
        elevationQueue.pop_front(); 
        elevationQueue.push_back(timestamp); 
    }
    
}
#endif
