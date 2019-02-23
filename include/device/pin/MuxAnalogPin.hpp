#pragma once

#include <stdint.h>
#include <CD74HC4067.h>

#include "AnalogPin.hpp"

class MuxAnalogPin: public AnalogPin {

public:
    MuxAnalogPin(CD74HC4067* _mux, const uint8_t _channel, const uint8_t _originPinNumber);
    ~MuxAnalogPin();

    uint16_t read();
private:
    CD74HC4067* mux;
    const uint8_t channel;
    const uint8_t originPinNumber;
};