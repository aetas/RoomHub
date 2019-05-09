#pragma once

#include <inttypes.h>
#include "PubSubClient.h"


class MqttClient {
public:
    virtual void begin(const char* hostname, uint16_t port, Client& connectionClient);
    virtual bool connected();
    virtual void connect(const char* deviceName, const char* willTopic, uint8_t willQoS, bool willRetain, const char* willMessage);
    virtual bool publish(const char* topic, const char* payload, bool retained = false, bool logMessage = true);
    virtual bool subscribe(const char* topic);
    virtual void onMessage(MQTT_CALLBACK_SIGNATURE);
    virtual bool loop();

private:
    PubSubClient client;
};