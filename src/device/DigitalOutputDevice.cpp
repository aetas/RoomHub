#include "device/DigitalOutputDevice.hpp"
#include <string.h>

DigitalOutputDevice::~DigitalOutputDevice() {
    delete digitalPin;
}

void DigitalOutputDevice::setProperty(const char* propertyName, const char* newValue) {
    if (strcmp("ON", newValue) == 0) {
        digitalPin->digitalWrite(ACTION_STATE);
        notify("state", newValue);
    } else {
        digitalPin->digitalWrite(DEFAULT_STATE);
        notify("state", "OFF");
    }
}