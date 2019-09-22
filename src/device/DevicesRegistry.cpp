#include "device/DevicesRegistry.hpp"
#include "device/DigitalInputDevice.hpp"
#include "device/Sct013Device.hpp"
#include "device/AnalogInputDevice.hpp"
#include "device/EmulatedSwitchDevice.hpp"

#include "WString.h"
#include "ArduinoLog.h"

DevicesRegistry::DevicesRegistry(uint8_t numberOfDevices) {
    devices = new Device*[numberOfDevices];
}

DevicesRegistry::~DevicesRegistry() {
    delete[] devices;
}

void DevicesRegistry::add(Device* device) {
    devices[currentNumberOfDevices] = device;
    currentNumberOfDevices++;
}

void DevicesRegistry::loop(const uint32_t& currentTimeMs) {
    for(uint8_t i = 0; i < currentNumberOfDevices; i++) {
        devices[i]->loop(currentTimeMs);
    }
}

void DevicesRegistry::setUpdateListener(UpdateListener* _listener) {
    for(uint8_t i = 0; i < currentNumberOfDevices; i++) {
        devices[i]->setUpdateListener(_listener);
    }
}

Device* DevicesRegistry::getDevice(uint16_t deviceId) {
    for(uint8_t i = 0; i < currentNumberOfDevices; i++) {
        if (devices[i]->getId() == deviceId) {
            return devices[i];
        }
    }
    Log.error(F("Device with id=%d not found in registry" CR), deviceId);
    return nullptr;
}

