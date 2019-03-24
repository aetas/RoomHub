#include "mqtt/MqttEventPublisher.hpp"
#include "ArduinoLog.h"

MqttEventPublisher::MqttEventPublisher() {

}

MqttEventPublisher& MqttEventPublisher::getInstance() {
    static MqttEventPublisher instance;
    return instance;
}

void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const uint8_t newValue) {
    Log.verbose("New value: %d on deviceId: %d" CR, newValue, deviceId);
}
void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const uint16_t newValue) {
     Log.verbose("New value: %d on deviceId: %d" CR, newValue, deviceId);
}
void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const char* newValue, const uint8_t length) {
    Log.verbose("New value: %s on deviceId: %d" CR, newValue, deviceId);
}
