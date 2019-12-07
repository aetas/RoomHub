#include "device/AnalogInputDevice.hpp"
#include <stdio.h>

AnalogInputDevice::AnalogInputDevice(const uint16_t _id, AnalogPin* _analogPin): 
        Device(_id, DeviceType::ANALOG_INPUT), analogPin(_analogPin) {};

AnalogInputDevice::~AnalogInputDevice() {
}

void AnalogInputDevice::loop(const uint32_t& currentTimeMs) {
    if (READ_INTERVAL_MS < currentTimeMs - lastReadTime) {
        uint16_t value = analogPin->read();
        notify("value", (uint32_t) value);
        lastReadTime = currentTimeMs;
    }
}