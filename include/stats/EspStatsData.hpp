#pragma once

#include "StatsData.hpp"

class EspStatsData: public StatsData {
public:
    uint32_t getFreeHeapInBytes();
    uint8_t getSignalStrength();
};