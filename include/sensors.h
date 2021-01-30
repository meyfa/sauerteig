#pragma once

static const size_t SENSOR_COUNT = 3;

extern const char* SENSOR_LABELS[SENSOR_COUNT];

void sensors_init();

void sensors_update();

float sensors_get_temperature(int sensor);

bool sensors_any_below(float min);

bool sensors_any_above(float max);
