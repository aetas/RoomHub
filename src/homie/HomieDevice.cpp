#include "homie/HomieDevice.hpp"

#include <stdlib.h>
#include <WString.h>
#include <stdio.h>
#include "ArduinoLog.h"


HomieDevice::HomieDevice(const char* _name, const uint8_t _statsIntervalSec,
                         const char*_firmwareName, const char*_firmwareVersion, const char* _ip, const char* _mac,
                         HomieNode** _nodes, const uint8_t _nodesNumber, MqttClient& _mqttClient,
                         StatsData& _statsData): 
        name(_name),
        statsIntervalSec(_statsIntervalSec),
        firmwareName(_firmwareName),
        firmwareVersion(_firmwareVersion),
        ip(_ip),
        mac(_mac),
        nodes(_nodes),
        nodesNumber(_nodesNumber),
        mqttClient(_mqttClient),
        statsData(_statsData) {
    
    String topicStartString = HOMIE_PREFIX "/";
    topicStartString += name;

    topicStart = new char[topicStartString.length()]();
    strcpy(topicStart, topicStartString.c_str());
}

HomieDevice::~HomieDevice() {
    delete[] topicStart;
}

void HomieDevice::setup() {
    String stateTopic = topicStart;
    stateTopic += "/$state";
    mqttClient.connect(name, stateTopic.c_str(), 1, 1, "lost");

    String homieVersionTopic = topicStart;
    homieVersionTopic += "/$homie";
    mqttClient.publish(homieVersionTopic.c_str(), HOMIE_VERSION, true);
    String nameTopic = topicStart;
    nameTopic += "/$name";
    mqttClient.publish(nameTopic.c_str(), name, true);
    String nodesListTopic = topicStart;
    nodesListTopic += "/$nodes";
    const char* nodesString = getNodesString();
    mqttClient.publish(nodesListTopic.c_str(), nodesString, true);
    String implementationTopic = topicStart;
    implementationTopic += "/$implementation";
    mqttClient.publish(implementationTopic.c_str(), HOMIE_IMPLEMENTATION, true);
    String firmwareNameTopic = topicStart;
    firmwareNameTopic += "/$fw/name";
    mqttClient.publish(firmwareNameTopic.c_str(), firmwareName, true);
    String firmwareVersionTopic = topicStart;
    firmwareVersionTopic += "/$fw/version";
    mqttClient.publish(firmwareVersionTopic.c_str(), firmwareVersion, true);
    String ipTopic = topicStart;
    ipTopic += "/$localip";
    mqttClient.publish(ipTopic.c_str(), ip, true);
    String macTopic = topicStart;
    macTopic += "/$mac";
    mqttClient.publish(macTopic.c_str(), mac, true);
    String statsListTopic = topicStart;
    statsListTopic += "/$stats";
    mqttClient.publish(statsListTopic.c_str(), "uptime,signal,freeheap", true);
    String statsIntervalTopic = topicStart;
    statsIntervalTopic += "/$stats/interval";
    char statsIntervalSecString[4];
    sprintf(statsIntervalSecString, "%d", statsIntervalSec);
    mqttClient.publish(statsIntervalTopic.c_str(), statsIntervalSecString, true);

    mqttClient.publish(stateTopic.c_str(), "ready", true);

    for(uint8_t i = 0; i < nodesNumber; i++) {
        nodes[i]->setup();
    }
}

boolean HomieDevice::loop(const uint32_t& currentTimeMs) {
    if (!mqttClient.loop()) {
        Log.warning(F("Problem with MQTT communication. Trying to reconnect..." CR));
        setup();
        return false;
    }
    updateStats(currentTimeMs);
    return true;
}

void HomieDevice::updateStats(const uint32_t& currentTimeMs) {
    if (statsIntervalSec*1000 < currentTimeMs - lastStatsUpdateMs) {
        refreshUptime(currentTimeMs);
        refreshSignalStrength();
        refreshFreeHeapStats();
        lastStatsUpdateMs = currentTimeMs;
    }
}
    
const HomieDeviceState HomieDevice::getState() {
    return state;
}

const char* HomieDevice::getNodesString() {
    String nodesString = "";
    for(uint8_t i = 0; i < nodesNumber; i++) {
        nodesString += nodes[i]->getId();
        if (i < nodesNumber -1) {
            nodesString += ',';
        }
    }
    char* nodesWithCharArray = new char[nodesString.length()]();
    strcpy(nodesWithCharArray, nodesString.c_str());

    return nodesWithCharArray;
}
const void HomieDevice::refreshUptime(const uint32_t& currentTimeMs) {
    char uptimeSecString[10];
    sprintf(uptimeSecString, "%d", uptime.uptimeSec(currentTimeMs));
    String uptimeTopic = topicStart;
    uptimeTopic += "/$stats/uptime";
    mqttClient.publish(uptimeTopic.c_str(), uptimeSecString, true);
}
const void HomieDevice::refreshSignalStrength() {
    String signalStrengthTopic = topicStart;
    signalStrengthTopic += "/$stats/signal";
    String signalStrengthString = String(statsData.getSignalStrength());
    mqttClient.publish(signalStrengthTopic.c_str(), signalStrengthString.c_str(), true);
}

const void HomieDevice::refreshFreeHeapStats() {
    String signalStrengthTopic = topicStart;
    signalStrengthTopic += "/$stats/freeheap";
    String freeHeapStatsString = String(statsData.getFreeHeapInBytes());
    mqttClient.publish(signalStrengthTopic.c_str(), freeHeapStatsString.c_str(), true);
}

void HomieDevice::setState(HomieDeviceState state) {
    this->state = state;
}

HomieNode* HomieDevice::getNode(uint8_t nodeId) {
    for(uint8_t i = 0; i < nodesNumber; i++) {
        uint8_t id = atoi(nodes[i]->getId());
        if (id == nodeId) {
            return nodes[i];
        }
    }
    Log.error(F("Homie node with id %d not found" CR), nodeId);
    return nullptr;
}