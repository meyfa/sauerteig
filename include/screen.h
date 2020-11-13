#pragma once

#include "U8glib.h"

enum ScreenType
{
    NO_CHANGE,

    MAIN,
    MENU,
    FANCONTROL,
};

class Screen
{
public:
    virtual ~Screen(){};

    virtual void draw(U8GLIB &u8g) = 0;

    virtual ScreenType handleClick() = 0;
    virtual void handleScroll(int steps) = 0;
};
