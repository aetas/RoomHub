#include "mqtt/MqttCommandReceiver.hpp"
#include "device/DevicesRegistry.hpp"
#include "ArduinoLog.h"

MqttCommandReceiver::MqttCommandReceiver(DevicesRegistry* _devicesRegistry, HomieDevice* _homieDevice)
    : devicesRegistry(_devicesRegistry), homieDevice(_homieDevice) {
}

MqttCommandReceiver& MqttCommandReceiver::getInstance(DevicesRegistry* _devicesRegistry, HomieDevice* _homieDevice) {
    static MqttCommandReceiver instance(_devicesRegistry, _homieDevice);
    return instance;
}

void MqttCommandReceiver::informDevice(String& deviceId, String& propertyName, String& value) {
    Log.notice(F("Device state change: %s(%s) <- %s" CR), deviceId.c_str(), propertyName.c_str(), value.c_str());
    uint8_t deviceIdInt = deviceId.toInt();
    devicesRegistry->getDevice(deviceIdInt)->setProperty(propertyName.c_str(), value.c_str());
    homieDevice->getNode(deviceIdInt)->propertyValueUpdated(propertyName.c_str(), value.c_str());
}

void MqttCommandReceiver::messageReceived(String &topic, String &payload) {
    Log.notice(F("MQTT received: %s <- %s" CR), topic.c_str(), payload.c_str());
    String nodeId = getHomieNodeId(topic);
    String propertyName = getHomiePropertyName(topic);
    MqttCommandReceiver::getInstance(nullptr, nullptr).informDevice(nodeId, propertyName, payload);
}

bool MqttCommandReceiver::isHomieNodePropertyValue(String& topic) {
    return (topic.indexOf('$') == -1);
}
String MqttCommandReceiver::getHomieNodeId(String& topic) {
    uint8_t firstSlashIndex = topic.indexOf('/');
    uint8_t secondSlashIndex = topic.indexOf('/', firstSlashIndex+1);
    uint8_t thirdSlashIndex = topic.indexOf('/', secondSlashIndex+1);
    return topic.substring(secondSlashIndex+1, thirdSlashIndex);
}
String MqttCommandReceiver::getHomiePropertyName(String& topic) {
    uint8_t firstSlashIndex = topic.indexOf('/');
    uint8_t secondSlashIndex = topic.indexOf('/', firstSlashIndex+1);
    uint8_t thirdSlashIndex = topic.indexOf('/', secondSlashIndex+1);
    uint8_t fourthSlashIndex = topic.indexOf('/', thirdSlashIndex+1);
    return topic.substring(thirdSlashIndex+1, fourthSlashIndex); 
}