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

void MqttCommandReceiver::informDevice(String& deviceId, String& propertyName, const char* value) {
    Log.notice(F("Device state change: %s(%s) <- %s" CR), deviceId.c_str(), propertyName.c_str(), value);
    uint8_t deviceIdInt = deviceId.toInt();
    devicesRegistry->getDevice(deviceIdInt)->setProperty(propertyName.c_str(), value);
    homieDevice->getNode(deviceIdInt)->propertyValueUpdated(propertyName.c_str(), value);
}

void MqttCommandReceiver::messageReceived(const char* topic, byte* payload, unsigned int length) {
    char* payloadString = new char[length];
    for(uint8_t i = 0; i < length; i++) {
        payloadString[i] = (char)payload[i];
    }
    payloadString[length] = '\0';
    
    Log.notice(F("MQTT received: %s <- %s" CR), topic, payloadString);
    String topicString = String(topic);
    String nodeId = getHomieNodeId(topicString);
    String propertyName = getHomiePropertyName(topicString);
    MqttCommandReceiver::getInstance(nullptr, nullptr).informDevice(nodeId, propertyName, payloadString);
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