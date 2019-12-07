#pragma once

#include "pjon/PjonDevice.hpp"

class Bme280Device: public PjonDevice {

public:
    Bme280Device(const uint16_t _id, const uint8_t _pjonId);
    using PjonDevice::messageReceived;
    void messageReceived(PjonMessage& message);

private:
    static const char* MESSAGE_TYPE_VALUES;
};