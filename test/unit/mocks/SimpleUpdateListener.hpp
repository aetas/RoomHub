#pragma once

#include "device/UpdateListener.hpp"

class SimpleUpdateListener: public UpdateListener {

public:
    void valueUpdated(const uint8_t deviceId, const uint8_t newValue) { smallIntValue = newValue; };
    void valueUpdated(const uint8_t deviceId, const uint16_t newValue) { bigIntValue = newValue; };
    void valueUpdated(const uint8_t deviceId, const char* newValue, const uint8_t length) { stringValue = newValue; stringLength = length; };

    uint8_t  smallIntValue = HIGH;
    uint16_t bigIntValue = 0;
    const char* stringValue = "";
    uint8_t stringLength = 0;
};