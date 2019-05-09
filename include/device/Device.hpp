#pragma once

#include <stdint.h>
#include "UpdateListener.hpp"
#include "config/device/DeviceConfig.hpp"

class Device {

public:
    Device(const uint16_t _id, const DeviceType _type): id(_id), type(_type) {};
    
    const uint16_t getId() { return id; };
    DeviceType getType() { return type; };
    void setUpdateListener(UpdateListener* _listener) { updateListener = _listener; };
    virtual void setProperty(const char* propertyName, const char* newValue) {};

protected:
    UpdateListener* updateListener = nullptr;

private:
    const uint16_t id;
    const DeviceType type;
};