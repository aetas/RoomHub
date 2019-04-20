#pragma once

#include "Device.hpp"
#include "pin/AnalogPin.hpp"
#include "EmonLib.h"

class Sct013Device: public Device {

public:
    Sct013Device(const uint16_t _id, AnalogPin* _analogPin);
    ~Sct013Device();

    void loop(const uint32_t& currentTimeMs);

private:
    AnalogPin* analogPin;
    EnergyMonitor emon1;
    const uint16_t READ_INTERVAL_MS = 30000;
    uint32_t lastReadTime = 0;
};