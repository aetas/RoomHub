#pragma once

#include "Device.hpp"
#include "pin/AnalogPin.hpp"

class AnalogInputDevice: public Device {

public:
    AnalogInputDevice(const uint16_t _id, AnalogPin* _analogPin);
    ~AnalogInputDevice();

    void loop(const uint32_t& currentTimeMs);

private:
    AnalogPin* analogPin;
    const uint16_t READ_INTERVAL_MS = 30000;
    uint32_t lastReadTime = 0;
};