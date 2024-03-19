#include "dataprocessing.h"
#include <iostream>
#include <fstream>


//#define APPLE
#ifndef APPLE
#include <pigpio.h> 

SerialRead::SerialRead(){
    if (gpioInitialise() < 0){
            printf("Pigpio not initialized."); 
    } else {
            printf("Pigpio succesffuly initialized.");
    }
    
    serialPort = serOpen("/dev/ttyACM0",9600,0); 

    if (serialPort< 0) { /* open serial port */
        printf ("Unable to open serial device") ;
    } else {
        printf("Opened serial port"); 
    }

    AltimeterState = FAILURE; 
    GpsState = FAILURE; 
    IMUState = FAILURE;  
    SDCardState = FAILURE; 
    AccelerometerState = FAILURE; 
    TemperatureState = FAILURE; 
    RadioState = FAILURE;  
    FlightState = StartupMode; 
}

SerialRead::~SerialRead(){
    serClose(serialPort); 

    gpioTerminate();
}

float SerialRead::getValue(std::string name){
    return serialValues[name]; 
}

float SerialRead::bytesToFloat()
{
    float output;
    char data[4]; 
    serRead(serialPort,data,4); 

    output = atof(data); 

    return output;
}

void SerialRead::readPack(){ 
    if(serDataAvailable (serialPort) ){          
        char preamble[2];

        char events1[1];
        char events2[1];
        char events3[1]; 
        
        serRead(serialPort,preamble,2); 

        u_int8_t sumOfFlightStatus; 

        for (int i = 0; i < 8; i++){
            if (0x01 & preamble[0]){
                switch(i){
                    case 0: AltimeterState = WORKING; 
                    case 1: GpsState = WORKING; 
                    case 2: SDCardState = WORKING; 
                    case 3: TemperatureState = WORKING; 
                    case 4: TemperatureState = FAILURE; 
                    case 5: AccelerometerState = WORKING; 
                    case 6: AccelerometerState = FAILURE;
                    case 7: IMUState = WORKING; 
                }
                preamble[0] >> 1; 
            }
        }
        u_int8_t sumOfFlightStatus; 
        for (int i = 8; i < 16; i++){
            if (0x01 & preamble[1]){
                switch(i){
                    case 8: IMUState = FAILURE; 
                    case 9: GpsState = WORKING; 
                    case 10: GpsState = FAILURE; 
                    case 11: AltimeterState = WORKING; 
                    case 12: AltimeterState = FAILURE; 
                    case 13: sumOfFlightStatus += 4;
                    case 14: sumOfFlightStatus += 2; 
                    case 15: sumOfFlightStatus += 1; 
                }
                preamble[1] >> 1; 
            }
        }
        /*Process the bytes for flight status */
        switch(sumOfFlightStatus){
            case 0: FlightState = StartupMode; 
            case 1: FlightState = StandbyMode; 
            case 2: FlightState = AscentMode; 
            case 3: FlightState = DrogueDeployedMode; 
            case 4: FlightState = MainDeployedMode; 
            case 5: FlightState = FaultMode; 
        }

        float timestamp = bytesToFloat(); 

        serRead(serialPort,events1,1); 
        serRead(serialPort,events2,1); 
        serRead(serialPort,events3,1); 

        float alt = bytesToFloat();
        float lat = bytesToFloat();
        float longi = bytesToFloat();

        float satInView = bytesToFloat(); 

        float accelx = bytesToFloat();
        float accely = bytesToFloat();
        float accelz = bytesToFloat();

        float gyrox = bytesToFloat();
        float gyroy = bytesToFloat();
        float gyroz = bytesToFloat();

        float accelXIMU = bytesToFloat(); 
        float accelYIMU = bytesToFloat(); 
        float accelZIMU = bytesToFloat(); 

        float oriX = bytesToFloat(); 
        float oriY = bytesToFloat(); 
        float oriZ = bytesToFloat(); 

        float magx = bytesToFloat();
        float magy = bytesToFloat();
        float magz = bytesToFloat();

        float temp = bytesToFloat(); 

        serialValues["longitude"] = longi; 
        serialValues["latitude"] = lat; 
        serialValues["altitude"] = alt; 
        serialValues["gyro_x"] = gyrox; 
        serialValues["gyro_y"] = gyroy; 
        serialValues["gyro_z"] = gyroz; 
        serialValues["accel_x"] = accelx; 
        serialValues["accel_y"] = accely; 
        serialValues["accel_z"] = accelz; 
        serialValues["mag_x"] = magx;
        serialValues["mag_y"] = magy; 
        serialValues["mag_z"] = magz;
        serialValues["timestamp"] = timestamp; 

    } else {
        printf("Serial port not available, could not read"); 
    }
    
}

#endif 

