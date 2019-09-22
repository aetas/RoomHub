#pragma once

#include <stdint.h>
#include "UpdateListener.hpp"
#include "config/device/DeviceConfig.hpp"

class Device {

public:
    Device(const uint16_t _id, const DeviceType _type): id(_id), type(_type) {};
    
    const uint16_t getId();
    DeviceType getType();
    void setUpdateListener(UpdateListener* _listener);
    virtual void setProperty(const char* propertyName, const char* newValue) {};
    virtual void loop(const uint32_t& currentTimeMs) {};
    
protected:
    void notify(const char* propertyName, const char* value);
    void notify(const char* propertyName, const uint8_t value);
    void notify(const char* propertyName, const uint16_t value);

private:
    const uint16_t id;
    const DeviceType type;
    UpdateListener* updateListener = nullptr;
};