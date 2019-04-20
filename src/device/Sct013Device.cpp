#include "device/Sct013Device.hpp"

#include <stdio.h>


Sct013Device::Sct013Device(const uint16_t _id, AnalogPin* _analogPin): 
    Device(_id, DeviceType::SCT013), analogPin(_analogPin) {
        emon1.current(analogPin->getPinNumber(), 29.0323);
        emon1.calcIrms(1480);
        emon1.calcIrms(1480);
    }

Sct013Device::~Sct013Device() {}

void Sct013Device::loop(const uint32_t& currentTimeMs) {
    if (READ_INTERVAL_MS < currentTimeMs - lastReadTime) {
        double power = emon1.calcIrms(1480) * 230.0;
        char powerChar[15];
        sprintf(powerChar, "%f", power);
        updateListener->valueUpdated(getId(), "power", powerChar);
        lastReadTime = currentTimeMs;
    }

}