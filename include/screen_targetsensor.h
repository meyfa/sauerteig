#pragma once

#include "screen.h"

class TargetSensorScreen : public Screen
{
public:
    ~TargetSensorScreen() override{};

    void draw(U8GLIB &u8g) override;

    ScreenType handleClick() override;
    void handleScroll(int steps) override;
};
