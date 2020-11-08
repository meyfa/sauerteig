#include <Arduino.h>

#include "heating.h"

float targetTemperature = SET_TEMP_DEFAULT;

float get_target_temperature()
{
    return targetTemperature;
}

void set_target_temperature(float temp)
{
    targetTemperature = constrain(temp, SET_TEMP_MIN, SET_TEMP_MAX);
}
