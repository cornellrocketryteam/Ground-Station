#pragma once

#include <iostream>
#include <map> 
#include <unordered_map>
#include <vector> 

/**
 * Will represent is a sensor is working or failing. If a sensor is failing, it is 
 * in fail mode, and we will display "FAILURE" for that sensor. 
*/
typedef enum WorkingState {WORKING, FAILURE} WorkingState; 
/**
 * Flight Mode State
*/
typedef enum FlightMode {StartupMode, StandbyMode, AscentMode,DrogueDeployedMode, MainDeployedMode,FaultMode, Armed} FlightMode; 

/**
 * The Class that stores the static member function that will read serial data, and then
 * u pdate the serialValues map with said data for the GUI's components to draw accurately. 
*/
class SerialRead {
    public: 
         /**
         * Will represent the states of each sensor, six in total
        */
        static WorkingState AltimeterState; 
        static WorkingState GpsState; 
        static WorkingState IMUState; 
        static WorkingState SDCardState; 
        static WorkingState AccelerometerState;
        static WorkingState TemperatureState;
        static WorkingState RadioState; 

        static FlightMode FlightState;

        /**
         * Stores the values that are read from RATS. 
        */
        static std::unordered_map<std::string, float> serialValues;
        /**
         * Will read the package received from RATS to be the [package] member 
         * via reading serial data  
        */
        static void readPack();  

}; 


/**
 * 6 bytes: Metadata
3 bits: flight mode
10 bits: Sensor statuses (2 bits each)
1 bit: SD state
1 bit: key armed
1 bit: altitude armed
4 bytes: timestamp
3 bytes: Events
(Will come up with enumeration)
52 bytes: Sensor readings (4 bytes each)
Altitude
Latitude
Longitude
Elevation
Accel X
Accel Y
Accel Z
Gyro X
Gyro Y
Gyro Z
Mag X
Mag Y
Mag Z 

For the EVENTS:
0: Key armed
1: Altitude armed
2: Alt init failed
3: Alt reading failed
4: Alt turned off
5: IMU init failed
6: IMU reading failed
7: IMU turned off
8: Accel init failed
9: Accel reading failed
10: Accel turned off
11: Therm init failed
12: Therm reading failed
13: Therm turned off
14: SD init failed
15: SD write failed
16: RFM init failed
17: RFM transmit failed

0 means false, 1 means true 
*/