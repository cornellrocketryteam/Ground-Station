#pragma once

#include <deque>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

class SerialRead {
private:
    std::unordered_map<std::string, float> serialValues;

    int serialDataFile;
    FILE *flightDataFile; /*The file to write flight telemetry*/

public:
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

    SensorState altimeterState;
    SensorState gpsState;
    SensorState imuState;
    SensorState accelerometerState;
    SensorState temperatureState;

    FlightMode flightMode;

    void readPacket();  /*Read the packet from RATS with pigpio*/

    float getValue(std::string name); /*Gets the float value from the serialValues*/

    SerialRead(); /*Open the serial port /dev/ttyACM0*/

    ~SerialRead(); /*Close the serial port*/

    std::deque<float> elevationQueue; /*Stores the elevation points to graph*/
};
