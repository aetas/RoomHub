#pragma once

#include "device/UpdateListener.hpp"

class SimpleUpdateListener: public UpdateListener {

public:
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint8_t newValue) { smallIntValue = newValue; };
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint16_t newValue) { bigIntValue = newValue; };
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const char* newValue) { stringValue = newValue; };

    uint8_t smallIntValue = 1;
    uint16_t bigIntValue = 0;
    const char* stringValue = "";
};