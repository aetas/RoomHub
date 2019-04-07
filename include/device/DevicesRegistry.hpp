#pragma once

#include "device/Device.hpp"

class DevicesRegistry {

public:
    DevicesRegistry(uint8_t maxNumberOfDevices);
    ~DevicesRegistry();
    void add(Device* device);
    void loop(const uint32_t& currentTimeMs);
    void setUpdateListener(UpdateListener* _listener);
    Device* getDevice(uint16_t deviceId);
private:
    Device** devices;
    uint8_t currentNumberOfDevices = 0;

};