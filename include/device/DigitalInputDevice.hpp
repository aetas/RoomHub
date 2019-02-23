#pragma once

#include "Device.hpp"
#include "device/pin/DigitalPin.hpp"

class DigitalInputDevice: public Device {

public:
    DigitalInputDevice(const uint16_t _id, DigitalPin* _digitalPin): DigitalInputDevice(_id, _digitalPin, LOW) {};

    DigitalInputDevice(const uint16_t _id, DigitalPin* _digitalPin, uint8_t _defaultState): 
        Device(_id, DeviceType::DIGITAL_INPUT), digitalPin(_digitalPin), currentState(_defaultState) {};

    ~DigitalInputDevice();

    void loop();

private:
    DigitalPin* digitalPin;
    uint8_t currentState;
};