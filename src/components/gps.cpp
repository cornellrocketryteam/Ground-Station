#include "gps.h"
#include <iostream> 
#include "../dataprocessing.h"

void GPS::drawLaunchSite(){
      DrawTexture(launchSiteTexture, 800, 0, RAYWHITE);
      DrawRectangleLinesEx((Rectangle){800,0,(float)imageWidth,(float)imageHeight}, 3,BLACK); 
}

void GPS::drawRocketPosition(){

}

void GPS::updatePosition(){
    currentLatitude = SerialRead::serialValues["latitude"]; 
    currentLongitude = SerialRead::serialValues["longitude"]; 
}

GPS::GPS(){
    /**
     * TODO: Change this to be based on the current screen's width and height s
    */
    imageWidth = 800;
    imageHeight = 500; 

    launchSiteImage = LoadImage("GroundStation2.0/img/launchSite.png"); 
    ImageResize(&launchSiteImage,imageWidth,imageHeight); 
    launchSiteTexture = LoadTextureFromImage(launchSiteImage);
    UnloadImage(launchSiteImage);
}
GPS::~GPS(){
     UnloadTexture(launchSiteTexture); 
}
