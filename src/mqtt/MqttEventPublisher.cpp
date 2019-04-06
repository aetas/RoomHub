#include "mqtt/MqttEventPublisher.hpp"
#include "ArduinoLog.h"
#include "WString.h"

MqttEventPublisher::MqttEventPublisher(HomieDevice* _homieDevice): homieDevice(_homieDevice) {

}

MqttEventPublisher& MqttEventPublisher::getInstance(HomieDevice* _homieDevice) {
    static MqttEventPublisher instance(_homieDevice);
    return instance;
}

void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const char* propertyName, const uint8_t newValue) {
    String stringValue = "";
    stringValue += newValue;
    this->valueUpdated(deviceId, propertyName, stringValue.c_str());
}
void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const char* propertyName, const uint16_t newValue) {
    String stringValue = "";
    stringValue += newValue;
    this->valueUpdated(deviceId, propertyName, stringValue.c_str());
}
void MqttEventPublisher::valueUpdated(const uint8_t deviceId, const char* propertyName, const char* newValue) {
    Log.verbose("New value: %s on deviceId: %d, property %s" CR, newValue, deviceId, propertyName);

    HomieNode* node = homieDevice->getNode(deviceId);
    node->propertyValueUpdated(propertyName, newValue);
}
