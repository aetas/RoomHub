#pragma once

#include "MqttClient.hpp"
#include "log/BufferedLogger.hpp"

class MqttLogger {
public:
    MqttLogger(MqttClient& mqttClient, BufferedLogger& BufferedLogger, const char* topic);
    void loop(uint32_t now);
    void sendLogs();
private:
    MqttClient& mqttClient;
    BufferedLogger& logger;
    const char* topic;
    uint32_t lastTimeLogPublished = 0;
};