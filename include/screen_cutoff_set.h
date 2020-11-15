#pragma once

#include "screen.h"

class CutoffSetScreen : public Screen
{
public:
    ~CutoffSetScreen() override{};

    void draw(U8GLIB &u8g) override;

    ScreenType handleClick() override;
    void handleScroll(int steps) override;
};
