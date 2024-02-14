#include "gps.h"
#include <iostream> 
#include "../dataprocessing.h"

void GPS::drawLaunchSite(){
      ImageDrawRectangle(&launchSiteImage, GetScreenWidth(), 0, GetScreenWidth()/2, GetScreenHeight()/2, RAYWHITE);
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
    std::cout << "IMAGE " << launchSiteImage.data << std::endl; 
    ImageResize(&launchSiteImage, GetScreenWidth() / 2, GetScreenHeight() / 2);
}
GPS::~GPS(){
     UnloadImage(launchSiteImage); 
}
