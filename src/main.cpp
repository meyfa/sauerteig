#include <Arduino.h>

#include "configuration.h"
#include "sensors.h"
#include "board_led.h"
#include "buzzer.h"
#include "rotary_encoder.h"
#include "enable_button.h"
#include "lcd.h"
#include "heating.h"
#include "fan.h"
#include "ui.h"

bool check_alarm()
{
    if (sensors_any_below(ALARM_TEMP_LOW))
    {
        return !ALARM_LOW_ONLY_ON || get_heater_enabled();
    }
    if (sensors_any_above(ALARM_TEMP_HIGH))
    {
        return true;
    }
    return false;
}

void setup()
{
    // allow for voltage stabilisation
    delay(POWERUP_DELAY);

    rotary_encoder_init();
    enable_button_init();
    board_led_init();
    buzzer_init();

    sensors_init();
    heating_init();
    fan_init();

    lcd_init();
    ui_init();

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
    // polling and safety check
    sensors_update();
    static bool alarm = false;
    if (check_alarm())
    {
        buzzer_toggle(true);
        alarm = true;
    }
    else if (alarm)
    {
        buzzer_toggle(false);
        alarm = false;
    }

    // heater enable
    static bool lastEnableButton = false;
    bool enableButton = enable_button_pressed();
    if (lastEnableButton && !enableButton)
    {
        set_heater_enabled(!get_heater_enabled());
        board_led_toggle(get_heater_enabled());
    }
    lastEnableButton = enableButton;

    // heater update
    heating_update();

    // ui
    ui_update();

    // LCD update
    static unsigned long lastLcdDraw = 0;
    unsigned long now = millis();
    if (now > lastLcdDraw + 250)
    {
        lcd_draw(ui_draw);
        lastLcdDraw = now;
    }
}

ISR(TIMER4_COMPA_vect)
{
    rotary_encoder_update();
}
