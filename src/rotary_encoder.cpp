#include <Arduino.h>

#include "rotary_encoder.h"
#include "pins.h"
#include "util.h"

// Direction: -1 means direction is inverted
const signed short ENCODER_DIRECTION = -1;

struct
{
    volatile bool en1, en2, enc;
} buttons;

volatile int wheelPosition = 0;

static int to_phase(bool a, bool b)
{
    if (!a && !b)
        return 0;
    if (!a && b)
        return 1;
    if (a && b)
        return 2;
    return 3;
}

static int phase_difference(int oldPhase, int newPhase)
{
    switch (oldPhase)
    {
    case 0:
        return newPhase == 0 ? 0 : (newPhase == 3 ? -1 : 1);
    case 1:
        return newPhase == 1 ? 0 : (newPhase == 0 ? -1 : 1);
    case 2:
        return newPhase == 2 ? 0 : (newPhase == 1 ? -1 : 1);
    case 3:
        return newPhase == 3 ? 0 : (newPhase == 2 ? -1 : 1);
    }
    return 0;
}

void rotary_encoder_init()
{
    // encoder signals A, B
    pinMode(BTN_EN1, INPUT_PULLUP);
    pinMode(BTN_EN2, INPUT_PULLUP);

    // encoder button
    pinMode(BTN_ENC, INPUT_PULLUP);
}

void rotary_encoder_update()
{
    // read all buttons

    buttons.en1 = digitalRead(BTN_EN1) == LOW;
    buttons.en2 = digitalRead(BTN_EN2) == LOW;
    buttons.enc = digitalRead(BTN_ENC) == LOW;

    // encoder handling

    static unsigned long lastUpdateTime = 0;

    static int lastPhase = 0;
    static int cumulativeDiff = 0;

    int phase = to_phase(buttons.en1, buttons.en2);
    int diff = phase_difference(lastPhase, phase);

    unsigned long now = millis();
    if (diff != 0)
    {
        lastUpdateTime = now;
    }

    if (now - lastUpdateTime > 500)
    {
        cumulativeDiff = 0;
    }
    else
    {
        cumulativeDiff += diff;
        if (abs(cumulativeDiff) > 2)
        {
            wheelPosition += ENCODER_DIRECTION * sgn(cumulativeDiff);
            cumulativeDiff = 0;
        }
    }

    lastPhase = phase;
}

bool rotary_encoder_get_button()
{
    return buttons.enc;
}

int rotary_encoder_get_wheel()
{
    return wheelPosition;
}
