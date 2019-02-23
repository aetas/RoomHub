#pragma once

#include "device/pin/DigitalPin.hpp"
#include "device/pin/AnalogPin.hpp"
#include "config/DeviceConfig.hpp"

class ExpanderPinProvider {

public:
    static ExpanderPinProvider& getInstance();
    
    ExpanderPinProvider(ExpanderPinProvider const&) = delete;
    void operator=(ExpanderPinProvider const&) = delete;

    // TODO it needs proper implementation
    DigitalPin* digitalPin(const uint8_t portNumber, const WireColor& wireColor);
    // TODO it needs proper implementation
    AnalogPin* analogPin(const uint8_t portNumber);

private:
    ExpanderPinProvider();
};