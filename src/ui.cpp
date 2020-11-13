#include "ui.h"
#include "rotary_encoder.h"

#include "screen_main.h"
#include "screen_fancontrol.h"

Screen *currentScreen;

static void switchScreen(ScreenType type)
{
    Screen *newScreen;

    switch (type)
    {
    case MAIN:
        newScreen = new MainScreen();
        break;
    case FANCONTROL:
        newScreen = new FanControlScreen();
        break;
    default:
        return;
    }

    delete currentScreen;
    currentScreen = newScreen;
}

void ui_init()
{
    currentScreen = new MainScreen();
}

void ui_update()
{
    // handle encoder scroll
    static long lastEncoderPos = 0;
    long encoderPos = rotary_encoder_get_wheel();
    if (encoderPos != lastEncoderPos && currentScreen)
    {
        int diff = (int)(encoderPos - lastEncoderPos);
        currentScreen->handleScroll(diff);
    }
    lastEncoderPos = encoderPos;

    // handle encoder click
    static bool lastEncoderButton = false;
    bool encoderButton = rotary_encoder_get_button();
    if (encoderButton && !lastEncoderButton && currentScreen)
    {
        ScreenType nextScreenType = currentScreen->handleClick();
        switchScreen(nextScreenType);
    }
    lastEncoderButton = encoderButton;
}

void ui_draw(U8GLIB &u8g)
{
    if (currentScreen)
    {
        currentScreen->draw(u8g);
    }
}
