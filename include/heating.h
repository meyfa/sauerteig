#pragma once

static const float SET_TEMP_MIN = 15;
static const float SET_TEMP_MAX = 80;
static const float SET_TEMP_DEFAULT = 20;

static const float ALARM_TEMP = 90;

static const int SET_SENSOR_DEFAULT = 1; // Air1

int get_target_sensor();

void set_target_sensor(int sensor);

float get_target_temperature();

void set_target_temperature(float temp);

float get_cutoff_temperature();

void set_cutoff_temperature(float temp);

bool get_heater_enabled();

void set_heater_enabled(bool state);

void heating_init();

void heating_update();

bool get_heater_active();
