#pragma once

#include <stdint.h>

class Client {

};

class MQTTClient {
public:
    void begin(const char* hostname, uint16_t port, Client& connectionClient) {};
    bool connect(const char* deviceName) {};
    bool publish(const char* topic, const char* payload) {};
    bool subscribe(const char* topic) {};
    void setWill(const char* topic, const char* payload) {}

};

