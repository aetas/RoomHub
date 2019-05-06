#pragma once

#include "DeviceConfig.hpp"

class ConfigurationStorage {
    public:
    virtual void storeName(const char* name) = 0;
    virtual const char* readName() = 0;
    virtual void storeMqttHostname(const char* mqttHostname) = 0;
    virtual const char* readMqttHostname() = 0;
    virtual void storeDeviceConfig(const char* deviceConfigString) = 0;
    virtual DeviceConfig** readDevicesConfig() = 0;
    virtual uint8_t numberOfDevices() = 0;
    virtual bool isDevicesConfigurationSet() = 0;
    virtual bool isMqttConfigurationSet() = 0;
    virtual void resetConfig() = 0;
};