#include "homie/HomieDeviceFactory.hpp"
#include "config/MasterConfig.hpp"
#include "ArduinoLog.h"

#include "WString.h"

HomieDeviceFactory::HomieDeviceFactory() {

}

HomieDeviceFactory::~HomieDeviceFactory() {

}


HomieDevice* HomieDeviceFactory::create(const char* ip, const char* mac, const char* hubName, 
                                        DeviceConfig** devicesConfig, const uint8_t numberOfDevices, 
                                        MqttClient& mqttClient, StatsData& statsData) {

    HomieNode** nodes = createNodes(hubName, devicesConfig, numberOfDevices, mqttClient);

  
    HomieDevice* homieDevice = new HomieDevice(hubName,
                                                HOMIE_STATS_INTERVAL_SEC,
                                                FIRMWARE_NAME,
                                                FIRMWARE_VERSION,
                                                ip,
                                                mac,
                                                nodes,
                                                numberOfDevices,
                                                mqttClient,
                                                statsData);
    return homieDevice;
}

HomieNode** HomieDeviceFactory::createNodes(const char* hubName, DeviceConfig** devicesConfig, uint8_t numberOfDevices, MqttClient& mqttClient) {

    HomieNode** homieNodes = new HomieNode*[numberOfDevices];
    for(uint8_t i = 0; i < numberOfDevices; i++) {
        HomieNodeProperty** properties = createHomieNodeProperties(devicesConfig[i]);
        const uint8_t numberOfProperties = propertiesNumber(devicesConfig[i]);
        
        char* deviceId = new char[2 + 3 * sizeof(int)]();
        strcpy(deviceId, String(devicesConfig[i]->getId()).c_str());

        homieNodes[i] = new HomieNode(hubName,
                                    deviceId,
                                    devicesConfig[i]->getName(),
                                    DeviceConfig::deviceTypeToString(devicesConfig[i]->getDeviceType()),
                                    properties,
                                    numberOfProperties,
                                    mqttClient);
  }

  return homieNodes;
}


HomieNodeProperty** HomieDeviceFactory::createHomieNodeProperties(DeviceConfig* node) {
  if(node->getDeviceType() == DeviceType::ANALOG_INPUT) {
    HomieNodeProperty** properties = new HomieNodeProperty*[1];
    properties[0] = new HomieNodeProperty("value", false, true, PropertyUnit::NONE, PropertyDataType::INTEGER, "0:4095");
    return properties;
  }
  if(node->getDeviceType() == DeviceType::BME280) {
    HomieNodeProperty** properties = new HomieNodeProperty*[2];
    properties[0] = new HomieNodeProperty("temperature", false, true, PropertyUnit::CELSIUS, PropertyDataType::FLOAT, "");
    properties[1] = new HomieNodeProperty("humidity", false, true, PropertyUnit::PERCENT, PropertyDataType::FLOAT, "");
    return properties;
  }
  if(node->getDeviceType() == DeviceType::DHT22) {
    HomieNodeProperty** properties = new HomieNodeProperty*[2];
    properties[0] = new HomieNodeProperty("temperature", false, true, PropertyUnit::CELSIUS, PropertyDataType::FLOAT, "");
    properties[1] = new HomieNodeProperty("humidity", false, true, PropertyUnit::PERCENT, PropertyDataType::FLOAT, "");
    return properties;
  }
  if(node->getDeviceType() == DeviceType::DIGITAL_INPUT) {
    HomieNodeProperty** properties = new HomieNodeProperty*[1];
    properties[0] = new HomieNodeProperty("state", false, false, PropertyUnit::NONE, PropertyDataType::INTEGER, "0,1");
    return properties;
  }
  if(node->getDeviceType() == DeviceType::DIGITAL_OUTPUT) {
    HomieNodeProperty** properties = new HomieNodeProperty*[1];
    properties[0] = new HomieNodeProperty("state", true, true, PropertyUnit::NONE, PropertyDataType::ENUM, "ON,OFF");
    return properties;
  }
  if(node->getDeviceType() == DeviceType::SCT013) {
    HomieNodeProperty** properties = new HomieNodeProperty*[1];
    properties[0] = new HomieNodeProperty("power", false, true, PropertyUnit::WATT, PropertyDataType::FLOAT, "");
    return properties;
  }
  if(node->getDeviceType() == DeviceType::EMULATED_SWITCH) {
    HomieNodeProperty** properties = new HomieNodeProperty*[1];
    properties[0] = new HomieNodeProperty("state", true, false, PropertyUnit::NONE, PropertyDataType::ENUM, "ON,OFF");
    return properties;
  }

  return nullptr;
}



const uint8_t HomieDeviceFactory::propertiesNumber(DeviceConfig* node) {
    switch (node->getDeviceType()) {
        case DeviceType::ANALOG_INPUT    : return 1;
        case DeviceType::BME280          : return 2;
        case DeviceType::DHT22           : return 2;
        case DeviceType::DIGITAL_INPUT   : return 1;
        case DeviceType::DIGITAL_OUTPUT  : return 1;
        case DeviceType::SCT013          : return 1;
        case DeviceType::EMULATED_SWITCH : return 1;
        default: return 0;
    }
}