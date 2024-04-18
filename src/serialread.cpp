#include "serialread.h"
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

SerialRead::SerialRead() {
    serialDataFile = open("/dev/cu.usbmodem2101", O_RDONLY | O_NONBLOCK);
    flightDataFile = fopen("data/flightData.txt", "w");
}

SerialRead::~SerialRead() {
    fclose(flightDataFile);
    close(serialDataFile);
}

float SerialRead::getValue(std::string name) {
    return serialValues[name];
}

template<typename T>
T converter(char *packet) {
    T temp;
    memcpy(&temp, packet, sizeof(temp));
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
    char packet[86];

    if (serialDataFile != -1) {
        // read 86 bytes to our buffer
        if (read(serialDataFile, packet, sizeof(packet)) != sizeof(packet)) {
            return;
        }

        bool altitudeArmed;
        bool gpsValid;
        bool sdInitialized;

        for (int i = 0; i < 16; i++) {
            switch (i) {
                case 0:
                    altitudeArmed = 0x01 & packet[0];
                    break;
                case 1:
                    gpsValid = 0x01 & packet[0];
                    break;
                case 2:
                    sdInitialized = 0x01 & packet[0];
                    break;
                case 3:
                    temperatureState = static_cast<SensorState>(0x03 & packet[0]);
                    break;
                case 4:
                    break;
                case 5:
                    accelerometerState = static_cast<SensorState>(0x03 & packet[0]);
                    break;
                case 6:
                    break;
                case 7:
                    imuState = static_cast<SensorState>(((0x01 & packet[1]) << 1) | (0x01 & packet[0]));
                    break;
                case 8:
                    break;
                case 9:
                    gpsState = static_cast<SensorState>(0x03 & packet[1]);
                    break;
                case 10:
                    break;
                case 11:
                    altimeterState = static_cast<SensorState>(0x03 & packet[1]);
                    break;
                case 12:
                    break;
                case 13:
                    flightMode = static_cast<FlightMode>(0x7 & packet[1]);
                    break;
                case 14:
                case 15:
                    break;
                default:
                    printf("ERROR: Reached default block of switch statement");
                    break;
            }
            packet[i / 8] >>= 1;
        }

        uint32_t timestamp = converter<uint32_t>((char *) &packet[2]);
        printf("%s%i%s", "Time Stamp: ", timestamp, "\n");

        printf("Events Byte 1: ");
        printByte(packet[6]);

        printf("Events Byte 2: ");
        printByte(packet[7]);

        printf("Events Byte 3: ");
        printByte(packet[8]);

        float alt = converter<float>((char *) &packet[9]);

        float lat = converter<float>((char *) &packet[13]);

        float longi = converter<float>((char *) &packet[17]);

        uint8_t satInView = converter<uint8_t>((char *) &packet[21]);

        float accelX = converter<float>((char *) &packet[22]);

        float accelY = converter<float>((char *) &packet[26]);

        float accelZ = converter<float>((char *) &packet[30]);

        float gyroX = converter<float>((char *) &packet[34]);

        float gyroY = converter<float>((char *) &packet[38]);

        float gyroZ = converter<float>((char *) &packet[42]);

        float accelXIMU = converter<float>((char *) &packet[46]);

        float accelYIMU = converter<float>((char *) &packet[50]);

        float accelZIMU = converter<float>((char *) &packet[54]);

        float oriX = converter<float>((char *) &packet[58]);

        float oriY = converter<float>((char *) &packet[62]);

        float oriZ = converter<float>((char *) &packet[66]);

        float gravityX = converter<float>((char *) &packet[70]);

        float gravityY = converter<float>((char *) &packet[74]);

        float gravityZ = converter<float>((char *) &packet[78]);

        float temp = converter<float>((char *) &packet[82]);

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


        /*TODO: Update the elevation Queue with the new value*/

//        if (flightDataFile != nullptr) { /*Write the packet to the text file */
//            printf("flightData.txt successfully opened, beginning to write data ...\n");
//
//            for (auto it = serialValues.begin(); it != serialValues.end(); it++) {
//                fprintf(flightDataFile, "%s: %f,", it->first.c_str(), it->second);
//            }
//            fprintf(flightDataFile, "\n");
//
//
//        } else {
//            printf("flightData.txt was not able to be opened\n");
//        }

    }
}
