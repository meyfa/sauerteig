#pragma once

#include <stddef.h>

template <size_t bufferSize>
class AverageBuffer
{
private:
    float buffer[bufferSize]{{0}};
    bool empty = true;
    size_t index = 0;
    float sum = 0;

public:
    /**
     * Obtain the buffer sliding average.
     */
    float average()
    {
        return sum / bufferSize;
    }

    /**
     * Add the value into the buffer, replacing the oldest value previously added.
     * If called for the first time, fills all buffer entries with this value.
     */
    void push(float value)
    {
        if (empty)
        {
            for (size_t i = 0; i < bufferSize; ++i)
            {
                buffer[i] = value;
            }
            ++index;
            sum = bufferSize * value;
            empty = false;
        }
        else
        {
            sum = sum - buffer[index] + value;
            buffer[index] = value;
        }

        ++index;
        if (index >= bufferSize)
        {
            index = 0;
        }
    }
};
