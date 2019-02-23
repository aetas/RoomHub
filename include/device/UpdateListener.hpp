#pragma once

#include <stdint.h>

class UpdateListener {

public:
    virtual void valueUpdated(const uint8_t deviceId, const uint8_t newValue) = 0;
    virtual void valueUpdated(const uint8_t deviceId, const uint16_t newValue) = 0;
    virtual void valueUpdated(const uint8_t deviceId, const char* newValue, const uint8_t length) = 0;
};