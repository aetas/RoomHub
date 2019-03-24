#include "mqtt/MqttEventPublisher.hpp"
#include <Arduino.h>

MqttEventPublisher::MqttEventPublisher() {

}

MqttEventPublisher& MqttEventPublisher::getInstance() {
    static MqttEventPublisher instance;
    return instance;
}

void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const uint8_t newValue) {
    Serial.print("New value: ");
    Serial.print(newValue);
    Serial.print(" on deviceId: ");
    Serial.println(deviceId);
}
void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const uint16_t newValue) {
     Serial.print("New value: ");
    Serial.print(newValue);
    Serial.print(" on deviceId: ");
    Serial.println(deviceId);
}
void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const char* newValue, const uint8_t length) {
    Serial.print("New value: ");
    Serial.print(newValue);
    Serial.print(" on deviceId: ");
    Serial.println(deviceId);
}
