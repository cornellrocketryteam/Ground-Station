#include "gps.h"
#include "dataprocessing.cpp"

void GPS::drawLaunchSite(){

}

void GPS::drawRocketPosition(){

}

void GPS::updatePosition(){
    currentLatitude = SerialRead::serialValues["latitude"]; 
    currentLongitude = SerialRead::serialValues["longitude"]; 
}

GPS::GPS(){
    
}