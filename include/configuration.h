#pragma once

// === GENERAL ===

// time to wait for voltage stabilization on powerup
#define POWERUP_DELAY           250     // [milliseconds]

// direction of rotary encoder (1 or -1)
#define ENCODER_DIRECTION       -1

// time to sound the buzzer for when testing
#define BUZZER_TEST_DURATION    500     // [milliseconds]


// === TEMPERATURES ===

// supported temperature range and initial value
#define SET_TEMP_MIN            15
#define SET_TEMP_MAX            80
#define SET_TEMP_DEFAULT        20

// temperature to trigger an alarm
#define ALARM_TEMP              90

// temperature to stop heating (customizable via UI, range: SET_TEMP_[MIN,MAX])
#define CUTOFF_TEMP_DEFAULT     40


// === SENSORS ===

// initially selected sensor
#define SET_SENSOR_DEFAULT      1

// sensor labels in the UI
#define SENSOR_LABEL_0          "Bed"
#define SENSOR_LABEL_1          "Air1"
#define SENSOR_LABEL_2          "Air2"

// number of samples to keep in the buffer
// (lower: faster sensing, higher: less jitter)
#define SENSOR_BUFFER_SIZE      64

// oversampling count
// (lower: better performance, higher: better accuracy)
#define SENSOR_OVERSAMPLING     128
