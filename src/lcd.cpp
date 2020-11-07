#include <Arduino.h>

#include "lcd.h"
#include "pins.h"

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
    u8g.firstPage();
    do
    {
        u8g.setFont(u8g_font_unifont);
        u8g.drawFrame(0, 0, 128, 31);
        u8g.drawStr(15, 13, "Target");

        u8g.drawFrame(0, 33, 128, 31);
        u8g.drawStr(15, 46, "Current");
    } while (u8g.nextPage());
}
