#pragma once

#include "screen.h"

class FanControlScreen : public Screen
{
public:
    ~FanControlScreen() override {};

    void draw(U8GLIB &u8g) override;

    ScreenType handleClick() override;
    void handleScroll(int steps) override;
};
