#pragma once

#include "Device.hpp"
#include "device/pin/DigitalPin.hpp"

class DigitalInputDevice: public Device {

public:
    DigitalInputDevice(const uint16_t _id, DigitalPin* _digitalPin, uint16_t _debounceMs): 
        Device(_id, DeviceType::DIGITAL_INPUT), digitalPin(_digitalPin), debounceMs(_debounceMs) 
    {
        digitalPin->pinMode(INPUT);
        digitalPin->pullUp();
    };

    ~DigitalInputDevice();

    void loop(const uint32_t& currentTimeMs);

private:
    DigitalPin* digitalPin;
    uint8_t currentState = HIGH;
    const uint16_t debounceMs = 0;
    uint32_t lastChangeMs = 0;
    uint8_t intermediateState = HIGH;
    uint32_t intermediateStateStart = 0;
    bool inIntermediateState = false;

    void startIntermediateState(uint8_t state, uint32_t currentTime);
    void endIntermediateState();
};