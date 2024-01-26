#include "sensorDisplay.h"

Graph createGraph(float x, float y, float width, float height, Color color){
    Graph graph; 
    graph.bounds = (Rectangle){x,y,width,height}; 
    graph.color = color; 
    return graph; 
}

void drawGraph(Graph graph){
    DrawRectangleRec(graph.bounds, graph.color); 
}

textDisplay createTextDisplay(float x, float y, float width, float height, Color color, const char* name){
    textDisplay textdisplay;
    textdisplay.bounds = (Rectangle){x,y,width,height}; 
    textdisplay.color = color; 
    textdisplay.text = name; 
    return textdisplay; 
}

void drawTextDisplay(textDisplay textdisplay){
    DrawRectangleRec(textdisplay.bounds, textdisplay.color); 
    DrawText(textdisplay.text, (int)(textdisplay.bounds.x + textdisplay.bounds.width / 2 - MeasureText(textdisplay.text, 20) / 2),
                 (int)(textdisplay.bounds.y + textdisplay.bounds.height / 2 - 10), 20, BLACK);
}

SensorDisplay::SensorDisplay(){
    //initialize all text displays and add them to the text displays vector 
    textDisplayWidth= GetScreenHeight() / 1400; 
    textDisplayHeight = textDisplayWidth / 2; 

    latitude = createTextDisplay(100,300,textDisplayWidth,textDisplayHeight,WHITE, "Latitude");
    longitude = createTextDisplay(200,300,textDisplayWidth,textDisplayHeight,WHITE, "Longitude");
    elevation = createTextDisplay(300,300,textDisplayWidth,textDisplayHeight,WHITE, "Elevation");
    accel_x = createTextDisplay(400,300,textDisplayWidth,textDisplayHeight,WHITE, "Accel_X");
    accel_y = createTextDisplay(500,300,textDisplayWidth,textDisplayHeight,WHITE, "Accel_Y");
    accel_z = createTextDisplay(600,300,textDisplayWidth,textDisplayHeight,WHITE, "Accel_Z");
    gyro_x = createTextDisplay(700,300,textDisplayWidth,textDisplayHeight,WHITE, "Gyro_X");
    gyro_y = createTextDisplay(800,300,textDisplayWidth,textDisplayHeight,WHITE, "Gyro_Y");
    gyro_z = createTextDisplay(900,300,textDisplayWidth,textDisplayHeight,WHITE, "Gyro_Z");
    mag_x = createTextDisplay(1000,300,textDisplayWidth,textDisplayHeight,WHITE, "Mag_X");
    mag_y = createTextDisplay(1100,300,textDisplayWidth,textDisplayHeight,WHITE, "Mag_Y");
    mag_z = createTextDisplay(1200,300,textDisplayWidth,textDisplayHeight,WHITE, "Mag_Z");
    temp = createTextDisplay(1300,300,textDisplayWidth,textDisplayHeight,WHITE, "Temperature");
    

    textdisplays.push_back(latitude); 
    textdisplays.push_back(longitude); 
    textdisplays.push_back(accel_x); 
    textdisplays.push_back(accel_y); 
    textdisplays.push_back(accel_z); 
    textdisplays.push_back(gyro_x); 
    textdisplays.push_back(gyro_y); 
    textdisplays.push_back(gyro_z); 
    textdisplays.push_back(elevation); 
    textdisplays.push_back(mag_x); 
    textdisplays.push_back(mag_y); 
    textdisplays.push_back(mag_z); 
    textdisplays.push_back(temp); 

    //initialize all graphs and add them to the graphs vector
}

void SensorDisplay::drawComponents(){
    // draw all of the text displays 
    for (int i = 0; i < textdisplays.size(); i++){
        drawTextDisplay(textdisplays.at(i)); 
    }

    // draw all of the graphs 
    for (int i = 0; i < graphs.size(); i++){
        drawGraph(graphs.at(i)); 
    }
}

void SensorDisplay::updateSizes(){
    textDisplayWidth= GetScreenHeight() / 1400; 
    textDisplayHeight = textDisplayWidth / 2;
}
