#include "dataprocessing.h"
#include <iostream>

//#define APPLE
#ifndef APPLE
#include <pigpio.h> 

SerialRead::SerialRead(){
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

    AltimeterState = FAILURE; 
    GpsState = FAILURE; 
    IMUState = FAILURE;  
    SDCardState = FAILURE; 
    AccelerometerState = FAILURE; 
    TemperatureState = FAILURE; 
    RadioState = FAILURE;  
    FlightState = StartupMode; 

    flightDataFile.open("data/flightData.txt",std::ios::out);
}

SerialRead::~SerialRead(){
    serClose(serialPort); 

    flightDataFile.close();

    gpioTerminate();
}

float SerialRead::getValue(std::string name){
    return serialValues[name]; 
}

float SerialRead::bytesToFloat()
{
    float output;
    char data[4]; 
    serRead(serialPort,data,4); 

    std::memcpy(&output,data, 4);

    return output;
}

void SerialRead::readPack(){ 
    if(serDataAvailable (serialPort) ){          
        char preamble[2];     /*Read the preamble packets*/
        serRead(serialPort,preamble,2); 

        for (int i = 0; i < 8; i++){
            if (0x01 & preamble[0]){
                switch(i){
                    case 0: AltimeterState = WORKING; 
                    case 1: GpsState = WORKING; 
                    case 2: SDCardState = WORKING; 
                    case 3: TemperatureState = WORKING; 
                    case 4: TemperatureState = FAILURE; 
                    case 5: AccelerometerState = WORKING; 
                    case 6: AccelerometerState = FAILURE;
                    case 7: IMUState = WORKING; 
                }
                preamble[0] >> 1; 
            }
        }
        u_int8_t sumOfFlightStatus; 
        for (int i = 8; i < 16; i++){
            if (0x01 & preamble[1]){
                switch(i){
                    case 8: IMUState = FAILURE; 
                    case 9: GpsState = WORKING; 
                    case 10: GpsState = FAILURE; 
                    case 11: AltimeterState = WORKING; 
                    case 12: AltimeterState = FAILURE; 
                    case 13: sumOfFlightStatus += 4;
                    case 14: sumOfFlightStatus += 2; 
                    case 15: sumOfFlightStatus += 1; 
                }
                preamble[1] >> 1; 
            }
        }
        /*Process the bytes for flight status */
        switch(sumOfFlightStatus){
            case 0: FlightState = StartupMode; 
            case 1: FlightState = StandbyMode; 
            case 2: FlightState = AscentMode; 
            case 3: FlightState = DrogueDeployedMode; 
            case 4: FlightState = MainDeployedMode; 
            case 5: FlightState = FaultMode; 
        }

        float timestamp = bytesToFloat(); 

        char events[3]; /*Read the events bytes*/
        serRead(serialPort,events,3);  

        for (int i = 0; i<8; i++){
            if (0x01 & events[0]){
                switch(i){
                    //case 0:
                    //case 1:
                    case 2: AltimeterState = FAILURE; 
                    case 3: AltimeterState = FAILURE; 
                    case 4: AltimeterState = FAILURE; 
                    case 5: IMUState = FAILURE; 
                    case 6: IMUState = FAILURE; 
                    case 7: IMUState = FAILURE; 
                }
                events[0]>>1; 
            }
        }
        for (int i = 8; i<16; i++){
            if (0x01 & events[1]){
                switch(i){
                    case 8: AccelerometerState = FAILURE; 
                    case 9: AccelerometerState = FAILURE; 
                    case 10: AccelerometerState = FAILURE; 
                    case 11: TemperatureState = FAILURE; 
                    case 12: TemperatureState = FAILURE; 
                    case 13: TemperatureState = FAILURE; 
                    case 14: SDCardState = FAILURE;
                    case 15: SDCardState = FAILURE;
                }
                events[1]>>1; 
            }
        }
        for (int i = 16; i<18; i++){
            if (0x01 & events[2]){
                switch(i){
                    case 16: RadioState = FAILURE; 
                    case 17: RadioState = FAILURE; 
                }
                events[2]>>1; 
            }
        }

        float alt = bytesToFloat();
        float lat = bytesToFloat();
        float longi = bytesToFloat();

        float satInView = bytesToFloat(); 

        float accelx = bytesToFloat();
        float accely = bytesToFloat();
        float accelz = bytesToFloat();

        float gyrox = bytesToFloat();
        float gyroy = bytesToFloat();
        float gyroz = bytesToFloat();

        float accelXIMU = bytesToFloat(); 
        float accelYIMU = bytesToFloat(); 
        float accelZIMU = bytesToFloat(); 

        float oriX = bytesToFloat(); 
        float oriY = bytesToFloat(); 
        float oriZ = bytesToFloat(); 

        float magx = bytesToFloat();
        float magy = bytesToFloat();
        float magz = bytesToFloat();

        float temp = bytesToFloat(); 

        serialValues["longitude"] = longi; 
        serialValues["latitude"] = lat; 
        serialValues["altitude"] = alt; 
        serialValues["gyro_x"] = gyrox; 
        serialValues["gyro_y"] = gyroy; 
        serialValues["gyro_z"] = gyroz; 
        serialValues["accel_x"] = accelx; 
        serialValues["accel_y"] = accely; 
        serialValues["accel_z"] = accelz; 
        serialValues["mag_x"] = magx;
        serialValues["mag_y"] = magy; 
        serialValues["mag_z"] = magz;
        serialValues["timestamp"] = timestamp; 

        if (flightDataFile.is_open()){ /*Write the packet to the text file */
        printf("flightData.txt successfully opened, beginning to write data ...");

        flightDataFile << preamble << timestamp << events << alt << lat << longi << satInView << accelx << accely; 
        flightDataFile << accelz << gyrox << gyroy << gyroz << accelXIMU << accelYIMU << accelZIMU; 
        flightDataFile << oriX << oriY << oriZ << magx << magy << magz << temp << "\n"; 

        } else {
        printf("flightData.txt was not able to be opened");
    }

    } else {
        printf("Serial port not available, could not read\n"); 
    }
  
}

#endif 