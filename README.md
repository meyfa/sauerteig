# sauerteig

This is the source code to an embedded heating chamber controller built from
cheap 3D printer components I had lying around.
The chamber is not meant to produce high temperatures but rather to be
consistent and accurate in the lower temperature ranges around 30°C.

**Mandatory disclaimer:** Use this project at your own risk. It is hacky, I
cannot vouch for the quality of the hardware used, and neither for the safety
of my code. It will probably not even work right with anything other than the
exact components I used.

## Parts List

- 1x Arduino Mega 2560
- 1x RAMPS 1.4 board
- 1x RepRapDiscount Full Graphics Smart Controller (ST7920 LCD, rotary 
  encoder, button, buzzer[, SD card slot])
- 3x 3950 100K thermistor
- 1x 12V heated bed
- 1x 12V fan
- 1x adequate 12V power supply

## Features

- LCD for viewing sensors and heating status
- Target temperature set via rotary encoder
- On-screen menu for advanced settings:
    - Selection of thermistor to use for targeting
    - Fan control (for air circulation inside the case)
    - Buzzer test
- Reliable temperature measurements with noise suppression

## How to Install

I use Visual Studio Code with PlatformIO to build and upload the firmware to
the Mega via USB.
