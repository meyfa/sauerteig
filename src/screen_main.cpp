#include "configuration.h"
#include "screen_main.h"
#include "sensors.h"
#include "heating.h"
#include "fan.h"

const float DEGREES_PER_SCROLL_STEP = 0.5f;

const uint8_t BITMAP_CNT = 2;   // number of bytes in h direction
const uint8_t BITMAP_SIZE = 12; // width and height in pixels

const uint8_t FAN_BITMAP[] = {
    0b01111111, 0b11100000,
    0b10000011, 0b11010000,
    0b11000111, 0b00010000,
    0b11000111, 0b00010000,
    0b11110110, 0b00010000,
    0b11111001, 0b11010000,
    0b10111001, 0b11110000,
    0b10000110, 0b11110000,
    0b10001110, 0b00110000,
    0b10001110, 0b00110000,
    0b10111100, 0b00010000,
    0b01111111, 0b11100000,
};

const uint8_t HEATER_BITMAP[] = {
    0b00000100, 0b00000000,
    0b00001100, 0b00000000,
    0b00001010, 0b00000000,
    0b00001001, 0b10000000,
    0b00001000, 0b10000000,
    0b00010000, 0b01000000,
    0b00100011, 0b01000000,
    0b00101110, 0b01000000,
    0b00101001, 0b01000000,
    0b00011010, 0b10000000,
    0b00001111, 0b00000000,
    0b11111111, 0b11110000,
};

const char *HEATER_OFF = "Off";
const char *HEATER_IDLE = "Idle";
const char *HEATER_HEATING = "Heating";

void MainScreen::draw(U8GLIB &u8g)
{
    int targetSensor = get_target_sensor();
    float targetTemp = get_target_temperature();
    bool heaterEnabled = get_heater_enabled();
    bool heaterActive = get_heater_active();
    int fanPercentage = fan_get_speed() * 100 / 255;

    u8g.drawFrame(0, 0, 84, 20);  // top left
    u8g.drawFrame(0, 19, 84, 45); // bottom left
    u8g.drawFrame(83, 0, 44, 64); // right

    u8g.drawStr(4, 13, "Target");
    u8g.setPrintPos(42, 13);
    u8g.print(targetTemp, 1);
    u8g.print(" \260C");

    u8g.drawBitmap(99, 5, BITMAP_CNT, BITMAP_SIZE, HEATER_BITMAP);
    const char *heaterString = heaterEnabled
                                   ? (heaterActive ? HEATER_HEATING : HEATER_IDLE)
                                   : HEATER_OFF;
    u8g.setPrintPos(83 + (44 - u8g.getStrWidth(heaterString)) / 2, 28);
    u8g.print(heaterString);

    u8g.drawBitmap(99, 35, BITMAP_CNT, BITMAP_SIZE, FAN_BITMAP);
    static char fanString[5];
    sprintf(fanString, "%d%%", fanPercentage);
    u8g.setPrintPos(83 + (44 - u8g.getStrWidth(fanString)) / 2, 59);
    u8g.print(fanString);

    for (size_t sensorId = 0; sensorId < SENSOR_COUNT; ++sensorId)
    {
        int yOffset = 26 + sensorId * 12;
        float sensorTemp = sensors_get_temperature(sensorId);
        if (targetSensor == (int)sensorId)
        {
            u8g.drawDisc(6, yOffset + 4, 2);
        }
        u8g.drawStr(12, yOffset + 8, SENSOR_LABELS[sensorId]);
        u8g.setPrintPos(42, yOffset + 8);
        if (sensorTemp < SENSOR_MINTEMP)
        {
            u8g.print('-');
            continue;
        }
        u8g.print(sensorTemp, 1);
        u8g.print(" \260C");
    }
}

ScreenType MainScreen::handleClick()
{
    return MENU;
}

void MainScreen::handleScroll(int steps)
{
    set_target_temperature(get_target_temperature() + DEGREES_PER_SCROLL_STEP * steps);
}
