#include <Arduino.h>

#include "board_led.h"
#include "pins.h"

void board_led_init()
{
    pinMode(LED_PIN, OUTPUT);
}

void board_led_toggle(bool state)
{
    digitalWrite(LED_PIN, state ? HIGH : LOW);
}
