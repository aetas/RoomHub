#pragma once

#include <stdint.h>

#define LOW               0x0
#define HIGH              0x1

class DigitalPin {

public:
    virtual uint8_t digitalRead() = 0;
    virtual void digitalWrite(uint8_t val) = 0;
};