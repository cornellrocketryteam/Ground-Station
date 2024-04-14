#include "serialread.h"
#include <stdio.h> 
#include <cstring> 
#include <iostream>

#ifndef __APPLE__
#include <pigpio.h>
#endif

SerialRead::SerialRead(){
#ifndef __APPLE__
    // if (gpioInitialise() < 0){
    //         printf("Pigpio not initialized.\n"); 
    // } else {
    //         printf("Pigpio succesffuly initialized.\n");
    // }

    // serialPort = serOpen("/dev/ttyACM0",115200,0);

    // if (serialPort< 0) { /* open serial port */
    //     printf ("Unable to open serial device\n") ;
    // } else {
    //     printf("Opened serial port\n"); 
    // }
#endif

    flightDataFile.open("data/flightData.txt",std::ios::out);
}

SerialRead::~SerialRead(){
    flightDataFile.close();

#ifndef __APPLE__
    // serClose(serialPort);
    // gpioTerminate();
#endif
}

float SerialRead::getValue(std::string name){
    return serialValues[name]; 
}

// template <typename T>
// T readType(char* data)
// {
//     T output;
//     memcpy(&output, data, sizeof(T));
//     return output;
// }

float converter(char* packet){
    float temp; 

    memcpy(&temp,packet,sizeof(temp)); 
    return temp;
}

uint32_t converterINT32(char* packet){
    uint32_t temp; 

    memcpy(&temp,packet,sizeof(temp)); 
    return temp;
}


void printByte(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        if (byte & (0b1 << i)) {
            std::cout << "1";
        } else {
            std::cout << "0";
        }
    }
    std::cout << std::endl;
}


void SerialRead::readPacket() {
    unsigned char packet[86];
    FILE *ptr;

    ptr = fopen("/dev/cu.usbmodem101","rb");  // r for read, b for binary

    if (ptr != nullptr) {

        fread(packet,sizeof(packet),1,ptr); // read 86 bytes to our buffer

            printf("Metadata Byte 1: "); 
            printByte(packet[0]); 

            printf("Metadata Byte 2: "); 
            printByte(packet[1]); 

            uint32_t timestamp = converterINT32((char*)&packet[2]); 
            printf ("%s%i%s", "Time Stamp: ",timestamp, "\n");

            printf("Events Byte 1: "); 
            printByte(packet[6]);

            printf("Events Byte 2: "); 
            printByte(packet[7]);

            printf("Events Byte 3: "); 
            printByte(packet[8]);

            float alt = converter((char*)&packet[9]);
            printf ("%s%f%s", "Altitude: ",alt, "\n");

            float lat = converter((char*)&packet[13]);
            printf ("%s%f%s", "Latitude: ",lat, "\n");

            float longi = converter((char*)&packet[17]);
            printf ("%s%f%s","Longitude: ", longi, "\n");

            float accelX = converter((char*)&packet[22]);
            printf ("%s%f%s", "Accel X: ", accelX, "\n");

            float accelY = converter((char*)&packet[26]);
            printf ("%s%f%s","Accel Y: ", accelY, "\n");

            float accelZ = converter((char*)&packet[30]);
            printf ("%s%f%s","Accel Z: ", accelZ, "\n");

            float gyroX = converter((char*)&packet[34]);
            printf ("%s%f%s", "Gyro X: ", gyroX, "\n");

            float gyroY = converter((char*)&packet[38]);
            printf ("%s%f%s", "Gyro Y: ", gyroY, "\n");

            float gyroZ = converter((char*)&packet[42]);
            printf ("%s%f%s", "Gyro Z: ", gyroZ, "\n");

            float accelXIMU = converter((char*)&packet[46]);
            printf ("%s%f%s","Accel X IMU: ", accelXIMU, "\n");

            float accelYIMU = converter((char*)&packet[50]);
            printf ("%s%f%s", "Accel Y IMU: ",accelYIMU, "\n");

            float accelZIMU = converter((char*)&packet[54]);
            printf ("%s%f%s","Accel Z IMU: ",  accelZIMU, "\n");

            float oriX = converter((char*)&packet[58]);
            printf ("%s%f%s", "Ori X: ", oriX, "\n");

            float oriY = converter((char*)&packet[62]);
            printf ("%s%f%s", "Ori Y: ", oriY, "\n");

            float oriZ = converter((char*)&packet[66]);
            printf ("%s%f%s", "Ori Z: ", oriZ, "\n");

            float gravityX = converter((char*)&packet[70]);
            printf ("%s%f%s","Gravity X: ", gravityX, "\n");

            float gravityY = converter((char*)&packet[74]);
            printf ("%s%f%s", "Gravity Y", gravityY, "\n");

            float gravityZ = converter((char*)&packet[78]);
            printf ("%s%f%s", "Gravity Z: ", gravityZ, "\n");

            float temp = converter((char*)&packet[82]);
            printf ("%s%f%s", "Temperature: ",temp, "\n");

            serialValues["timestamp"] = float(timestamp);

            serialValues["Altitude"] = alt;


            serialValues["Latitude"] = float(lat);
            serialValues["Longitude"] = float(longi);
        
            serialValues["Accel X"] = accelX;
            serialValues["Accel Y"] = accelY;
            serialValues["Accel Z"] = accelZ;
        

            serialValues["Gyro X"] = gyroX;
            serialValues["Gyro Y"] = gyroY;
            serialValues["Gyro Z"] = gyroZ;
        

            serialValues["Accel X IMU"] = accelXIMU;
            serialValues["Accel Y IMU"] = accelYIMU;
            serialValues["Accel Z IMU"] = accelZIMU;
        

            serialValues["Orientation X"] = oriX;
            serialValues["Orientation Y"] = oriY;
            serialValues["Orientation Z"] = oriZ;
        

            serialValues["Gravity X"] = gravityX;
            serialValues["Gravity Y"] = gravityY;
            serialValues["Gravity Z"] = gravityZ;
        

        /*Update the elevation Queue with the new value*/
        // if (elevationQueue.size() < 300){
        //     elevationQueue.push_back(alt);
        // } else {
        //     elevationQueue.push_back(alt);
        //     elevationQueue.pop_front();
        // }

        // if (flightDataFile.is_open()){ /*Write the packet to the text file */
        //     printf("flightData.txt successfully opened, beginning to write data ...\n");

        //     flightDataFile << metadata << ", " << timestamp << ", "<< ", "<< alt << ", "<< latitude << ", "<< longitude << ", "<< satInView << ", "<< accelX << ", " << accelY << ", ";
        //     flightDataFile << accelZ << ", " << gyroX << ", "<< gyroY << ", "<< gyroZ << ", "<< accelXIMU << ", " << accelYIMU << ", "<< accelZIMU << ", ";
        //     flightDataFile << oriX << ", " << oriY << ", " << oriZ << ", " << gravityX << ", " << gravityY << ", " << gravityZ << ", " << temp << "\n";

        // } else {
        //     printf("flightData.txt was not able to be opened\n");
        // }

        fclose(ptr); 
    } 
}


