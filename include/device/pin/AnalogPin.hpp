#pragma once

#include <stdint.h>

class AnalogPin {

public:
    virtual uint16_t read() = 0;
};