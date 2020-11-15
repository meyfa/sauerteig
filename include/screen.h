#pragma once

#include "U8glib.h"

enum ScreenType
{
    NO_CHANGE,

    MAIN,
    MENU,
    TARGET_SENSOR,
    FANCONTROL,
    CUTOFF_SET,
};

class Screen
{
public:
    virtual ~Screen(){};

    virtual void draw(U8GLIB &u8g) = 0;

    virtual ScreenType handleClick() = 0;
    virtual void handleScroll(int steps) = 0;
};
