#include "statusbar.h"

/**
 * Constructor to create the Status Lights in the StatusBar constructor
*/
StatusLight createStatusLight(const char* name, float radius, bool isWorking){
    StatusLight temp; 
    temp.name = name; 
    temp.radius = radius; 
    temp.isWorking = isWorking;
    return temp; 
}

StatusBar::StatusBar(int posX, int posY, int wid, int hght){
     StatusLight GPS = createStatusLight("GPS",10,true); 
     StatusLight Altimeter = createStatusLight("Altimeter",10,true); 
     StatusLight Temperature = createStatusLight("Temperature",10,true); 
     StatusLight Gyroscope = createStatusLight("Gyroscope",10,true); 
     StatusLight IMU = createStatusLight("IMU",10,true); 
     StatusLight SD = createStatusLight("SD",10,true); 

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
        if (statusLights.at(acc).isWorking){
            DrawCircle(drawX, drawY, statusLights.at(acc).radius, GREEN); 
        } else {
            DrawCircle(drawX, drawY, statusLights.at(acc).radius, RED); 
        }
        // Draw the name of the bar 
        DrawText( statusLights.at(acc).name, drawX, drawY - 50, 20,BLUE);
        drawX += 200; 
        acc += 1; 
    }
}

void StatusBar::updateSensor(const char* name ){
    for (auto i : statusLights){
        if (i.name == name){
            
        }
    }
}