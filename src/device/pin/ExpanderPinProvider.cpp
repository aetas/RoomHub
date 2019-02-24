#include "device/pin/ExpanderPinProvider.hpp"
#include "device/pin/ExpanderDigitalPin.hpp"
#include "device/pin/MuxAnalogPin.hpp"

ExpanderPinProvider::ExpanderPinProvider(Adafruit_MCP23017* _expanders, CD74HC4067* _mux) {
    expanders = _expanders;
    mux = _mux;
}

ExpanderPinProvider& ExpanderPinProvider::getInstance(Adafruit_MCP23017* expanders, CD74HC4067* mux) {
    static ExpanderPinProvider instance(expanders, mux);
    return instance;
}

DigitalPin* ExpanderPinProvider::digitalPin(const uint8_t portNumber, const WireColor& wireColor) {
    uint8_t wireColorAsNumber = static_cast<uint8_t>(wireColor);
    uint8_t expanderAddress = (portNumber/4) - 1;
    uint8_t expanderPinNumber = ((portNumber-1) % 4) * 4 + (wireColorAsNumber-3);
    
    return new ExpanderDigitalPin(&expanders[expanderAddress], expanderPinNumber);
}

AnalogPin* ExpanderPinProvider::analogPin(const uint8_t portNumber) {
    return new MuxAnalogPin(mux, portNumber-1, muxCommonPin);
}