#include <Arduino.h>

#include "sensors.h"
#include "board_led.h"
#include "buzzer.h"
#include "rotary_encoder.h"
#include "lcd.h"
#include "heating.h"

const float DEGREES_PER_ENCODER_STEP = 0.5f;

void setup()
{
    sensors_init();
    rotary_encoder_init();

    board_led_init();
    buzzer_init();

    lcd_init();
}

void loop()
{
    // polling
    sensors_update();
    rotary_encoder_update();

    // handle encoder temperature change
    static long lastEncoderPos = 0;
    long encoderPos = rotary_encoder_get_wheel();
    if (encoderPos != lastEncoderPos)
    {
        int diff = (int)(encoderPos - lastEncoderPos);
        set_target_temperature(get_target_temperature() + DEGREES_PER_ENCODER_STEP * diff);
        lastEncoderPos = encoderPos;
    }

    // button test
    board_led_toggle(rotary_encoder_get_button());
    buzzer_toggle(rotary_encoder_get_button());

    // LCD update
    static unsigned long lastLcdDraw = millis();
    unsigned long now = millis();
    if (now > lastLcdDraw + 500)
    {
        lcd_draw();
        lastLcdDraw = now;
    }
}
