#pragma once

#include "screen.h"

class MenuScreen : public Screen
{
public:
    ~MenuScreen() override{};

    void draw(U8GLIB &u8g) override;

    ScreenType handleClick() override;
    void handleScroll(int steps) override;
};
