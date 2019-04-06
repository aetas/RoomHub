#pragma once

#include "config/DeviceConfig.hpp"
#include "homie/HomieNode.hpp"
#include "mqtt/MqttClient.hpp"

class HomieNodeFactory {

public:
    static HomieNode** createNodes(DeviceConfig devicesConfig[], uint8_t numberOfDevices, char* homieDeviceName, MqttClient& mqttClient);

private:
    HomieNodeFactory();
    ~HomieNodeFactory();

    static HomieNode** createNode(DeviceConfig devicesConfig);
};