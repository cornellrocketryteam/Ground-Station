#include "dataprocessing.h"
#include <iostream>
#include <fstream>

std::unordered_map<std::string, float> SerialRead::serialValues;

std::deque<float> SerialRead::elevationQueue; 

WorkingState AltimeterState = WORKING; 
WorkingState GpsState = WORKING; 
WorkingState IMUState = WORKING; 
WorkingState SDCardState = WORKING; 
WorkingState AccelerometerState = WORKING;
WorkingState TemperatureState = WORKING;
WorkingState RadioState = WORKING; 

FlightMode FlightState = StartupMode;

#define APPLE
#ifndef APPLE

#include <wiringPi.h>
#include <wiringSerial.h>

typedef unsigned char uchar;

int serial_port ; /* Serial port to read from */
char data; /* The data that we will read */

/*
Reads 4 unsigned characters from the serial port, and then converts those bytes 
into a float. 
*/
float bytesToFloat()
{
    float output;

    uchar b0 = serialGetchar (serial_port);
    uchar b1 = serialGetchar (serial_port);
    uchar b2 = serialGetchar (serial_port);
    uchar b3 = serialGetchar (serial_port);

    *((uchar*)(&output) + 3) = b0;
    *((uchar*)(&output) + 2) = b1;
    *((uchar*)(&output) + 1) = b2;
    *((uchar*)(&output) + 0) = b3;

    return output;
}

void SerialRead::readPack(){
    if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)	/* open serial port */
    {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    }

    if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
    {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    }

    if(serialDataAvail (serial_port) ){          
        u_char preAmble1 = serialGetchar (serial_port);	
        for (int i = 1; i <= 8; i++){
            if (preAmble1 & 0x01){
                switch(i) {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                }
            }
            preAmble1 >> 1; 
        }

        u_char preAmble2 = serialGetchar (serial_port);
        for (int i = 1; i <= 8; i++){
            if (preAmble2 & 0x01){
                switch(i) {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6: SDCardState = FAILURE; 
                    case 7: 
                    case 8:
                }
            }
            preAmble2 >> 1; 
        }

        float timestamp = bytesToFloat(); 

        u_char events1  = serialGetchar (serial_port);
        for (int i = 1; i <= 8; i++){
            if (events1 & 0x01){
                switch(i) {
                    case 1:
                    case 2:
                    case 3:AltimeterState = FAILURE; 
                    case 4:AltimeterState = FAILURE; 
                    case 5:AltimeterState = FAILURE; 
                    case 6:IMUState = FAILURE;
                    case 7:IMUState = FAILURE; 
                    case 8:IMUState = FAILURE; 
                }
            }
            events1 >> 1; 
        }

        u_char events2  = serialGetchar (serial_port);	
        for (int i = 1; i <= 8; i++){
            if (events2 & 0x01){
                switch(i) {
                    case 1:AccelerometerState = FAILURE; 
                    case 2:AccelerometerState = FAILURE; 
                    case 3:AccelerometerState = FAILURE; 
                    case 4:TemperatureState = FAILURE;
                    case 6:TemperatureState = FAILURE;
                    case 7:TemperatureState = FAILURE;
                    case 8:SDCardState = FAILURE; 
                }
            }
            events2 >> 1; 
        }

        u_char events3  = serialGetchar (serial_port);	
        for (int i = 1; i <= 8; i++){
            if (events3 & 0x01){
                switch(i) {
                    case 1:SDCardState = FAILURE;
                    case 2:RadioState = FAILURE;
                    case 3:RadioState = FAILURE; 
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                }
            }
            events3 >> 1; 
        }

        float alt = bytesToFloat();
        float lat = bytesToFloat();
        float longi = bytesToFloat();
        float elev = bytesToFloat();
        float accelx = bytesToFloat();
        float accely = bytesToFloat();
        float accelz = bytesToFloat();
        float gyrox = bytesToFloat();
        float gyroy = bytesToFloat();
        float gyroz = bytesToFloat();
        float magx = bytesToFloat();
        float magy = bytesToFloat();
        float magz = bytesToFloat();

        SerialRead::serialValues["longitude"] = longi; 
        SerialRead::serialValues["latitude"] = lat; 
        SerialRead::serialValues["altitude"] = alt; 
        SerialRead::serialValues["elevation"] = elev; 
        SerialRead::serialValues["gyro_x"] = gyrox; 
        SerialRead::serialValues["gyro_y"] = gyroy; 
        SerialRead::serialValues["gyro_z"] = gyroz; 
        SerialRead::serialValues["accel_x"] = accelx; 
        SerialRead::serialValues["accel_y"] = accely; 
        SerialRead::serialValues["accel_z"] = accelz; 
        SerialRead::serialValues["mag_x"] = magx;
        SerialRead::serialValues["mag_y"] = magy; 
        SerialRead::serialValues["mag_z"] = magz;
        SerialRead::serialValues["timestamp"] = timestamp; 
    }
}

#endif 