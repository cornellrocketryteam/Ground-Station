#include "sensorDisplay.h"
#include "dataprocessing.h"

SensorScreen::SensorScreen() : latitude(100, 300, 1, 0, RAYWHITE, "Latitude"),
                               longitude(100, 400, 1, 0, RAYWHITE, "Longitude"),
                               elevation(100, 500, 1, 0,RAYWHITE, "Elevation"),
                               accel_x(100, 600, 1, 0,RAYWHITE, "Accel_X"),
                               accel_y(100, 700, 1, 0,RAYWHITE, "Accel_Y"),
                               accel_z(100, 800, 1, 0,WHITE, "Accel_Z"),
                               gyro_x(100, 900, 1, 0,WHITE, "Gyro_X"),
                               gyro_y(300, 300, 1, 0,WHITE, "Gyro_Y"),
                               gyro_z(300, 400, 1, 0,WHITE, "Gyro_Z"),
                               mag_x(300, 500, 1, 0,WHITE, "Mag_X"),
                               mag_y(300, 600, 1, 0,WHITE, "Mag_Y"),
                               mag_z(300, 700, 1, 0,WHITE, "Mag_Z"),
                               temp(300, 800, 1, 0,WHITE, "Temperature"),
                               elevationGraph(screenWidth/2, 0, screenWidth/2, screenHeight/2-25, WHITE),
                               temperatureGraph(screenWidth/2, 0, screenHeight/2, screenHeight/2-25, WHITE)
{
    graphs.push_back(elevationGraph);
    graphs.push_back(temperatureGraph);
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
    for (auto graph : graphs)
    {
        graph.draw();
    }
}


void SensorScreen::updateValues()
{
    float lat = SerialRead::serialValues["latitude"];
    latitude.setText(std::to_string(lat));
}
