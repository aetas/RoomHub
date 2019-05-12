#pragma once

#include "device/UpdateListener.hpp"

class SimpleUpdateListener: public UpdateListener {

public:
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint8_t newValue) { smallIntValue = newValue; valueUpdatedCalledTimes++; };
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint16_t newValue) { bigIntValue = newValue; valueUpdatedCalledTimes++; };
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const char* newValue) { stringValue = newValue; valueUpdatedCalledTimes++; };

    uint8_t smallIntValue = 1;
    uint16_t bigIntValue = 0;
    const char* stringValue = "";
    uint8_t valueUpdatedCalledTimes = 0;
};