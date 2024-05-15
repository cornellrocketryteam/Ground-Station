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

    drawDataPoint("Altitude (m)", sfr::serialRead->altitudeMeters, posX + width_step, posY + height_step, offsetY);
    drawDataPoint("Altitude (ft)", sfr::serialRead->altitudeFeet, posX + 3*width_step, posY + height_step, offsetY);
    drawDataPoint("Temperature (c)", sfr::serialRead->temp, posX + 5*width_step, posY + height_step, offsetY);

    drawDataPoint("Gyro X (deg/s)", sfr::serialRead->gyroX, posX + width_step, posY + 3*height_step, offsetY);
    drawDataPoint("Gyro Y (deg/s)", sfr::serialRead->gyroY, posX + 3*width_step, posY + 3*height_step, offsetY);
    drawDataPoint("Gyro Z (deg/s)", sfr::serialRead->gyroZ, posX + 5*width_step, posY + 3*height_step, offsetY);

    drawDataPoint("Accel X (m/s²)", sfr::serialRead->accelX, posX + width_step, posY + 5*height_step, offsetY);
    drawDataPoint("Accel Y (m/s²)", sfr::serialRead->accelY, posX + 3*width_step, posY + 5*height_step, offsetY);
    drawDataPoint("Accel Z (m/s²)", sfr::serialRead->accelZ, posX + 5*width_step, posY + 5*height_step, offsetY);

    drawDataPoint("Gravity X (m/s²)", sfr::serialRead->gravityX, posX + width_step, posY + 7*height_step, offsetY);
    drawDataPoint("Gravity Y (m/s²)", sfr::serialRead->gravityY, posX + 3*width_step, posY + 7*height_step, offsetY);
    drawDataPoint("Gravity Z (m/s²)", sfr::serialRead->gravityZ, posX + 5*width_step, posY + 7*height_step, offsetY);
}
