#include "statusbar.h"

/**
 * Constructor to create the Status Lights in the StatusBar constructor
*/
StatusLight::StatusLight(const char* _name, float _radius, bool _isWorking){
    name = _name; 
    radius = _radius; 
    isWorking = _isWorking; 
}

bool StatusLight::getWorking(){
    return isWorking; 
}
float StatusLight::getRadius(){
    return radius; 
}
const char* StatusLight::getName(){
    return name; 
}

StatusBar::StatusBar(int posX, int posY, int wid, int hght){
     StatusLight GPS("GPS",10,true); 
     StatusLight Altimeter("Altimeter",10,true); 
     StatusLight Temperature("Temperature",10,true); 
     StatusLight Gyroscope("Gyroscope",10,true); 
     StatusLight IMU("IMU",10,true); 
     StatusLight SD("SD",10,true); 

    statusLights.push_back(GPS); 
    statusLights.push_back(Altimeter); 
    statusLights.push_back(Temperature); 
    statusLights.push_back(Gyroscope); 
    statusLights.push_back(IMU); 
    statusLights.push_back(SD); 

    barPositionX = posX; 
    barPositionY = posY; 
    width = wid; 
    height = hght; 
}

void StatusBar::drawBar(){

    DrawRectangle(barPositionX - 50,barPositionY - 50,200*statusLights.size(), 100, WHITE);

    int drawX = barPositionX;  
    int drawY = barPositionY; 

    int acc = 0; 
    while (acc < statusLights.size()){
        if (statusLights.at(acc).getWorking()){
            DrawCircle(drawX, drawY, statusLights.at(acc).getRadius(), GREEN); 
        } else {
            DrawCircle(drawX, drawY, statusLights.at(acc).getRadius(), RED); 
        }
        // Draw the name of the bar 
        DrawText( statusLights.at(acc).getName(), drawX-25, drawY - 50, 20,BLUE);
        drawX += 200; 
        acc += 1; 
    }
}

