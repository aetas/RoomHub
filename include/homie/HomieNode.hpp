#pragma once

#include <inttypes.h>
#include "HomieNodeProperty.hpp"
#include "mqtt/MqttClient.hpp"

#ifndef HOMIE_PREFIX
#define HOMIE_PREFIX "homie"
#endif

#ifndef HOMIE_IMPLEMENTATION
#define HOMIE_IMPLEMENTATION "Aetas"
#endif

class HomieNode {

public:
    HomieNode(const char* _deviceName, const char* _id, const char* _name, 
              const char* _type, HomieNodeProperty** _properties, const uint8_t _propertiesNumber,
              MqttClient& _mqttClient);

    ~HomieNode();

    void setup();

    const char* getId();
    const char* getName();
    const char* getType();
    const char* getPropertiesString();

    HomieNodeProperty** getProperties();
    const uint8_t getPropertiesNumber();

    void propertyValueUpdated(const char* propertyName, const char* newValue);

private:
    MqttClient& mqttClient;

    char* topicStart;
    const char* id;
    const char* name;
    const char* type;

    HomieNodeProperty** properties;
    const uint8_t propertiesNumber;

    void setupProperties();
};