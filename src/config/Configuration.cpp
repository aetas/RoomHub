#include "config/Configuration.hpp"
#include "ArduinoLog.h"

void Configuration::loadConfiguration(ConfigurationStorage& storage, ConfigurationServer& configurationServer) {
    if (!storage.isDevicesConfigurationSet() || !storage.isMqttConfigurationSet()) {
        Log.warning(F("Configuration not found starting configuration server" CR));
        configurationServer.startConfigServer();
    }
    Log.notice(F("Configuration found - starting RoomHub" CR));
    roomHubName = storage.readName();
    // Log.trace(F("hubName = %s" CR), roomHubName);
    mqttHostname = storage.readMqttHostname();
    // Log.trace(F("MqttHostname = %s" CR), mqttHostname);
    devicesConfig = storage.readDevicesConfig();
    numberOfDevices = storage.numberOfDevices();
    Log.notice(F("Devices (%i) configuration read from memory" CR), numberOfDevices);
}

const char* Configuration::getRoomHubName() { return roomHubName; }
const char* Configuration::getMqttHostname() { return mqttHostname; }
DeviceConfig** Configuration::getDevicesConfig() { return devicesConfig; }
uint8_t Configuration::getNumberOfDevices() { return numberOfDevices; }