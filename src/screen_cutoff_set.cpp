#include "screen_cutoff_set.h"
#include "heating.h"

const float DEGREES_PER_SCROLL_STEP = 0.5f;

void CutoffSetScreen::draw(U8GLIB &u8g)
{
    float cutoffTemp = get_cutoff_temperature();

    u8g.drawStr(0, 26, "Cutoff Temperature");

    u8g.drawStr(32, 44, "<");
    u8g.drawStr(92, 44, ">");

    u8g.drawFrame(40, 33, 48, 14);

    u8g.setPrintPos(44, 44);
    u8g.print(cutoffTemp, 1);
    u8g.print(" \260C");
}

ScreenType CutoffSetScreen::handleClick()
{
    return MENU;
}

void CutoffSetScreen::handleScroll(int steps)
{
    set_cutoff_temperature(get_cutoff_temperature() + DEGREES_PER_SCROLL_STEP * steps);
}
