#include "screen_main.h"
#include "sensors.h"
#include "heating.h"

const float DEGREES_PER_SCROLL_STEP = 0.5f;

void MainScreen::draw(U8GLIB &u8g)
{
    int targetSensor = get_target_sensor();
    float targetTemp = get_target_temperature();

    u8g.drawFrame(0, 0, 128, 18);
    u8g.drawFrame(0, 20, 128, 44);

    u8g.drawStr(6, 13, "Target");
    u8g.setPrintPos(86, 13);
    u8g.print(targetTemp, 1);
    u8g.print(" \260C");

    for (size_t sensorId = 0; sensorId < SENSOR_COUNT; ++sensorId)
    {
        int yOffset = 26 + sensorId * 12;
        float sensorTemp = sensors_get_temperature(sensorId);
        if (targetSensor == (int)sensorId)
        {
            u8g.drawDisc(9, yOffset + 4, 2);
        }
        u8g.drawStr(15, yOffset + 8, SENSOR_LABELS[sensorId]);
        u8g.setPrintPos(86, yOffset + 8);
        if (sensorTemp < MIN_SENSOR_TEMP)
        {
            u8g.print('-');
            continue;
        }
        u8g.print(sensorTemp, 1);
        u8g.print(" \260C");
    }
}

ScreenType MainScreen::handleClick()
{
    return MENU;
}

void MainScreen::handleScroll(int steps)
{
    set_target_temperature(get_target_temperature() + DEGREES_PER_SCROLL_STEP * steps);
}
