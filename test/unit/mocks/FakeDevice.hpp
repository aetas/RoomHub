#pragma once

#include <iostream>
#include "device/Device.hpp"

using namespace std;

class FakeDevice: public Device {
public:
    FakeDevice(const uint16_t _id, DeviceType _deviceType): Device(_id, _deviceType) {};
    void fakeSmallIntChange(uint8_t newValue) { 
        if (this->updateListener == nullptr) {
            return;
        }
        this->updateListener->valueUpdated(this->getId(), newValue); 
    };
};
