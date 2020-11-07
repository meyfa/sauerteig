#pragma once

typedef int8_t pin_t;

// LIMIT SWITCHES
#define X_MIN_PIN                            3
#define X_MAX_PIN                            2
#define Y_MIN_PIN                           14
#define Y_MAX_PIN                           15
#define Z_MIN_PIN                           18
#define Z_MAX_PIN                           19

// TEMPERATURE SENSORS
#define TEMP_0_PIN                          13  // Analog Input
#define TEMP_1_PIN                          15  // Analog Input
#define TEMP_BED_PIN                        14  // Analog Input

// HEATERS / FANS
#define RAMPS_D8_PIN                         8
#define RAMPS_D9_PIN                         9
#define RAMPS_D10_PIN                       10
#define HEATER_0_PIN             RAMPS_D10_PIN
#define HEATER_BED_PIN            RAMPS_D8_PIN
#define FAN_PIN                   RAMPS_D9_PIN

// MISC
#define SDSS                                53
#define LED_PIN                             13
#define PS_ON_PIN                           12

// LCD
#define LCD_PINS_RS                         16
#define LCD_PINS_ENABLE                     17
#define LCD_PINS_D4                         23
#define LCD_PINS_D5                         25
#define LCD_PINS_D6                         27
#define LCD_PINS_D7                         29

#define BEEPER_PIN                          37
#define BTN_EN1                             31
#define BTN_EN2                             33
#define BTN_ENC                             35
#define SD_DETECT_PIN                       49
#define KILL_PIN                            41
