#pragma once

#include "device/pin/DigitalPin.hpp"
#include "device/pin/AnalogPin.hpp"
#include "config/DeviceConfig.hpp"

class PinProvider {

public:
    static PinProvider& getInstance();
    
    PinProvider(PinProvider const&) = delete;
    void operator=(PinProvider const&) = delete;

    // TODO it needs proper implementation
    DigitalPin* digitalPin(const uint8_t portNumber, const WireColor& wireColor);
    // TODO it needs proper implementation
    AnalogPin* analogPin(const uint8_t portNumber);

private:
    PinProvider();
};