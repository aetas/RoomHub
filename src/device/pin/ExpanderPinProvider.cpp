#include "device/pin/ExpanderPinProvider.hpp"
#include "device/pin/ExpanderDigitalPin.hpp"
#include "device/pin/MuxAnalogPin.hpp"
#include "ArduinoLog.h"

ExpanderPinProvider::ExpanderPinProvider(Adafruit_MCP23017* _expanders, CD74HC4067* _mux, uint8_t _muxCommonPin):
    expanders(_expanders), mux(_mux), muxCommonPin(_muxCommonPin) {}

ExpanderPinProvider& ExpanderPinProvider::getInstance(Adafruit_MCP23017* expanders, CD74HC4067* mux, uint8_t muxCommonPin) {
    static ExpanderPinProvider instance(expanders, mux, muxCommonPin);
    return instance;
}

DigitalPin* ExpanderPinProvider::digitalPin(const uint8_t portNumber, const WireColor& wireColor) {
    uint8_t wireColorAsNumber = static_cast<uint8_t>(wireColor);
    uint8_t expanderAddress = (portNumber-1) / 4;
    uint8_t expanderPinNumber = ((portNumber-1) % 4) * 4 + (wireColorAsNumber-3);
    
    // Log.trace(F("expander address: %d, expander pin number: %d" CR), expanderAddress, expanderPinNumber);
    
    return new ExpanderDigitalPin(&expanders[expanderAddress], expanderPinNumber);
}

AnalogPin* ExpanderPinProvider::analogPin(const uint8_t portNumber) {
    return new MuxAnalogPin(mux, portNumber-1, muxCommonPin);
}