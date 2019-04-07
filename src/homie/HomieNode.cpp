#include "homie/HomieNode.hpp"
#include <string.h>
#include <WString.h>

#include "ArduinoLog.h"



HomieNode::HomieNode(const char* _deviceName, const char* _id, const char* _name, 
                     const char* _type, HomieNodeProperty** _properties, const uint8_t _propertiesNumber,
                     MqttClient& _mqttClient)
    : name(_name), id(_id), type(_type), properties(_properties), propertiesNumber(_propertiesNumber), mqttClient(_mqttClient) {

    String topicStartString = HOMIE_PREFIX "/";
    topicStartString += _deviceName;
    topicStartString += "/";
    topicStartString += _id;

    topicStart = new char[topicStartString.length()]();
    strcpy(topicStart, topicStartString.c_str());
}

HomieNode::~HomieNode() {}

void HomieNode::setup() {
    String nameTopic = topicStart;
    nameTopic += "/$name";
    mqttClient.publish(nameTopic.c_str(), name, true);
    String typeTopic = topicStart;
    typeTopic += "/$type";
    mqttClient.publish(typeTopic.c_str(), type, true);
    String propertiesTopic = topicStart;
    propertiesTopic += "/$properties";
    mqttClient.publish(propertiesTopic.c_str(), getPropertiesString(), true);

    setupProperties();
    
}

void HomieNode::setupProperties() {
    
    for(uint8_t i = 0; i < propertiesNumber; i++) {
        HomieNodeProperty* property = properties[i];
        String propertyTopic = topicStart;
        propertyTopic += "/";
        propertyTopic += property->getName();
        
        String settableTopic = propertyTopic;
        settableTopic += "/$settable";
        mqttClient.publish(settableTopic.c_str(), property->isSettable() ? "true" : "false", true);
        String retainedTopic = propertyTopic;
        retainedTopic += "/$retained";
        mqttClient.publish(retainedTopic.c_str(), property->isRetained() ? "true" : "false", true);
        String unitTopic = propertyTopic;
        unitTopic += "/$unit";
        mqttClient.publish(unitTopic.c_str(), property->getUnit(), true);
        String datatypeTopic = propertyTopic;
        datatypeTopic += "/$datatype";
        mqttClient.publish(datatypeTopic.c_str(), property->getDataType(), true);
        String formatTopic = propertyTopic;
        formatTopic += "/$format";
        mqttClient.publish(formatTopic.c_str(), property->getFormat(), true);

        if (property->isSettable()) {
            String propertySetTopic = propertyTopic;
            propertySetTopic += "/set";
            mqttClient.subscribe(propertySetTopic.c_str());
        }
        
    }
}

const char* HomieNode::getId() {
    return id;
}

const char* HomieNode::getName() {
    return name;
}

const char* HomieNode::getType() {
    return type;
}

const char* HomieNode::getPropertiesString() {
    String props = "";
    for(uint8_t i = 0; i < propertiesNumber; i++) {
        props += properties[i]->getName();
        if (i < propertiesNumber-1) {
            props += ",";
        }
    }
    char* propsCharArray = new char[props.length()]();
    strcpy(propsCharArray, props.c_str());

    return propsCharArray;
}

HomieNodeProperty* HomieNode::getProperty(const char* name) {
    for(uint8_t i = 0; i < propertiesNumber; i++) {
        if (strcmp(properties[i]->getName(), name) == 0) {
            return properties[i];
        }
    }
    Log.error(F("Property '%s' not found" CR), name);
    return nullptr;
}

const uint8_t HomieNode::getPropertiesNumber() {
    return propertiesNumber;
}

void HomieNode::propertyValueUpdated(const char* propertyName, const char* newValue) {
    HomieNodeProperty* property = getProperty(propertyName);
    if (property == nullptr) return;

    String propertyTopic = topicStart;
    propertyTopic += "/";
    propertyTopic += propertyName;
    mqttClient.publish(propertyTopic.c_str(), newValue, property->isRetained());
}