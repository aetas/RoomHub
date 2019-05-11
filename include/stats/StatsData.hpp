#pragma once

#include <inttypes.h>

class StatsData {
public:
    virtual uint32_t getFreeHeapInBytes() = 0;
    virtual uint8_t getSignalStrength() = 0;
};