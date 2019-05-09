#pragma once

#include "ConfigurationStorage.hpp"
#include "ConfigurationServer.hpp"
#include "device/DeviceConfig.hpp"

class Configuration {
public:
    void loadConfiguration(ConfigurationStorage& storage, ConfigurationServer& configurationServer);
    const char* getRoomHubName();
    const char* getMqttHostname();
    DeviceConfig** getDevicesConfig();
    uint8_t getNumberOfDevices();
private:
    const char* roomHubName;
    const char* mqttHostname;
    DeviceConfig** devicesConfig;
    uint8_t numberOfDevices;
};