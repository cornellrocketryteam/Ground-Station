#include "serialread.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fmt/chrono.h>
#include <bitset>

#define PACKET_SIZE 98

auto fmt::formatter<SensorState>::format(SensorState s, format_context& ctx) const {
    string_view state = "unknown";
    switch (s) {
        case SensorState::OFF: state = "OFF"; break;
        case SensorState::VALID: state = "VALID"; break;
        case SensorState::INVALID: state = "INVALID"; break;
    }
    return formatter<string_view>::format(state, ctx);
}

auto fmt::formatter<FlightMode>::format(FlightMode f, format_context& ctx) const {
    string_view mode = "unknown";
    switch (f) {
        case FlightMode::STARTUP: mode = "STARTUP"; break;
        case FlightMode::STANDBY: mode = "STANDBY"; break;
        case FlightMode::ASCENT: mode = "ASCENT"; break;
        case FlightMode::DROGUEDEPLOYED: mode = "DROGUEDEPLOYED"; break;
        case FlightMode::MAINDEPLOYED: mode = "MAINDEPLOYED"; break;
        case FlightMode::FAULT: mode = "FAULT"; break;
    }
    return formatter<string_view>::format(mode, ctx);
}

SerialRead::SerialRead() {
    serialDataFile = open("/dev/cu.usbmodem2101", O_RDONLY | O_NONBLOCK);
    auto now = std::chrono::system_clock::now();
    std::string flightDataFilePath = fmt::format("data/flightData_{:%Y_%m_%d_%H:%M}.csv", now);
    flightDataFile.open(flightDataFilePath.c_str(), std::ios::out);
    flightDataFile << "timestamp,flightMode,altitudeArmed,gpsValid,sdInitialized,temperatureState,accelerometerState,imuState,gpsState,altimeterState,altitude,latitude,longitude,satInView,accelX,accelY,accelZ,gyroX,gyroY,gyroZ,accelXIMU,accelYIMU,accelZIMU,oriX,oriY,oriZ,gravityX,gravityY,gravityZ,temp" << std::endl;

    for (int _ = 0; _ < 400; ++_) {
        elevationQueue.push_back(0.0);
    }
}

SerialRead::~SerialRead() {
    flightDataFile.close();
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
    char packet[PACKET_SIZE];

    if (serialDataFile != -1) {
        // read 86 bytes to our buffer
        if (read(serialDataFile, packet, sizeof(packet)) != sizeof(packet)) {
            return;
        }

        printf("Packet: \n\n");
        printf("\n\n\n\t\tDEBUG Binary Dump:\n\n");
        for (uint i = 0; i < PACKET_SIZE; i++) {
            std::bitset<sizeof(unsigned int) * 8> bits(packet[i]);
            printf("%d", bits);
        }
        printf("\n\n");

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

        if (altimeterState == SensorState::VALID) {
            altitudeMeters = converter<float>((char *) &packet[9]);
            altitudeFeet = altitudeMeters * 3.280839895;

            elevationQueue.pop_front();
            elevationQueue.push_back(altitudeFeet);
        }

        if (gpsState == SensorState::VALID) {
            latitude = converter<float>((char *) &packet[13]);
            longitude = converter<float>((char *) &packet[17]);
            satInView = converter<uint8_t>((char *) &packet[21]);
        }

        if (accelerometerState == SensorState::VALID) {
            accelX = converter<float>((char *) &packet[22]);
            accelY = converter<float>((char *) &packet[26]);
            accelZ = converter<float>((char *) &packet[30]);
        }

        if (imuState == SensorState::VALID) {
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

        if (temperatureState == SensorState::VALID) {
            temp = converter<float>((char *) &packet[82]);
        }

        rssi = converter<float>((char*) &packet[86]);
        snr = converter<float>((char*) &packet[90]);
        frequencyError = converter<float>((char*) &packet[95]); 

        if (flightDataFile.is_open()) {
            flightDataFile << fmt::format("{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}",timestamp,flightMode,altitudeArmed,gpsValid,sdInitialized,temperatureState,accelerometerState,imuState,gpsState,altimeterState,altitudeMeters,latitude,longitude,satInView,accelX,accelY,accelZ,gyroX,gyroY,gyroZ,accelXIMU,accelYIMU,accelZIMU,oriX,oriY,oriZ,gravityX,gravityY,gravityZ,temp) << std::endl;
        }
    }
}
