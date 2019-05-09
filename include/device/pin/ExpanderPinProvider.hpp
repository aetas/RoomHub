#pragma once

#include "device/pin/PinProvider.hpp"
#include "device/pin/DigitalPin.hpp"
#include "device/pin/AnalogPin.hpp"
#include "config/device/DeviceConfig.hpp"
#include <Adafruit_MCP23017.h>
#include <CD74HC4067.h>

class ExpanderPinProvider: public PinProvider {

public:
    static ExpanderPinProvider& getInstance(Adafruit_MCP23017* expanders, CD74HC4067* mux, uint8_t muxCommonPin);
    
    ExpanderPinProvider(ExpanderPinProvider const&) = delete;
    void operator=(ExpanderPinProvider const&) = delete;

    DigitalPin* digitalPin(const uint8_t portNumber, const WireColor& wireColor);
    AnalogPin* analogPin(const uint8_t portNumber);

private:
    ExpanderPinProvider(Adafruit_MCP23017* expanders, CD74HC4067* mux, uint8_t muxCommonPin);
    Adafruit_MCP23017* expanders;
    CD74HC4067* mux;
    uint8_t muxCommonPin;
};