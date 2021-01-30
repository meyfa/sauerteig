#pragma once

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
