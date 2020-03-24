#include "mqtt/MqttConnectionTester.hpp"
#include "ArduinoLog.h"

MqttConnectionTester::MqttConnectionTester(MqttClient& _mqttClient, const char *_connectionTestMqttTopic) : 
        mqttClient(_mqttClient), 
        connectionTestMqttTopic(_connectionTestMqttTopic) {
}

void MqttConnectionTester::subscribe() {
  mqttClient.subscribe(connectionTestMqttTopic);
}

void MqttConnectionTester::publishCurrentTime(const uint32_t &currentTimeMs) {
  if (currentTimeMs - lastPublishTimeMs > 200) {
    char currentTimeMsString[10];
    sprintf(currentTimeMsString, "%d", currentTimeMs);
    // Log.trace(F("MQTT Test connection: Publishing current time: %s" CR), currentTimeMsString);
    mqttClient.publish(connectionTestMqttTopic, currentTimeMsString, true, false);
    lastPublishTimeMs = currentTimeMs;
  }
}

void MqttConnectionTester::startGracePeriod(const uint32_t &currentTimeMs) {
  gracePeriodStartMs = currentTimeMs;
}

bool MqttConnectionTester::isTestTopic(const char* topic) {
  return (strcmp(topic, connectionTestMqttTopic) == 0);
}

void MqttConnectionTester::onNewConnectionTestTimeReceived(const char* connectionTestTimeString) {
  // Log.trace(F("MQTT Test connection: message received: %s" CR), connectionTestTimeString);
  uint32_t connectionTestTime = strtoul(connectionTestTimeString, NULL, 10);
  receivedConnectionTestTimeMs = connectionTestTime;
}

bool MqttConnectionTester::checkConnection(const uint32_t &currentTimeMs) {
  if (currentTimeMs - gracePeriodStartMs < 10000) { // grace period for starting device and in case of reconnection
    return true;
  }

  bool isConnectionOK = currentTimeMs - receivedConnectionTestTimeMs < 500;
  if (!isConnectionOK) { // in case of problem give time to reconnect before another check
    startGracePeriod(currentTimeMs);
  }

  return isConnectionOK;
}