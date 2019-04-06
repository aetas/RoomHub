#include "mqtt/MqttClient.hpp"

#include "WString.h"
#include "ArduinoLog.h"
#include "Arduino.h"

void MqttClient::begin(const char* hostname, uint16_t port, Client& connectionClient) {
    client.begin(hostname, port, connectionClient);
}

void MqttClient::connect(const char* deviceName) {
    while(!client.connect(deviceName)) {
        Log.notice(F("Connecting to MQTT..." CR));
        delay(500);
    }
}

bool MqttClient::publish(const char* topic, const char* payload) {
    Log.notice(F("MQTT: %s -> %s" CR), topic, payload);
    if(!client.publish(topic, payload)){
        Log.error(F("MQTT message sending failed. Topic: %s | Payload %s" CR), topic, payload);
        return false;
    }
    return true;
}

bool MqttClient::subscribe(const char* topic) {
    Log.notice(F("MQTT subscribe: %s" CR), topic);
    if(!client.subscribe(topic)) {
        Log.error(F("MQTT subscription failed. Topic: %s" CR), topic);
        return false;
    }
    return true;
}

void MqttClient::setWill(const char* topic, const char* payload) {
    Log.notice(F("MQTT will: %s -> %s" CR), topic, payload);
    client.setWill(topic, payload);
}