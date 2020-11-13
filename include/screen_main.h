#pragma once

#include "screen.h"

class MainScreen : public Screen
{
public:
    ~MainScreen() override {};

    void draw(U8GLIB &u8g) override;

    ScreenType handleClick() override;
    void handleScroll(int steps) override;
};
