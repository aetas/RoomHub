#pragma once

#include <iostream>
#include "device/pin/DigitalPin.hpp"

using namespace std;

class FakeDigitalPin: public DigitalPin {

public:
    FakeDigitalPin() {};
    uint8_t digitalRead() {
        cout << "Fake digital read called" << endl;
        return state;
    };
    void digitalWrite(uint8_t val) {
        cout << "Fake digital write called" << endl;
        state = val;
    };

private:
    uint8_t state = LOW;
};