#include <Arduino.h>

#include "buzzer.h"
#include "pins.h"

void buzzer_init()
{
    pinMode(BEEPER_PIN, OUTPUT);
    digitalWrite(BEEPER_PIN, LOW);
}

void buzzer_toggle(bool state)
{
    digitalWrite(BEEPER_PIN, state ? HIGH : LOW);
}
