#include <Arduino.h>

#include "pins.h"
#include "sensors.h"
#include "board_led.h"
#include "buzzer.h"
#include "rotary_encoder.h"
#include "lcd.h"
#include "heating.h"
#include "fan.h"

const float DEGREES_PER_ENCODER_STEP = 0.5f;

void setup()
{
    sensors_init();
    rotary_encoder_init();

    board_led_init();
    buzzer_init();

    lcd_init();

    heating_init();
    set_heater_enabled(true);

    fan_init();

    // rotary encoder timer interrupt
    // set timer4 interrupt at 248 Hz (should be enough for the rotary encoder)

    cli();
    TCCR4A = 0;
    TCCR4B = 0;
    // reset counter value
    TCNT4 = 0;
    // WGM42: CTC mode (counter resets after reaching OCR4A),
    // CS42+CS40: prescaler = 1024
    TCCR4B = _BV(WGM42) | _BV(CS42) | _BV(CS40);
    // set counter limit
    OCR4A = 15624 / 248; // = (16 * 10^6 / 1024 - 1) / 248
    // enable timer compare interrupt
    TIMSK4 |= _BV(OCIE4A);
    sei();
}

void loop()
{
    // polling
    sensors_update();

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
    // board_led_toggle(rotary_encoder_get_button());
    // buzzer_toggle(rotary_encoder_get_button());

    // heater
    heating_update();
    board_led_toggle(get_heater_active());

    // LCD update
    static unsigned long lastLcdDraw = 0;
    unsigned long now = millis();
    if (now > lastLcdDraw + 250)
    {
        lcd_draw();
        lastLcdDraw = now;
    }
}

ISR(TIMER4_COMPA_vect)
{
    rotary_encoder_update();
}
