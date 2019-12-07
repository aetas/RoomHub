#pragma once

#include <stdint.h>

class UpdateListener {

public:
    virtual void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint8_t& newValue) = 0;
    virtual void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint32_t& newValue) = 0;
    virtual void valueUpdated(const uint8_t deviceId, const char* propertyName, const float& newValue) = 0;
    virtual void valueUpdated(const uint8_t deviceId, const char* propertyName, const char* newValue) = 0;
};