#pragma once

#include "WString.h"
#include "device/DevicesRegistry.hpp"
#include "homie/HomieDevice.hpp"
#include "mqtt/MqttConnectionTester.hpp"
#include "Arduino.h"


class MqttCommandReceiver {

public:
    static MqttCommandReceiver& getInstance(DevicesRegistry* devicesRegistry, MqttConnectionTester* _mqttConnectionTester);
    
    MqttCommandReceiver(MqttCommandReceiver const&) = delete;
    void operator=(MqttCommandReceiver const&) = delete;

    void informDevice(String& deviceId, String& propertyName, const char* value);

    static void messageReceived(const char* topic, byte* payload, unsigned int length);

private:
    MqttCommandReceiver(DevicesRegistry* _devicesRegistry, MqttConnectionTester* _mqttConnectionTester);
    DevicesRegistry* devicesRegistry;
    MqttConnectionTester* mqttConnectionTester;

    static bool isHomieNodePropertyValue(String& topic);
    static String getHomieNodeId(String& topic);
    static String getHomiePropertyName(String& topic);
};