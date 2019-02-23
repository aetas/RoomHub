#include "config/DeviceConfig.hpp"

DeviceConfig::DeviceConfig(uint16_t _id, DeviceType _type, uint8_t _portNumber, WireColor _wire):
    id(_id), 
    type(_type),
    portNumber(_portNumber),
    wire(_wire) {}

DeviceConfig::~DeviceConfig() {

}

const uint8_t DeviceConfig::getId() {
    return id;
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

