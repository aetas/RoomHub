#pragma once

#include "device/pin/DigitalPin.hpp"
#include "device/pin/AnalogPin.hpp"
#include "config/device/DeviceConfig.hpp"

class PinProvider {

public:
    virtual DigitalPin* digitalPin(const uint8_t portNumber, const WireColor& wireColor) = 0;
    virtual AnalogPin* analogPin(const uint8_t portNumber) = 0;
};