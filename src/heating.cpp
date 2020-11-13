#include <Arduino.h>

#include "heating.h"
#include "sensors.h"
#include "pins.h"

int targetSensor = SET_SENSOR_DEFAULT;
float targetTemperature = SET_TEMP_DEFAULT;
bool enabled = false;
bool active = false;

int get_target_sensor()
{
    return targetSensor;
}

void set_target_sensor(int sensor)
{
    targetSensor = constrain(sensor, 0, (int)SENSOR_COUNT - 1);
}

float get_target_temperature()
{
    return targetTemperature;
}

void set_target_temperature(float temp)
{
    targetTemperature = constrain(temp, SET_TEMP_MIN, SET_TEMP_MAX);
}

bool get_heater_enabled()
{
    return enabled;
}

void set_heater_enabled(bool state)
{
    enabled = state;
}

void heating_init()
{
    pinMode(HEATER_BED_PIN, OUTPUT);
    digitalWrite(HEATER_BED_PIN, LOW);
}

void heating_update()
{
    if (!enabled)
    {
        digitalWrite(HEATER_BED_PIN, LOW);
        return;
    }

    float temp = sensors_get_temperature(targetSensor);
    active = enabled && temp < targetTemperature;
    digitalWrite(HEATER_BED_PIN, active ? HIGH : LOW);
}

bool get_heater_active()
{
    return active;
}
