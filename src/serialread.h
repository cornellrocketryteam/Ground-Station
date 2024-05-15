#pragma once

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <fmt/core.h>

enum class SensorState {
    OFF = 0,
    VALID = 1,
    INVALID = 2
};

template <> struct fmt::formatter<SensorState>: formatter<string_view> {
    // parse is inherited from formatter<string_view>.

    auto format(SensorState s, format_context& ctx) const;
};

enum class FlightMode {
    STARTUP = 0,
    STANDBY = 1,
    ASCENT = 2,
    DROGUEDEPLOYED = 3,
    MAINDEPLOYED = 4,
    FAULT = 5,
};

template <> struct fmt::formatter<FlightMode>: formatter<string_view> {
    // parse is inherited from formatter<string_view>.

    auto format(FlightMode f, format_context& ctx) const;
};

class SerialRead {
private:
    int serialDataFile;
    std::ofstream flightDataFile; /*The file to write flight telemetry*/

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
    float altitudeMeters;
    float altitudeFeet;
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

    /* The radio values to be printed to the terminal but not displayed. */
    float rssi;
    float snr;
    float frequencyError; 

    std::deque<float> elevationQueue; /*Stores the elevation points to graph*/
};
