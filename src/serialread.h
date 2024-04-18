#pragma once

#include <deque>
#include <iostream>
#include <map>
#include <vector>

enum SensorState {
    OFF = 0,
    VALID = 1,
    INVALID = 2
};

enum FlightMode {
    STARTUP = 0,
    STANDBY = 1,
    ASCENT = 2,
    DROGUEDEPLOYED = 3,
    MAINDEPLOYED = 4,
    FAULT = 5,
};

class SerialRead {
private:
    int serialDataFile;
    FILE *flightDataFile; /*The file to write flight telemetry*/

public:
    SerialRead(); /*Open the serial port*/
    ~SerialRead(); /*Close the serial port*/

    void readPacket();  /*Read the packet from RATS*/

    bool altitudeArmed;
    bool gpsValid;
    bool sdInitialized;

    SensorState temperatureState;
    SensorState accelerometerState;
    SensorState imuState;
    SensorState gpsState;
    SensorState altimeterState;

    FlightMode flightMode;

    uint32_t timestamp;
    float altitude;
    float latitude;
    float longitude;
    uint8_t satInView;
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
    float accelXIMU;
    float accelYIMU;
    float accelZIMU;
    float oriX;
    float oriY;
    float oriZ;
    float gravityX;
    float gravityY;
    float gravityZ;
    float temp;

    std::deque<float> elevationQueue; /*Stores the elevation points to graph*/
};
