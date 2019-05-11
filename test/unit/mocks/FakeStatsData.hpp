#pragma once

#include "stats/StatsData.hpp"

#include <inttypes.h>

class FakeStatsData: public StatsData {
public:
    uint32_t getFreeHeapInBytes() { return 0; }
    uint8_t getSignalStrength() { return 100; }
};