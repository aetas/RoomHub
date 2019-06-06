#pragma once

#include "ConfigurationStorage.hpp"
#include "device/DeviceConfig.hpp"
#include "device/DeviceConfigParser.hpp"
#include <Arduino.h>

#define ETHERNET_CONFIG_FILE "/ethernet.conf"
#define NAME_CONFIG_FILE "/name.conf"
#define MQTT_CONFIG_FILE "/mqtt.conf"
#define DEVICES_CONFIG_FILE "/devices.conf"
#define DEVICES_COUNT_CONFIG_FILE "/devices-count.conf"

class SpiffsConfigurationStorage: public ConfigurationStorage {
public:
    ~SpiffsConfigurationStorage();
    void storeName(const char* name);
    const char* readName();
    void storeMqttHostname(const char* mqttHostname);
    const char* readMqttHostname();
    void storeDeviceConfig(const char* deviceConfigString);
    DeviceConfig** readDevicesConfig();
    void storeEthernetConfig(const char* ethernetConfigString);
    EthernetConfiguration readEthernetConfiguration();
    uint8_t numberOfDevices();
    bool isMqttConfigurationSet();
    bool isDevicesConfigurationSet();
    bool isEthernetConfigurationSet();
    void resetConfig();
    void resetEthernetConfig();
private:
    const __FlashStringHelper* MOUNTING_FAILED_MESSAGE = F("Mounting SPIFFS failed\n");
    const __FlashStringHelper* OPENING_FILE_FAILED_MESSAGE = F("Opening file '%s' failed\n");
    DeviceConfigParser deviceConfigParser;
    DeviceConfig** devicesConfigs = new DeviceConfig*[128];
    
    void store(const char* filename, const char* value, bool append = false);
    const char* read(const char* filename);
};