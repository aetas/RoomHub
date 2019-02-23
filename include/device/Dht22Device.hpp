#pragma once

#include "Device.hpp"
#include "device/pin/DigitalPin.hpp"

class Dht22Device: public Device {

public:
    Dht22Device(const uint16_t _id, DigitalPin* _digitalPin): 
        Device(_id, DeviceType::DHT22), digitalPin(_digitalPin) {};

    ~Dht22Device();

private:
    DigitalPin* digitalPin;
};