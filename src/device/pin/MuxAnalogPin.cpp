#include "device/pin/MuxAnalogPin.hpp"
#include <Arduino.h>

#define arduinoAnalogRead analogRead

MuxAnalogPin::MuxAnalogPin(CD74HC4067* _mux, const uint8_t _channel, const uint8_t _originPinNumber):
    mux(_mux), 
    channel(_channel),
    originPinNumber(_originPinNumber) {

}

MuxAnalogPin::~MuxAnalogPin() {

}

uint16_t MuxAnalogPin::read() {
    mux->channel(channel);
    return analogRead(originPinNumber);
}

uint8_t MuxAnalogPin::getPinNumber() {
    return originPinNumber;
}