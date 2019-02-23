#include "device/DigitalOutputDevice.hpp"

DigitalOutputDevice::~DigitalOutputDevice() {
    delete digitalPin;
}

void DigitalOutputDevice::setState(const uint8_t newState) {
    digitalPin->digitalWrite(newState);
}