#include "screen_targetsensor.h"
#include "sensors.h"
#include "heating.h"

void TargetSensorScreen::draw(U8GLIB &u8g)
{
    int selectedSensor = get_target_sensor();

    for (size_t i = 0; i < SENSOR_COUNT; ++i)
    {
        if ((int)i == selectedSensor)
        {
            u8g.drawLine(0, i * 14, 127, i * 14);
            u8g.drawLine(0, i * 14 + 12, 127, i * 14 + 12);
        }
        u8g.drawStr(8, i * 14 + 10, SENSOR_LABELS[i]);
    }
}

ScreenType TargetSensorScreen::handleClick()
{
    return MENU;
}

void TargetSensorScreen::handleScroll(int steps)
{
    set_target_sensor(get_target_sensor() + steps);
}
