#include "serialread.h"
#include <stdio.h> 
#include <cstring> 
#include <iostream>

#ifndef __APPLE__
#include <pigpio.h>
#endif

SerialRead::SerialRead(){
#ifndef __APPLE__
    if (gpioInitialise() < 0){
            printf("Pigpio not initialized.\n"); 
    } else {
            printf("Pigpio succesffuly initialized.\n");
    }

    serialPort = serOpen("/dev/ttyACM0",9600,0); 

    if (serialPort< 0) { /* open serial port */
        printf ("Unable to open serial device\n") ;
    } else {
        printf("Opened serial port\n"); 
    }
#endif

    flightDataFile.open("data/flightData.txt",std::ios::out);
}

SerialRead::~SerialRead(){
    flightDataFile.close();

#ifndef __APPLE__
    serClose(serialPort);
    gpioTerminate();
#endif
}

float SerialRead::getValue(std::string name){
    return serialValues[name]; 
}

template <typename T>
T SerialRead::readType()
{
    T output;
    char data[sizeof(T)];

#ifndef __APPLE__
    serRead(serialPort, data, sizeof(T));
#endif

    memcpy(&output, data, sizeof(T));

    return output;
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
#ifndef __APPLE__
    if (serDataAvailable(serialPort)) {
        uint8_t packet[86];
        serRead(serialPort, packet, sizeof(packet));
        for (int i = 0; i < 86; i++) {
            std::cout << "Byte " << i << ": ";
            printByte(packet[i]);
        }
    }
//    if(serDataAvailable (serialPort) ){
//        auto metadata = readType<uint16_t>();
//
//        bool altitudeArmed;
//        bool gpsValid;
//        bool sdInitialized;
//
//        for (int i = 0; i < sizeof(metadata) * 8; i++){
//            switch (i) {
//                case 0:
//                    altitudeArmed =  0x01 & metadata;
//                    break;
//                case 1:
//                    gpsValid =  0x01 & metadata;
//                    break;
//                case 2:
//                    sdInitialized =  0x01 & metadata;
//                    break;
//                case 3:
//                    temperatureState = static_cast<SensorState>(0x03 & metadata);
//                    break;
//                case 4:
//                    continue;
//                case 5:
//                    accelerometerState = static_cast<SensorState>(0x03 & metadata);
//                    break;
//                case 6:
//                    continue;
//                case 7:
//                    imuState = static_cast<SensorState>(0x03 & metadata);
//                    break;
//                case 8:
//                    continue;
//                case 9:
//                    gpsState = static_cast<SensorState>(0x03 & metadata);
//                    break;
//                case 10:
//                    continue;
//                case 11:
//                    altimeterState = static_cast<SensorState>(0x03 & metadata);
//                    break;
//                case 12:
//                    continue;
//                case 13:
//                    flightMode = static_cast<FlightMode>(0x7 & metadata);
//                    break;
//                case 14:
//                case 15:
//                    continue;
//                default:
//                    printf("ERROR: Reached default block of switch statement");
//                    break;
//            }
//            metadata >>= 1;
//        }
//
//        auto timestamp = readType<uint32_t>();
//
//        char events[3]; /*Read the events bytes*/
//        serRead(serialPort, events, sizeof(events));
//
//        for (int i = 0; i < sizeof(events) * 8; i++){
//            switch(i) {
//                default:
//                    // TODO: FIGURE OUT WHAT TO DO FOR EACH EVENT
//                    break;
//            }
//            events[i / 8] >>= 1;
//        }
//
//        auto alt = readType<float>();
//
//        auto latitude = readType<int32_t>();
//        auto longitude = readType<int32_t>();
//
//        auto satInView = readType<uint8_t>();
//
//        auto accelX = readType<float>();
//        auto accelY = readType<float>();
//        auto accelZ = readType<float>();
//
//        auto gyroX = readType<float>();
//        auto gyroY = readType<float>();
//        auto gyroZ = readType<float>();
//
//        auto accelXIMU = readType<float>();
//        auto accelYIMU = readType<float>();
//        auto accelZIMU = readType<float>();
//
//        auto oriX = readType<float>();
//        auto oriY = readType<float>();
//        auto oriZ = readType<float>();
//
//        auto gravityX = readType<float>();
//        auto gravityY = readType<float>();
//        auto gravityZ = readType<float>();
//
//        auto temp = readType<float>();
//
//        serialValues["timestamp"] = float(timestamp);
//
//        if (altimeterState == VALID) {
//            serialValues["Altitude"] = alt;
//        }
//
//        if (gpsState == VALID) {
//            serialValues["Latitude"] = float(latitude);
//            serialValues["Longitude"] = float(longitude);
//            serialValues["Satellites"] = float(satInView);
//        }
//
//        if (accelerometerState == VALID) {
//            serialValues["Accel X"] = accelX;
//            serialValues["Accel Y"] = accelY;
//            serialValues["Accel Z"] = accelZ;
//        }
//
//        if (imuState == VALID) {
//            serialValues["Gyro X"] = gyroX;
//            serialValues["Gyro Y"] = gyroY;
//            serialValues["Gyro Z"] = gyroZ;
//        }
//
//        if (imuState == VALID) {
//            serialValues["Accel X IMU"] = accelXIMU;
//            serialValues["Accel Y IMU"] = accelYIMU;
//            serialValues["Accel Z IMU"] = accelZIMU;
//        }
//
//        if (imuState == VALID) {
//            serialValues["Orientation X"] = oriX;
//            serialValues["Orientation Y"] = oriY;
//            serialValues["Orientation Z"] = oriZ;
//        }
//
//        if (imuState == VALID) {
//            serialValues["Gravity X"] = gravityX;
//            serialValues["Gravity Y"] = gravityY;
//            serialValues["Gravity Z"] = gravityZ;
//        }
//
//        /*Update the elevation Queue with the new value*/
//        if (elevationQueue.size() < 300){
//            elevationQueue.push_back(alt);
//        } else {
//            elevationQueue.push_back(alt);
//            elevationQueue.pop_front();
//        }
//
//        if (flightDataFile.is_open()){ /*Write the packet to the text file */
//            printf("flightData.txt successfully opened, beginning to write data ...\n");
//
//            flightDataFile << metadata << ", " << timestamp << ", "<< events << ", "<< alt << ", "<< latitude << ", "<< longitude << ", "<< satInView << ", "<< accelX << ", " << accelY << ", ";
//            flightDataFile << accelZ << ", " << gyroX << ", "<< gyroY << ", "<< gyroZ << ", "<< accelXIMU << ", " << accelYIMU << ", "<< accelZIMU << ", ";
//            flightDataFile << oriX << ", " << oriY << ", " << oriZ << ", " << gravityX << ", " << gravityY << ", " << gravityZ << ", " << temp << "\n";
//
//        } else {
//            printf("flightData.txt was not able to be opened\n");
//        }
//    } else {
//        printf("Serial port not available, could not read\n");
//    }
#endif
}
