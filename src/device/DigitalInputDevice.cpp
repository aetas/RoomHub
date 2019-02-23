#include "device/DigitalInputDevice.hpp"

DigitalInputDevice::~DigitalInputDevice() {
    delete digitalPin;
}

void DigitalInputDevice::loop() {
    uint8_t value = digitalPin->digitalRead();
    if(currentState != value) {
        updateListener->valueUpdated(getId(), value);
        currentState = value;
    }
}