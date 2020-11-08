#pragma once

static const size_t SENSOR_COUNT = 3;

void sensors_init();

void sensors_update();

float sensors_get_temperature(int sensor);
