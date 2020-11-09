#include <Arduino.h>

#include "sensors.h"
#include "pins.h"
#include "average_buffer.h"

const int OVERSAMPLE = 128;

AverageBuffer<100> buffers[SENSOR_COUNT];

typedef struct
{
    int16_t value, celsius;
} temp_entry_t;

// R25 = 100 kOhm, beta25 = 4100 K, 4.7 kOhm pull-up, Hisens thermistor
const temp_entry_t temptable_13[] PROGMEM = {
    {int16_t(20.04), 300},
    {int16_t(23.19), 290},
    {int16_t(26.71), 280},
    {int16_t(31.23), 270},
    {int16_t(36.52), 260},
    {int16_t(42.75), 250},
    {int16_t(50.68), 240},
    {int16_t(60.22), 230},
    {int16_t(72.03), 220},
    {int16_t(86.84), 210},
    {int16_t(102.79), 200},
    {int16_t(124.46), 190},
    {int16_t(151.02), 180},
    {int16_t(182.86), 170},
    {int16_t(220.72), 160},
    {int16_t(316.96), 140},
    {int16_t(447.17), 120},
    {int16_t(590.61), 100},
    {int16_t(737.31), 80},
    {int16_t(857.77), 60},
    {int16_t(939.52), 40},
    {int16_t(986.03), 20},
    {int16_t(1008.7), 0}};

static float convert_temperature(int raw)
{
    const size_t LEN = sizeof(temptable_13) / sizeof(temptable_13[0]);

    uint8_t l = 0;
    uint8_t r = LEN;
    uint8_t m;

    while (true)
    {
        m = (l + r) >> 1;
        if (!m)
        {
            return int16_t(pgm_read_word(&temptable_13[0].celsius));
        }
        if (m == l || m == r)
        {
            return int16_t(pgm_read_word(&temptable_13[LEN - 1].celsius));
        }

        int16_t v00 = pgm_read_word(&temptable_13[m - 1].value),
                v10 = pgm_read_word(&temptable_13[m - 0].value);

        if (raw < v00)
        {
            r = m;
        }
        else if (raw > v10)
        {
            l = m;
        }
        else
        {
            const int16_t v01 = int16_t(pgm_read_word(&temptable_13[m - 1].celsius)),
                          v11 = int16_t(pgm_read_word(&temptable_13[m - 0].celsius));
            return v01 + (raw - v00) * float(v11 - v01) / float(v10 - v00);
        }
    }
}

static int readSensor(int index)
{
    pin_t pin = index == 1 ? TEMP_1_PIN : (index == 2 ? TEMP_2_PIN : TEMP_0_PIN);

    long samples = 0;
    for (int i = 0; i < OVERSAMPLE; ++i)
    {
        samples += analogRead(pin);
    }
    return samples / OVERSAMPLE;
}

void sensors_init()
{
}

void sensors_update()
{
    static unsigned long lastRead = 0;
    unsigned long now = millis();
    if (now < lastRead + 20)
    {
        return;
    }
    lastRead = now;

    for (size_t i = 0; i < SENSOR_COUNT; ++i)
    {
        float read = convert_temperature(readSensor(i));
        buffers[i].push(read);
    }
}

float sensors_get_temperature(int sensor)
{
    return buffers[sensor].average();
}
