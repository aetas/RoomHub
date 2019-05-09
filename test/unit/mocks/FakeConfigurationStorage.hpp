#pragma once

#include <iostream>
#include <string>
#include <list>
#include "config/device/DeviceConfigParser.hpp"
#include "config/ConfigurationStorage.hpp"

using namespace std;

class FakeConfigurationStorage: public ConfigurationStorage {
public:
    FakeConfigurationStorage(DeviceConfigParser& _parser): deviceConfigParser(_parser) { }
    void storeName(const char* _name) { name = _name; }
    const char* readName() { return name.c_str(); }
    void storeMqttHostname(const char* _mqttHostname) { mqttHostname = _mqttHostname; }
    const char* readMqttHostname() { return mqttHostname.c_str(); }
    void storeDeviceConfig(const char* _deviceConfigString) { devicesConfigString.push_back(string(_deviceConfigString)); }
    DeviceConfig** readDevicesConfig() {
        DeviceConfig** devicesConfig = new DeviceConfig*[128];
        int i = 0;
        for (const string& deviceLine : devicesConfigString) {
            devicesConfig[i] = deviceConfigParser.parse(deviceLine.c_str());
            i++;
        }
        return devicesConfig;
    }
    uint8_t numberOfDevices() { return devicesConfigString.size(); }
    bool isDevicesConfigurationSet() { return devicesConfigString.size() > 0; }
    bool isMqttConfigurationSet() { return mqttHostname != ""; }
    void resetConfig() { name = ""; mqttHostname = ""; }
private:
    string name = "";
    string mqttHostname = "";
    list<string> devicesConfigString;

    DeviceConfigParser& deviceConfigParser;
};