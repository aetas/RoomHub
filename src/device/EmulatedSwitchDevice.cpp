#include "device/EmulatedSwitchDevice.hpp"
#include <string.h>

EmulatedSwitchDevice::~EmulatedSwitchDevice() {
    delete digitalPin;
}

void EmulatedSwitchDevice::setProperty(const char* propertyName, const char* newValue) {
    if (strcmp("ON", newValue) == 0) {
        digitalPin->digitalWrite(ACTION_STATE);
        isPressed = true;
        notify("state", newValue);
    }
}

void EmulatedSwitchDevice::loop(const uint32_t& currentTimeMs) {
    if (isPressed && !pressedAcknowledged) {
        pressedOnMs = currentTimeMs;
        pressedAcknowledged = true;
    } else if (pressedAcknowledged && currentTimeMs - pressedOnMs > PRESS_TIME_MS) {
        isPressed = false;
        pressedAcknowledged = false;
        digitalPin->digitalWrite(DEFAULT_STATE);
        notify("state", "OFF");
    }
}