#pragma once

#include <stdint.h>

#include "ArduinoLog.h"
#include "Arduino.h"


#include <functional>
#define MQTT_CALLBACK_SIGNATURE std::function<void(char*, uint8_t*, unsigned int)> callback

class Client {

};

class PubSubClient {
public:
    void setClient(Client& connectionClient) {};
    void setServer(const char* hostname, uint16_t port) {};
    bool connect(const char* deviceName, const char* willTopic, uint8_t willQoS, bool willRetain, const char* willMessage) {};
    bool connected() {};
    bool publish(const char* topic, const char* payload, bool retained = false) {};
    bool subscribe(const char* topic, uint8_t qos) {};
    void setCallback(MQTT_CALLBACK_SIGNATURE) {};
    void loop() {};

};

