#include "config/DeviceConfig.hpp"

DeviceConfig::DeviceConfig(uint8_t _id, const char* _name, DeviceType _type, uint8_t _portNumber, WireColor _wire, uint16_t _debounceMs):
    id(_id), 
    name(_name),
    type(_type),
    portNumber(_portNumber),
    wire(_wire),
    debounceMs(_debounceMs) {}

DeviceConfig::~DeviceConfig() {

}

const uint8_t DeviceConfig::getId() {
    return id;
}

const char* DeviceConfig::getName() {
    return name;
}
    
const DeviceType DeviceConfig::getDeviceType() {
    return type;
}

const uint8_t DeviceConfig::getPortNumber() {
    return portNumber;
}

const WireColor DeviceConfig::getWireColor() {
    return wire;
}

const uint16_t DeviceConfig::getDebounceMs() {
    return debounceMs;
}

const char* DeviceConfig::deviceTypeToString(DeviceType deviceType) {
    switch(deviceType) {
        case DeviceType::ANALOG_INPUT:      return "AnalogInput";
        case DeviceType::BME280 :           return "BME280";
        case DeviceType::DHT22 :            return "DHT22";
        case DeviceType::DIGITAL_INPUT :    return "DigitalInput";
        case DeviceType::DIGITAL_OUTPUT :   return "DigitalOutput";
        case DeviceType::SCT013 :           return "SCT-013";
        default: return "UNKNOWN";
    }
}