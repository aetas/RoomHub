#pragma once

#include "Device.hpp"
#include "device/pin/DigitalPin.hpp"

class DigitalOutputDevice: public Device {

public:
    
    const uint8_t ACTION_STATE = LOW;
    const uint8_t DEFAULT_STATE = HIGH;

    DigitalOutputDevice(const uint16_t _id, DigitalPin* _digitalPin): Device(_id, DeviceType::DIGITAL_OUTPUT), digitalPin(_digitalPin) {
        digitalPin->pinMode(OUTPUT);
        digitalPin->digitalWrite(DEFAULT_STATE);
    };

    ~DigitalOutputDevice();
    void setProperty(const char* propertyName, const char* newValue);

private:
    DigitalPin* digitalPin;
};