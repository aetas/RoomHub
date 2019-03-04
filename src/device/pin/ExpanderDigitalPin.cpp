#include "device/pin/ExpanderDigitalPin.hpp"

ExpanderDigitalPin::ExpanderDigitalPin(Adafruit_MCP23017* _expander, const uint8_t _pinNumber): 
    expander(_expander),
    pinNumber(_pinNumber) {

}

ExpanderDigitalPin::~ExpanderDigitalPin() {

}

uint8_t ExpanderDigitalPin::digitalRead() {
    return expander->digitalRead(pinNumber);
}

void ExpanderDigitalPin::digitalWrite(uint8_t val) {
    expander->digitalWrite(pinNumber, val);
}

void ExpanderDigitalPin::pinMode(uint8_t mode) {
    expander->pinMode(pinNumber, mode);
}

void ExpanderDigitalPin::pullUp() {
    expander->pullUp(pinNumber, HIGH);
}