#pragma once

static const float SET_TEMP_MIN = 15;
static const float SET_TEMP_MAX = 80;
static const float SET_TEMP_DEFAULT = 20;

float get_target_temperature();

void set_target_temperature(float degrees);

bool get_heater_enabled();

void set_heater_enabled(bool state);

void heating_init();

void heating_update();

bool get_heater_active();
