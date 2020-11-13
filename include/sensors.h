#pragma once

static const size_t SENSOR_COUNT = 3;
static const float MIN_SENSOR_TEMP = 5;

extern const char* SENSOR_LABELS[SENSOR_COUNT];

void sensors_init();

void sensors_update();

float sensors_get_temperature(int sensor);
