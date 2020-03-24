#include "mqtt/MqttCommandReceiver.hpp"
#include "device/DevicesRegistry.hpp"
#include "ArduinoLog.h"

MqttCommandReceiver::MqttCommandReceiver(DevicesRegistry* _devicesRegistry, MqttConnectionTester* _mqttConnectionTester)
    : devicesRegistry(_devicesRegistry), mqttConnectionTester(_mqttConnectionTester) {
}

MqttCommandReceiver& MqttCommandReceiver::getInstance(DevicesRegistry* _devicesRegistry, MqttConnectionTester* _mqttConnectionTester) {
    static MqttCommandReceiver instance(_devicesRegistry, _mqttConnectionTester);
    return instance;
}

void MqttCommandReceiver::informDevice(String& deviceId, String& propertyName, const char* value) {
    Log.notice(F("Device state change: %s(%s) <- %s" CR), deviceId.c_str(), propertyName.c_str(), value);
    uint8_t deviceIdInt = deviceId.toInt();
    devicesRegistry->getDevice(deviceIdInt)->setProperty(propertyName.c_str(), value);
}

void MqttCommandReceiver::messageReceived(const char* topic, byte* payload, unsigned int length) {
    char* payloadCopy = (char*)malloc(length+1);
    memcpy(payloadCopy, payload, length);
    payloadCopy[length] = '\0';
    
    MqttCommandReceiver& receiver = MqttCommandReceiver::getInstance(nullptr, nullptr);

    if (receiver.mqttConnectionTester->isTestTopic(topic)) {
        // No logs in here because it is called 5 times a second
        receiver.mqttConnectionTester->onNewConnectionTestTimeReceived(payloadCopy);
    } else {
        Log.notice(F("MQTT received: %s <- %s" CR), topic, payloadCopy);
        String topicString = String(topic);
        String nodeId = getHomieNodeId(topicString);
        String propertyName = getHomiePropertyName(topicString);
        receiver.informDevice(nodeId, propertyName, payloadCopy);
    }
    free(payloadCopy);
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