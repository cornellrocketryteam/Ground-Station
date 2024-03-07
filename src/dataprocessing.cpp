#include "dataprocessing.h"
#include <iostream>
#include <fstream>

std::unordered_map<std::string, float> SerialRead::serialValues;

std::deque<float> SerialRead::elevationQueue; 

#define APPLE
#ifndef APPLE

#include <wiringPi>
#include <wiringSerial.h>

typedef unsigned char uchar;

int serial_port ; /* Serial port to read from */
char data; /* The data that we will read */

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
    return 1 ;
    }

    if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
    {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
    }

    if(serialDataAvail (serial_port) ){          
        u_char preAmble1 = serialGetchar (serial_port);	
        u_char preAmble2 = serialGetchar (serial_port);

        float timestamp = bytesToFloat(); 

        u_char events1  = serialGetchar (serial_port);	
        u_char events2  = serialGetchar (serial_port);	
        u_char events3  = serialGetchar (serial_port);	

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
    }
}

#endif 