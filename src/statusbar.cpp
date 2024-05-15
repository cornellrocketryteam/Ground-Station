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
    status_lights.emplace_back(new StatusLight("GPS", 20));
    status_lights.emplace_back(new StatusLight("Altimeter", 20));
    status_lights.emplace_back(new StatusLight("Temperature", 20));
    status_lights.emplace_back(new StatusLight("Accelerometer", 20));
    status_lights.emplace_back(new StatusLight("IMU", 20));
}

void StatusBar::draw(int posX, int posY, int width, int height) {
    updateStatusLights();

    int fontSize = 20;
    int centerY = posY + height/2;
    int offsetY = height/6;
    int width_step = (0.75*width) / (2*status_lights.size());
    for (int i = 0; i < status_lights.size(); ++i) {
        StatusLight status_light = *status_lights.at(i);
        Color color = status_light.getWorking() ? GREEN : RED;
        int x = width_step*(2*i+1);

        int text_width = MeasureText(status_light.getName().c_str(), fontSize);
        DrawText(status_light.getName().c_str(), posX + x - text_width/2, centerY - offsetY - fontSize/2, fontSize, WHITE);

        DrawCircle(posX + x, centerY + offsetY, status_light.getRadius(), color);
    }

    // Current Flight Mode
    DrawRectangle(posX + 0.75*width, posY, 0.25*width, height, SKYBLUE);
    int headerX = posX + 0.875*width - MeasureText("Current Flight Mode:", fontSize)/2;

    std::string flightMode;
    switch (sfr::serialRead->flightMode) {
        case FlightMode::STARTUP:
            flightMode = "Startup";
            break;
        case FlightMode::STANDBY:
            flightMode = "Standby";
            break;
        case FlightMode::ASCENT:
            flightMode = "Ascent";
            break;
        case FlightMode::DROGUEDEPLOYED:
            flightMode = "Drogue Deployed";
            break;
        case FlightMode::MAINDEPLOYED:
            flightMode = "Main Deployed";
            break;
        case FlightMode::FAULT:
            flightMode = "Fault";
            break;
    }
    DrawText("Current Flight Mode:", headerX, posY + height/3 - fontSize/2, fontSize, DARKBLUE);
    int statusX = posX + 0.875*width - MeasureText(flightMode.c_str(), fontSize)/2;
    DrawText(flightMode.c_str(), statusX, posY + 2*height/3 - fontSize/2, fontSize, DARKBLUE);
}

void StatusBar::updateStatusLights() {
    for (auto i : status_lights) {
        if (i->getName() == "GPS") {
            i->setWorking(sfr::serialRead->gpsState == SensorState::VALID);
        } else if (i->getName() == "Altimeter") {
            i->setWorking(sfr::serialRead->altimeterState == SensorState::VALID);
        } else if (i->getName() == "Temperature") {
            i->setWorking(sfr::serialRead->temperatureState == SensorState::VALID);
        } else if (i->getName() == "Accelerometer") {
            i->setWorking(sfr::serialRead->accelerometerState == SensorState::VALID);
        } else if (i->getName() == "IMU") {
            i->setWorking(sfr::serialRead->imuState == SensorState::VALID);
        }
    }
}
