#include "screen_main.h"
#include "sensors.h"
#include "heating.h"

const float DEGREES_PER_SCROLL_STEP = 0.5f;

void MainScreen::draw(U8GLIB &u8g)
{
    float targetTemp = get_target_temperature();
    float currentTemp0 = sensors_get_temperature(0);
    float currentTemp1 = sensors_get_temperature(1);
    float currentTemp2 = sensors_get_temperature(2);

    u8g.drawFrame(0, 0, 128, 18);
    u8g.drawFrame(0, 20, 128, 44);

    u8g.drawStr(6, 13, "Target");
    u8g.setPrintPos(90, 13);
    u8g.print(targetTemp, 1);

    u8g.drawStr(6, 34, "Bed");
    u8g.setPrintPos(90, 34);
    u8g.print(currentTemp0, 1);

    u8g.drawStr(6, 46, "Case 1");
    u8g.setPrintPos(90, 46);
    if (currentTemp1 < MIN_SENSOR_TEMP)
    {
        u8g.print('-');
    }
    else
    {
        u8g.print(currentTemp1, 1);
    }

    u8g.drawStr(6, 58, "Case 2");
    u8g.setPrintPos(90, 58);
    if (currentTemp2 < MIN_SENSOR_TEMP)
    {
        u8g.print('-');
    }
    else
    {
        u8g.print(currentTemp2, 1);
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
