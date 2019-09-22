#pragma once

#include <iostream>
#include <map>
#include "device/Device.hpp"
#include "WString.h"

using namespace std;

class FakeDevice: public Device {
public:
    FakeDevice(const uint16_t _id, DeviceType _deviceType): Device(_id, _deviceType) {};
    void fakeSmallIntChange(uint8_t newValue) { 
        if (this->updateListener == nullptr) {
            return;
        }
        this->updateListener->valueUpdated(this->getId(), "fakeValue", newValue); 
    };

    void setProperty(const char* propertyName, const char* newValue) {
        cout << "FAKE device: " << "Setting property " << propertyName << " = " << newValue << endl;
        properties[propertyName] = newValue;
    };

    const String currentPropertyValue(const char* propertyName) {
        return properties[propertyName];
    }

    void loop(const uint32_t& currentTimeMs) {
        lastLoopMs = currentTimeMs;
    }

    uint32_t getLastLoopMs() {
        return lastLoopMs;
    }

private:
    map<String, String> properties;
    uint32_t lastLoopMs = -1;
};
