#pragma once

#include <stdint.h>

#define LOW               0x0
#define HIGH              0x1

#define INPUT             0x01
#define OUTPUT            0x02

class DigitalPin {

public:
    virtual uint8_t digitalRead() = 0;
    virtual void digitalWrite(uint8_t val) = 0;
    virtual void pinMode(uint8_t mode) = 0;
};