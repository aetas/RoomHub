#include "device/Device.hpp"


const uint16_t Device::getId() {
    return id; 
};

DeviceType Device::getType() {
    return type; 
};

void Device::setUpdateListener(UpdateListener* _listener) { 
    updateListener = _listener; 
}

void Device::notify(const char* propertyName, const char* value) {
    if (updateListener != nullptr) {
        updateListener->valueUpdated(getId(), "state", value);
    }
}

void Device::notify(const char* propertyName, const uint8_t value) {
    if (updateListener != nullptr) {
        updateListener->valueUpdated(getId(), "state", value);
    }
}

void Device::notify(const char* propertyName, const uint16_t value) {
    if (updateListener != nullptr) {
        updateListener->valueUpdated(getId(), "state", value);
    }
}