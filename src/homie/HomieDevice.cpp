#include "homie/HomieDevice.hpp"

#include <stdlib.h>
#include <WString.h>
#include <stdio.h>
#include "ArduinoLog.h"


HomieDevice::HomieDevice(const char* _name, const uint8_t _statsIntervalSec,
                         const char*_firmwareName, const char*_firmwareVersion, const char* _ip, const char* _mac,
                         HomieNode** _nodes, const uint8_t _nodesNumber, MqttClient& _mqttClient): 
        name(_name), 
        homieVersion(HOMIE_VERSION),
        statsIntervalSec(_statsIntervalSec),
        firmwareName(_firmwareName),
        firmwareVersion(_firmwareVersion),
        ip(_ip),
        mac(_mac),
        nodes(_nodes),
        nodesNumber(_nodesNumber),
        mqttClient(_mqttClient) {
    
    String topicStartString = HOMIE_PREFIX "/";
    topicStartString += name;

    topicStart = new char[topicStartString.length()]();
    strcpy(topicStart, topicStartString.c_str());

    String stateTopic = topicStart;
    stateTopic += "/$state";
    mqttClient.setWill(stateTopic.c_str(), "lost");
}

HomieDevice::~HomieDevice() {
    delete[] topicStart;
}

void HomieDevice::setup() {
    String homieVersionTopic = topicStart;
    homieVersionTopic += "/$homie";
    mqttClient.publish(homieVersionTopic.c_str(), homieVersion);
    String nameTopic = topicStart;
    nameTopic += "/$name";
    mqttClient.publish(nameTopic.c_str(), name);
    String nodesListTopic = topicStart;
    nodesListTopic += "/$nodes";
    const char* nodesString = getNodesString();
    mqttClient.publish(nodesListTopic.c_str(), getNodesString());
    delete[] nodesString;
    String implementationTopic = topicStart;
    implementationTopic += "/$implementation";
    mqttClient.publish(implementationTopic.c_str(), HOMIE_IMPLEMENTATION);
    String firmwareNameTopic = topicStart;
    firmwareNameTopic += "/$fw/name";
    mqttClient.publish(firmwareNameTopic.c_str(), firmwareName);
    String firmwareVersionTopic = topicStart;
    firmwareVersionTopic += "/$fw/version";
    mqttClient.publish(firmwareVersionTopic.c_str(), firmwareVersion);
    String ipTopic = topicStart;
    ipTopic += "/$localip";
    mqttClient.publish(ipTopic.c_str(), ip);
    String macTopic = topicStart;
    macTopic += "/$mac";
    mqttClient.publish(macTopic.c_str(), mac);
    String statsListTopic = topicStart;
    statsListTopic += "/$stats";
    mqttClient.publish(statsListTopic.c_str(), "uptime,signal");
    String statsIntervalTopic = topicStart;
    statsIntervalTopic += "/$stats/interval";
    char statsIntervalSecString[4];
    sprintf(statsIntervalSecString, "%d", statsIntervalSec);
    mqttClient.publish(statsIntervalTopic.c_str(), statsIntervalSecString);
    String uptimeTopic = topicStart;
    uptimeTopic += "/$stats/uptime";
    mqttClient.publish(uptimeTopic.c_str(), "0");
    String stateTopic = topicStart;
    stateTopic += "/$state";
    mqttClient.publish(stateTopic.c_str(), "ready");

    for(uint8_t i = 0; i < nodesNumber; i++) {
        nodes[i]->setup();
    }
}

void HomieDevice::loop(const uint32_t& currentTimeMs) {
    updateStats(currentTimeMs);
}

void HomieDevice::updateStats(const uint32_t& currentTimeMs) {
    if (statsIntervalSec*1000 < currentTimeMs - lastStatsUpdateMs) {
        refreshUptime(currentTimeMs);
        refreshSignalStrength();
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
    mqttClient.publish(uptimeTopic.c_str(), uptimeSecString);
}
const void HomieDevice::refreshSignalStrength() {
    String signalStrengthTopic = topicStart;
    signalStrengthTopic += "/$stats/signal";
    mqttClient.publish(signalStrengthTopic.c_str(), "0"); // TODO maj: real signal strength needed
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