#include "gps.h"
#include <iostream> 
#include "../dataprocessing.h"

void GPS::drawLaunchSite(){
      DrawTexture(launchSiteTexture, 800, 0, RAYWHITE);
}

void GPS::drawRocketPosition(){

}

void GPS::updatePosition(){
    currentLatitude = SerialRead::serialValues["latitude"]; 
    currentLongitude = SerialRead::serialValues["longitude"]; 
}

GPS::GPS(){
    /**
     * TODO: Fix this 
    */
    launchSiteImage = LoadImage("GroundStation2.0/img/launchSite.png"); 
    ImageResize(&launchSiteImage,800,500); 
    launchSiteTexture = LoadTextureFromImage(launchSiteImage);
    UnloadImage(launchSiteImage);
}
GPS::~GPS(){
     UnloadTexture(launchSiteTexture); 
}
