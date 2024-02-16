#include "sensorDisplay.h"
#include "dataprocessing.h"

SensorScreen::SensorScreen() : latitude(100, 300, 1, 0, RAYWHITE, "Latitude"),
                               longitude(100, 400, 1, 0, RAYWHITE, "Longitude"),
                               elevation(100, 500, 1, 0,RAYWHITE, "Elevation"),
                               accel_x(100, 600, 1, 0,RAYWHITE, "Accel_X"),
                               accel_y(100, 700, 1, 0,RAYWHITE, "Accel_Y"),
                               accel_z(300, 300, 1, 0,WHITE, "Accel_Z"),
                               gyro_x(300, 400, 1, 0,WHITE, "Gyro_X"),
                               gyro_y(300, 500, 1, 0,WHITE, "Gyro_Y"),
                               gyro_z(300, 600, 1, 0,WHITE, "Gyro_Z"),
                               mag_x(300, 700, 1, 0,WHITE, "Mag_X"),
                               mag_y(500, 300, 1, 0,WHITE, "Mag_Y"),
                               mag_z(500, 400, 1, 0,WHITE, "Mag_Z"),
                               temp(500, 500, 1, 0,WHITE, "Temperature"),
                               flightMode(1300,900,1,0,WHITE,"Flight Mode"),
                               elevationGraph(screenWidth/2, screenHeight/2, screenWidth/2, screenHeight/2-100, WHITE),
                               statusBar(100, 950, 1400, 100)
{
   //SerialRead::initializeSensorEnums();
}

void SensorScreen::drawComponents()
{
    // read in the sensor values
    SerialRead::updateSerialValues();

    //update the texts boxes based on the new sensor values
    updateValues();

    // draw all of the text displays

    latitude.draw();
    longitude.draw();
    accel_x.draw();
    accel_y.draw();
    accel_z.draw();
    gyro_x.draw();
    gyro_y.draw();
    gyro_z.draw();
    elevation.draw();
    mag_x.draw();
    mag_y.draw();
    mag_z.draw();
    temp.draw();

    // draw all of the graphs
    elevationGraph.draw();

    // draw the GPS launch site
    gps.drawLaunchSite();

    //Draw the status bar of the sensors
    statusBar.drawBar();
}


void SensorScreen::updateValues()
{
    float lat = SerialRead::serialValues["latitude"];
    latitude.setText("Latitude: " + std::to_string(lat));

    float longi = SerialRead::serialValues["longitude"]; 
    longitude.setText("Latitude: " + std::to_string(longi)); 

    float accx = SerialRead::serialValues["accel_x"]; 
    accel_x.setText("Accel_X: " + std::to_string(accx)); 

    float accy = SerialRead::serialValues["accel_y"]; 
    accel_y.setText("Accel_Y: " + std::to_string(accy)); 

    float accz = SerialRead::serialValues["accel_z"]; 
    accel_z.setText("Accel_Z: " + std::to_string(accz)); 

    float gyrox = SerialRead::serialValues["gyro_x"]; 
    gyro_x.setText("Gyro_X: " + std::to_string(gyrox)); 

    float gyroy = SerialRead::serialValues["gyro_y"]; 
    gyro_y.setText("Gyro_Y: " + std::to_string(gyroy)); 
    
    float gyroz = SerialRead::serialValues["gyro_z"]; 
    gyro_z.setText("Gyro_Z: " + std::to_string(gyroz)); 
    
    float elev = SerialRead::serialValues["elevation"]; 
    elevation.setText("Elevation: " + std::to_string(elev)); 

    float magx = SerialRead::serialValues["mag_x"]; 
    mag_x.setText("Mag_X: " + std::to_string(magx)); 

    float magy = SerialRead::serialValues["mag_y"]; 
    mag_y.setText("Mag_Y: " + std::to_string(magy)); 

    float magz = SerialRead::serialValues["mag_z"]; 
    mag_z.setText("Mag_Z: " + std::to_string(magz)); 

    float temper = SerialRead::serialValues["temp"]; 
    temp.setText("Temperature: " + std::to_string(temper)); 

    // std::string flightString; 
    // switch(SerialRead::getFlightState()){
    //     case (StartupMode) : flightString = "Startup"; 
    //     case (StandbyMode) :flightString = "Standby"; 
    //     case (AscentMode) :flightString = "Ascent"; 
    //     case (DrogueDeployedMode) :flightString = "Drogue Deployed"; 
    //     case (MainDeployedMode) :flightString = "Main Deployed"; 
    //     case (FaultMode) :flightString = "Fault"; 
    // }
    // flightMode.setText("Flight Mode: " + flightString); 

}
