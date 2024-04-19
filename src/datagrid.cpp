#include "datagrid.h"
#include "sfr.h"
#include <math.h>
#include "raylib.h"

template <typename T>
void drawDataPoint(std::string title, T value, int posX, int posY, int offsetY) {
    int fontSize = 20;

    int title_text_width = MeasureText(title.c_str(), fontSize);
    DrawText(title.c_str(), posX - title_text_width/2, posY - fontSize/2 - offsetY, fontSize, WHITE);

    std::string stringValue = fmt::format("{:.3f}", value);
    int value_text_width = MeasureText(stringValue.c_str(), fontSize);
    DrawText(stringValue.c_str(), posX - value_text_width/2, posY - fontSize/2 + offsetY, fontSize, WHITE);
}

void DataGrid::draw(int posX, int posY, int width, int height)
{
    int width_step = width / 6;
    int height_step = height / 8;
    int offsetY = height / 32;

    drawDataPoint("Altitude", sfr::serialRead->altitude, posX + width_step, posY + height_step, offsetY);
    drawDataPoint("Longitude", sfr::serialRead->longitude, posX + 3*width_step, posY + height_step, offsetY);
    drawDataPoint("Latitude", sfr::serialRead->latitude, posX + 5*width_step, posY + height_step, offsetY);

    drawDataPoint("Gyro X", sfr::serialRead->gyroX, posX + width_step, posY + 3*height_step, offsetY);
    drawDataPoint("Gyro Y", sfr::serialRead->gyroY, posX + 3*width_step, posY + 3*height_step, offsetY);
    drawDataPoint("Gyro Z", sfr::serialRead->gyroZ, posX + 5*width_step, posY + 3*height_step, offsetY);

    drawDataPoint("Accel X", sfr::serialRead->accelX, posX + width_step, posY + 5*height_step, offsetY);
    drawDataPoint("Accel Y", sfr::serialRead->accelY, posX + 3*width_step, posY + 5*height_step, offsetY);
    drawDataPoint("Accel Z", sfr::serialRead->accelZ, posX + 5*width_step, posY + 5*height_step, offsetY);

    drawDataPoint("Gravity X", sfr::serialRead->gravityX, posX + width_step, posY + 7*height_step, offsetY);
    drawDataPoint("Gravity Y", sfr::serialRead->gravityY, posX + 3*width_step, posY + 7*height_step, offsetY);
    drawDataPoint("Gravity Z", sfr::serialRead->gravityZ, posX + 5*width_step, posY + 7*height_step, offsetY);
}
