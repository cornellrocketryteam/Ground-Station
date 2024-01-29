#include "sensorDisplay.h"

Graph createGraph(float x, float y, float width, float height, Color color){
    Graph graph; 
    graph.bounds = (Rectangle){x,y,width,height}; 
    graph.color = color; 
    return graph; 
}

void drawGraph(Graph graph){
    DrawRectangleRec(graph.bounds, graph.color); 
    //DrawRectangle(graph.bounds.x,graph.bounds.y,graph.bounds.width,graph.bounds.height,graph.color);

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
                 (int)(textdisplay.bounds.y + textdisplay.bounds.height / 2 - 10), 20, WHITE);
}

SensorDisplay::SensorDisplay(){
    //initialize all text displays and add them to the text displays vector

    updateSizes(); 

    latitude = createTextDisplay(100,300,textDisplayWidth,textDisplayHeight,RAYWHITE, "Latitude");
    longitude = createTextDisplay(100,400,textDisplayWidth,textDisplayHeight,RAYWHITE, "Longitude");
    elevation = createTextDisplay(100,500,textDisplayWidth,textDisplayHeight,RAYWHITE, "Elevation");
    accel_x = createTextDisplay(100,600,textDisplayWidth,textDisplayHeight,RAYWHITE, "Accel_X");
    accel_y = createTextDisplay(100,700,textDisplayWidth,textDisplayHeight,RAYWHITE, "Accel_Y");
    accel_z = createTextDisplay(100,800,textDisplayWidth,textDisplayHeight,WHITE, "Accel_Z");
    gyro_x = createTextDisplay(100,900,textDisplayWidth,textDisplayHeight,WHITE, "Gyro_X");
    gyro_y = createTextDisplay(300,300,textDisplayWidth,textDisplayHeight,WHITE, "Gyro_Y");
    gyro_z = createTextDisplay(300,400,textDisplayWidth,textDisplayHeight,WHITE, "Gyro_Z");
    mag_x = createTextDisplay(300,500,textDisplayWidth,textDisplayHeight,WHITE, "Mag_X");
    mag_y = createTextDisplay(300,600,textDisplayWidth,textDisplayHeight,WHITE, "Mag_Y");
    mag_z = createTextDisplay(300,700,textDisplayWidth,textDisplayHeight,WHITE, "Mag_Z");
    temp = createTextDisplay(300,800,textDisplayWidth,textDisplayHeight,WHITE, "Temperature");
    
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
    elevationGraph = createGraph(screenWidth/2,0,screenWidth/2, screenHeight/2 - 25,RAYWHITE); 
    temperatureGraph = createGraph(screenWidth/2,screenHeight/2,screenWidth/2, screenHeight/2 -25,RAYWHITE); 

    graphs.push_back(elevationGraph);
    graphs.push_back(temperatureGraph); 
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

//TODO remove the hardcoding once we figure out how to get the actual width
// of the screen 
void SensorDisplay::updateSizes(){
    textDisplayWidth= 1600 / 1600; 
    textDisplayHeight = textDisplayWidth / 2;
}
