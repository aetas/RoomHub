#pragma once

#include "config/DeviceConfig.hpp"
#include "homie/HomieDevice.hpp"
#include "mqtt/MqttClient.hpp"

class HomieDeviceFactory {

public:
    static HomieDevice* create(const char* ip, const char* mac, DeviceConfig devicesConfig[], const uint8_t numberOfDevices, MqttClient& mqttClient);

private:
    HomieDeviceFactory();
    ~HomieDeviceFactory();

    static HomieNode** createNodes(DeviceConfig devicesConfig[], uint8_t numberOfDevices, MqttClient& mqttClient);
    static HomieNodeProperty** createHomieNodeProperties(DeviceConfig* node);
    static const uint8_t propertiesNumber(DeviceConfig* node);
};