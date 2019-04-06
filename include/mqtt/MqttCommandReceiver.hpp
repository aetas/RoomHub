#pragma once

#include "WString.h"
#include "device/DevicesRegistry.hpp"
#include "homie/HomieDevice.hpp"


class MqttCommandReceiver {

public:
    static MqttCommandReceiver& getInstance(DevicesRegistry* devicesRegistry, HomieDevice* _homieDevice);
    
    MqttCommandReceiver(MqttCommandReceiver const&) = delete;
    void operator=(MqttCommandReceiver const&) = delete;

    void informDevice(String& deviceId, String& propertyName, String& value);

    static void messageReceived(String &topic, String &payload);

private:
    MqttCommandReceiver(DevicesRegistry* _devicesRegistry, HomieDevice* _homieDevice);
    DevicesRegistry* devicesRegistry;
    HomieDevice* homieDevice;

    static bool isHomieNodePropertyValue(String& topic);
    static String getHomieNodeId(String& topic);
    static String getHomiePropertyName(String& topic);
};