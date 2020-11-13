#include "screen_fancontrol.h"
#include "fan.h"

const int SPEED_CHANGE_PER_SCROLL_STEP = 10;

void FanControlScreen::draw(U8GLIB &u8g)
{
    int fanSpeed = fan_get_speed();

    u8g.drawStr(0, 26, "Fan Speed");
    u8g.setPrintPos(94, 26);
    u8g.print(fanSpeed * 100 / 255);
    u8g.print(" %");

    u8g.drawFrame(0, 30, 128, 12);
    u8g.drawBox(2, 32, fanSpeed * 124 / 255, 8);
}

ScreenType FanControlScreen::handleClick()
{
    return MENU;
}

void FanControlScreen::handleScroll(int steps)
{
    fan_set_speed(fan_get_speed() + SPEED_CHANGE_PER_SCROLL_STEP * steps);
}
