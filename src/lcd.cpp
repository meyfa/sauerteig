#include <Arduino.h>

#include "lcd.h"
#include "pins.h"
#include "sensors.h"
#include "heating.h"

#include "U8glib.h"

U8GLIB_ST7920_128X64_1X u8g(LCD_PINS_D4, LCD_PINS_ENABLE, LCD_PINS_RS);

void lcd_init()
{
    if (u8g.getMode() == U8G_MODE_R3G3B2)
    {
        u8g.setColorIndex(255); // white
    }
    else if (u8g.getMode() == U8G_MODE_GRAY2BIT)
    {
        u8g.setColorIndex(3); // max intensity
    }
    else if (u8g.getMode() == U8G_MODE_BW)
    {
        u8g.setColorIndex(1); // pixel on
    }
    else if (u8g.getMode() == U8G_MODE_HICOLOR)
    {
        u8g.setHiColorByRGB(255, 255, 255);
    }
}

void lcd_draw()
{
    float targetTemp = get_target_temperature();
    float currentTemp0 = sensors_get_temperature(0);
    float currentTemp1 = sensors_get_temperature(1);
    float currentTemp2 = sensors_get_temperature(2);

    u8g.firstPage();
    do
    {
        u8g.setFont(u8g_font_helvR08);

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
        if (currentTemp1 < MIN_SENSOR_TEMP) {
            u8g.print('-');
        } else {
            u8g.print(currentTemp1, 1);
        }

        u8g.drawStr(6, 58, "Case 2");
        u8g.setPrintPos(90, 58);
        if (currentTemp2 < MIN_SENSOR_TEMP) {
            u8g.print('-');
        } else {
            u8g.print(currentTemp2, 1);
        }
    } while (u8g.nextPage());
}
