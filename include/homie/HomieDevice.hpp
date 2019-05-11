#pragma once

#include <stdint.h>
#include "HomieNode.hpp"
#include <string.h>
#include "Uptime.hpp"
#include "../mqtt/MqttClient.hpp"
#include "stats/StatsData.hpp"

#ifndef HOMIE_PREFIX
#define HOMIE_PREFIX "homie"
#endif

#ifndef HOMIE_IMPLEMENTATION
#define HOMIE_IMPLEMENTATION "Aetas"
#endif

#ifndef HOMIE_VERSION
#define HOMIE_VERSION           "3.0.1"
#endif

enum class HomieDeviceState {
    INIT, READY, DISCONNECTED, SLEEPING, LOST, ALERT
};

class HomieDevice {

public:
    HomieDevice(const char* _name, const uint8_t _statsIntervalSec,
                const char* _firmwareName, const char* _firmwareVersion, const char* _ip, const char* _mac,
                HomieNode** _nodes, const uint8_t _nodesNumber, MqttClient& _mqttClient,
                StatsData& _statsData);

    ~HomieDevice();

    
    const HomieDeviceState getState();
    HomieNode* getNode(uint8_t nodeId);

    void setState(HomieDeviceState state);

    void setup();
    void loop(const uint32_t& currentTimeMs);

private:
    char* topicStart;
    const char* name;

    uint32_t lastStatsUpdateMs = 0;
    const uint8_t statsIntervalSec;

    const char* firmwareName;
    const char* firmwareVersion;

    const char* ip;
    const char* mac;

    HomieNode** nodes;
    const uint8_t nodesNumber;

    HomieDeviceState state = HomieDeviceState::INIT;
    MqttClient& mqttClient;

    StatsData& statsData;

    Uptime uptime = Uptime();

    void updateStats(const uint32_t& currentTimeMs);
    const void refreshUptime(const uint32_t& currentTimeMs);
    const void refreshSignalStrength();
    const void refreshFreeHeapStats();
    const char* getNodesString();
};