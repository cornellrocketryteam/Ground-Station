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

        timestamp = converter<uint32_t>((char *) &packet[2]);
        printf("%s%i%s", "Time Stamp: ", timestamp, "\n");

        printf("Events Byte 1: ");
        printByte(packet[6]);

        printf("Events Byte 2: ");
        printByte(packet[7]);

        printf("Events Byte 3: ");
        printByte(packet[8]);

        if (altimeterState == VALID) {
            altitude = converter<float>((char *) &packet[9]);

            if (elevationQueue.max_size() < 500) {
                elevationQueue.push_back(altitude);
            } else {
                elevationQueue.pop_front();
                elevationQueue.push_back(altitude);
            }
        }

        if (gpsState == VALID) {
            latitude = converter<float>((char *) &packet[13]);
            longitude = converter<float>((char *) &packet[17]);
            satInView = converter<uint8_t>((char *) &packet[21]);
        }

        if (accelerometerState == VALID) {
            accelX = converter<float>((char *) &packet[22]);
            accelY = converter<float>((char *) &packet[26]);
            accelZ = converter<float>((char *) &packet[30]);
        }

        if (imuState == VALID) {
            gyroX = converter<float>((char *) &packet[34]);
            gyroY = converter<float>((char *) &packet[38]);
            gyroZ = converter<float>((char *) &packet[42]);
            accelXIMU = converter<float>((char *) &packet[46]);
            accelYIMU = converter<float>((char *) &packet[50]);
            accelZIMU = converter<float>((char *) &packet[54]);
            oriX = converter<float>((char *) &packet[58]);
            oriY = converter<float>((char *) &packet[62]);
            oriZ = converter<float>((char *) &packet[66]);
            gravityX = converter<float>((char *) &packet[70]);
            gravityY = converter<float>((char *) &packet[74]);
            gravityZ = converter<float>((char *) &packet[78]);
        }

        if (temperatureState == VALID) {
            temp = converter<float>((char *) &packet[82]);
        }

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
