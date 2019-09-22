#pragma once

#include "Device.hpp"
#include "device/pin/DigitalPin.hpp"

class EmulatedSwitchDevice: public Device {

public:
    EmulatedSwitchDevice(const uint16_t _id, DigitalPin* _digitalPin): Device(_id, DeviceType::EMULATED_SWITCH), digitalPin(_digitalPin) {
        digitalPin->pinMode(OUTPUT);
    };

    ~EmulatedSwitchDevice();
    void setProperty(const char* propertyName, const char* newValue);
    void loop(const uint32_t& currentTimeMs);

private:
    DigitalPin* digitalPin;
    bool isPressed = false;
    bool pressedAcknowledged = false;
    uint32_t pressedOnMs = 0;
    const uint16_t PRESS_TIME_MS = 500;
};