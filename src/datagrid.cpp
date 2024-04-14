#include "datagrid.h"
#include "sfr.h"
#include <math.h>
#include "raylib.h"

/**
 * Constructor to create the Status Lights in the StatusBar constructor
*/
DataPoint::DataPoint(std::string title) : title(title)
{
}

std::string DataPoint::getTitle() {
    return title;
}

float DataPoint::getValue() {
    return value;
}

void DataPoint::setValue(float val){
    value = val; 
}

DataGrid::DataGrid()
{
    data_points.emplace_back(new DataPoint("Altitude"));
    data_points.emplace_back(new DataPoint("Longitude"));
    data_points.emplace_back(new DataPoint("Latitude"));
    data_points.emplace_back(new DataPoint("Gyro X"));
    data_points.emplace_back(new DataPoint("Gyro Y"));
    data_points.emplace_back(new DataPoint("Gyro Z"));
    data_points.emplace_back(new DataPoint("Accel X"));
    data_points.emplace_back(new DataPoint("Accel Y"));
    data_points.emplace_back(new DataPoint("Accel Z"));
    data_points.emplace_back(new DataPoint("Gravity X"));
    data_points.emplace_back(new DataPoint("Gravity Y"));
    data_points.emplace_back(new DataPoint("Gravity Z"));
}

void DataGrid::draw(int posX, int posY, int width, int height)
{
    updateValues();

    int fontSize = 20;
    int width_step = width / 6;
    int height_step = height / 8;
    int offsetY = height / 32;
    for (int i = 0; i < data_points.size(); ++i) {
        DataPoint status_light = *(data_points.at(i));
        int x = width_step*(2*(i%3)+1);
        int y = height_step*(2*floor(i/3)+1);

        int title_text_width = MeasureText(status_light.getTitle().c_str(), fontSize);
        DrawText(status_light.getTitle().c_str(), posX + x - title_text_width/2, posY + y - fontSize/2 - offsetY, fontSize, WHITE);


        //printf("%s%f%s", status_light.getTitle().c_str(), status_light.getValue(), "\n");

        std::string value = std::to_string(status_light.getValue());
        int value_text_width = MeasureText(value.c_str(), fontSize);
        DrawText(value.c_str(), posX + x - value_text_width/2, posY + y - fontSize/2 + offsetY, fontSize, WHITE);
    }
}

void DataGrid::updateValues() {
    for (auto elem : data_points){

        // printf("%s%f", elem.getTitle().c_str(), sfr::serialRead.getValue(elem.getTitle()));
        
        elem->setValue(sfr::serialRead->getValue(elem->getTitle()));

        //printf("%s%f%n", elem.getTitle().c_str(), elem.getValue(), "\n");
    }

}
