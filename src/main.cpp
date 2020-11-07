#include <Arduino.h>

#include "lcd.h"

void setup() {
    lcd_init();
}

void loop() {
    lcd_draw();

    delay(50);
}
