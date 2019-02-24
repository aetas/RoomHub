#pragma once

#include "Device.hpp"
#include "device/pin/DigitalPin.hpp"

class DigitalOutputDevice: public Device {

public:
    DigitalOutputDevice(const uint16_t _id, DigitalPin* _digitalPin): Device(_id, DeviceType::DIGITAL_OUTPUT), digitalPin(_digitalPin) {
        digitalPin->pinMode(OUTPUT);
    };

    ~DigitalOutputDevice();
    void setState(const uint8_t newState);

private:
    DigitalPin* digitalPin;
};