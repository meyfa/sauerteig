#include <Arduino.h>

#include "enable_button.h"
#include "pins.h"

void enable_button_init()
{
    pinMode(KILL_PIN, INPUT_PULLUP);
}

bool enable_button_pressed()
{
    return digitalRead(KILL_PIN) == LOW;
}
