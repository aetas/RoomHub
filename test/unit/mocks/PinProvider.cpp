#include "device/pin/PinProvider.hpp"
#include "FakeDigitalPin.hpp"
#include "FakeAnalogPin.hpp"

PinProvider::PinProvider() {

}

PinProvider& PinProvider::getInstance() {
    static PinProvider instance;
    return instance;
}

DigitalPin* PinProvider::digitalPin(const uint8_t portNumber, const WireColor& wireColor) {
    return new FakeDigitalPin();
}

AnalogPin* PinProvider::analogPin(const uint8_t portNumber) {
    return new FakeAnalogPin();
}