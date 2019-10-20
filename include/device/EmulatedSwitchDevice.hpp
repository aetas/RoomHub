#pragma once

#include "Device.hpp"
#include "device/pin/DigitalPin.hpp"

class EmulatedSwitchDevice: public Device {

public:

    const uint8_t ACTION_STATE = LOW;
    const uint8_t DEFAULT_STATE = HIGH;

    EmulatedSwitchDevice(const uint16_t _id, DigitalPin* _digitalPin): Device(_id, DeviceType::EMULATED_SWITCH), digitalPin(_digitalPin) {
        digitalPin->pinMode(OUTPUT);
        digitalPin->digitalWrite(DEFAULT_STATE);
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