#pragma once

#include <inttypes.h>
#include "MQTTClient.h"


class MqttClient {
public:
    virtual void begin(const char* hostname, uint16_t port, Client& connectionClient);
    virtual void connect(const char* deviceName);
    virtual bool publish(const char* topic, const char* payload);
    virtual bool subscribe(const char* topic);
    virtual void setWill(const char* topic, const char* payload);

private:
    MQTTClient client;
    const char* hubName;
};