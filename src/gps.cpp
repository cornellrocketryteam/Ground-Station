#include "gps.h"
#include <iostream> 
#include "serialread.h"

GPS::~GPS(){
    UnloadTexture(launchSiteTexture);
}

void GPS::draw(int posX, int posY, int width, int height){
    if (launchSiteTexture.width != width && launchSiteTexture.height != height) {
        std::cout << "Resized!" << std::endl;
        Image launchSiteImage = LoadImage("img/launchSite.png");
        ImageResize(&launchSiteImage, width, height);
        launchSiteTexture = LoadTextureFromImage(launchSiteImage);
        UnloadImage(launchSiteImage);
    }

    DrawTexture(launchSiteTexture, posX, posY, WHITE);
    DrawCircle(posX+width/2, posY+height/2, 5, RED);
}

void GPS::updatePosition(){
    // currentLatitude = SerialRead::serialValues["latitude"];
    // currentLongitude = SerialRead::serialValues["longitude"];
}
