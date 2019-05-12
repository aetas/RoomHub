#include "mqtt/MqttClient.hpp"

#include "ArduinoLog.h"
#include "WString.h"

void MqttClient::begin(const char* hostname, uint16_t port, Client& _connectionClient) {
    // Log.trace(F("MQTT client set up (hostname = '%s', port = '%i')" CR), hostname, port);
    client.setClient(_connectionClient);
    client.setServer(hostname, port);
}

bool MqttClient::connected() {
    return client.connected();
}

void MqttClient::connect(const char* deviceName, const char* willTopic, uint8_t willQoS, bool willRetain, const char* willMessage) {
    while(!client.connect(deviceName, willTopic, willQoS, willRetain, willMessage)) {
        Log.notice(F("Connecting to MQTT as %s..." CR), deviceName);
        delay(1000);
    }
    Log.notice(F("MQTT connected. Will: %s -> %s" CR), willTopic, willMessage);
}

bool MqttClient::publish(const char* topic, const char* payload, bool retained, bool logMessage) {
    if (logMessage) {
        Log.notice(F("MQTT: %s -> %s" CR), topic, payload);
    }
    if(!client.publish(topic, payload, retained)){
        Log.error(F("MQTT message sending failed. Topic: %s | Payload %s" CR), topic, payload);
        return false;
    }
    return true;
}

bool MqttClient::subscribe(const char* topic) {
    Log.notice(F("MQTT subscribe: %s" CR), topic);
    if(!client.subscribe(topic, 1)) {
        Log.error(F("MQTT subscription failed. Topic: %s" CR), topic);
        return false;
    }
    return true;
}

void MqttClient::onMessage(MQTT_CALLBACK_SIGNATURE) {
    client.setCallback(callback);
}

bool MqttClient::loop() {
    return client.loop();
}