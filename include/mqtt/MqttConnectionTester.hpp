#pragma once

#include <stdint.h>
#include "MqttClient.hpp"


class MqttConnectionTester {
public:
  MqttConnectionTester(MqttClient& _mqttClient, const char* _connectionTestMqttTopic);
  void publishCurrentTime(const uint32_t& currentTimeMs);
  bool isTestTopic(const char* topic);
  void onNewConnectionTestTimeReceived(const char* connectionTestTimeString);
  bool checkConnection(const uint32_t &currentTimeMs);
  void subscribe();

private:
  void startGracePeriod(const uint32_t &currentTimeMs);

  MqttClient& mqttClient;
  const char* connectionTestMqttTopic;
  uint32_t lastPublishTimeMs = 0;
  uint32_t receivedConnectionTestTimeMs = 0;
  uint32_t gracePeriodStartMs = 0;
};