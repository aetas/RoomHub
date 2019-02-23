#pragma once

#include "Device.hpp"
#include "pin/AnalogPin.hpp"

class AnalogInputDevice: public Device {

public:
    AnalogInputDevice(const uint16_t _id, AnalogPin* _analogPin): 
        Device(_id, DeviceType::ANALOG_INPUT), analogPin(_analogPin) {};

    ~AnalogInputDevice();

private:
    AnalogPin* analogPin;
};