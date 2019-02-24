#pragma once

#include "DigitalPin.hpp"
#include <Adafruit_MCP23017.h>

class ExpanderDigitalPin: public DigitalPin {

public:    
    ExpanderDigitalPin(Adafruit_MCP23017* _expander, const uint8_t _pinNumber);
    ~ExpanderDigitalPin();
    uint8_t digitalRead();
    void digitalWrite(uint8_t val);
    void pinMode(uint8_t mode);
private:
    Adafruit_MCP23017* expander;
    const uint8_t pinNumber;
};

