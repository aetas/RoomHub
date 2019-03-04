#include "device/DigitalInputDevice.hpp"

DigitalInputDevice::~DigitalInputDevice() {}

void DigitalInputDevice::loop(const uint32_t& currentTimeMs) {
    uint8_t value = digitalPin->digitalRead();

    if ((inIntermediateState && currentTimeMs - intermediateStateStart > debounceMs) || debounceMs == 0)   {
          if (updateListener != nullptr) {
            updateListener->valueUpdated(getId(), value);
        }
        endIntermediateState();
    }

    if(currentState != value) {
        if(!inIntermediateState) {
            startIntermediateState(value, currentTimeMs);
        } else {
            endIntermediateState();
        }
        currentState = value;
    }
}

void DigitalInputDevice::startIntermediateState(uint8_t state, uint32_t currentTime) {
    inIntermediateState = true;
    intermediateStateStart = currentTime;
    intermediateState = state;
}

void DigitalInputDevice::endIntermediateState() {
    inIntermediateState = false;
}

