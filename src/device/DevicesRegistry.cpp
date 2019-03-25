#include "device/DevicesRegistry.hpp"
#include "device/DigitalInputDevice.hpp"

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
        if (devices[i]->getType() == DeviceType::DIGITAL_INPUT) {
            ((DigitalInputDevice*) devices[i])->loop(currentTimeMs);
        }
    }
}

void DevicesRegistry::setUpdateListener(UpdateListener* _listener) {
    for(uint8_t i = 0; i < currentNumberOfDevices; i++) {
        devices[i]->setUpdateListener(_listener);
    }
}

