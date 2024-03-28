#include "statusbar.h"
#include "sfr.h"
#include "raylib.h"

/**
 * Constructor to create the Status Lights in the StatusBar constructor
*/
StatusLight::StatusLight(std::string name, float radius) : name(name), radius(radius)
{
}

bool StatusLight::getWorking() {
    return isWorking;
}

void StatusLight::setWorking(bool val){
    isWorking = val; 
}

float StatusLight::getRadius() {
    return radius;
}

std::string StatusLight::getName() {
    return name;
}

StatusBar::StatusBar() {
    status_lights.emplace_back("GPS", 20);
    status_lights.emplace_back("Altimeter", 20);
    status_lights.emplace_back("Temperature", 20);
    status_lights.emplace_back("Gyroscope", 20);
    status_lights.emplace_back("IMU", 20);
}

void StatusBar::draw(int posX, int posY, int width, int height) {
    updateStatusLights();

    int fontSize = 20;
    int centerY = posY + height/2;
    int offsetY = height/6;
    int width_step = (0.66*width) / (2*status_lights.size());
    for (int i = 0; i < status_lights.size(); ++i) {
        StatusLight status_light = status_lights.at(i);
        Color color = status_light.getWorking() ? GREEN : RED;
        int x = width_step*(2*i+1);

        int text_width = MeasureText(status_light.getName().c_str(), fontSize);
        DrawText(status_light.getName().c_str(), posX + x - text_width/2, centerY - offsetY - fontSize/2, fontSize, WHITE);

        DrawCircle(posX + x, centerY + offsetY, status_light.getRadius(), color);
    }

    // Current Flight Mode
    DrawRectangle(posX + 0.66*width, posY, 0.34*width, height, SKYBLUE);
    int headerX = posX + 0.83*width - MeasureText("Current Flight Mode:", fontSize)/2;

    std::string flightMode;
    switch (sfr::serialRead.flightMode) {
        case SerialRead::STARTUP:
            flightMode = "Startup";
            break;
        case SerialRead::STANDBY:
            flightMode = "Standby";
            break;
        case SerialRead::ASCENT:
            flightMode = "Ascent";
            break;
        case SerialRead::DROGUEDEPLOYED:
            flightMode = "Drogue Deployed";
            break;
        case SerialRead::MAINDEPLOYED:
            flightMode = "Main Deployed";
            break;
        case SerialRead::FAULT:
            flightMode = "Fault";
            break;
    }
    DrawText("Current Flight Mode:", headerX, posY + height/3 - fontSize/2, fontSize, DARKBLUE);
    int statusX = posX + 0.83*width - MeasureText(flightMode.c_str(), fontSize)/2;
    DrawText(flightMode.c_str(), statusX, posY + 2*height/3 - fontSize/2, fontSize, DARKBLUE);
}

void StatusBar::updateStatusLights(){
    for (auto i : status_lights){
        if (i.getName() == "GPS"){
            if (sfr::serialRead.gpsState == sfr::serialRead.VALID){
                i.setWorking(true);
            } else {
                i.setWorking(false);
            }
        } else if (i.getName() == "Altimeter"){
            if (sfr::serialRead.altimeterState == sfr::serialRead.VALID){
                i.setWorking(true);
            } else {
                i.setWorking(false);
            }
        } else if (i.getName() == "Temperature"){
            if (sfr::serialRead.temperatureState == sfr::serialRead.VALID){
                i.setWorking(true);
            } else {
                i.setWorking(false);
            }
        } else if (i.getName() == "Gyroscope"){
            if (sfr::serialRead.accelerometerState == sfr::serialRead.VALID){
                i.setWorking(true);
            } else {
                i.setWorking(false);
            }
        } else if (i.getName() == "IMU"){
            if (sfr::serialRead.imuState == sfr::serialRead.VALID){
                i.setWorking(true);
            } else {
                i.setWorking(false);
            }
        }
    }
}
