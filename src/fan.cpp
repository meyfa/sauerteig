#include <Arduino.h>

#include "fan.h"
#include "pins.h"

int currentSpeed = 0;

void fan_init()
{
    pinMode(RAMPS_D9_PIN, OUTPUT);

    // PWM using timer2 (responsible for pins 9 and 10)

    cli();

    // prescaler = 1024
    TCCR2B = _BV(CS22) | _BV(CS21) | _BV(CS20);
    // COM2A1: activate on 10, COM2B1: activate on 9,
    // WGM21+WGM20: Fast PWM with TOP=0xFF
    TCCR2A = _BV(WGM21) | _BV(WGM20); // | _BV(COM2A1) | _BV(COM2B1)
    // set duty cycle 0..255 (A = pin 10, B = pin 9)
    OCR2A = 0;
    OCR2B = 0;

    sei();
}

int fan_get_speed()
{
    return currentSpeed;
}

void fan_set_speed(int speed)
{
    currentSpeed = constrain(speed, 0, 255);

    if (speed == 0)
    {
        // toggle COM2B1 off
        TCCR2A &= ~_BV(COM2B1);
        OCR2B = 0;
        return;
    }

    // toggle COM2B1 on
    TCCR2A |= _BV(COM2B1);
    OCR2B = currentSpeed;
}
