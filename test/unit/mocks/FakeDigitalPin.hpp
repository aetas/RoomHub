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
    void pinMode(uint8_t mode) {
        string modeString;
        if (mode == INPUT) {
            modeString = "INPUT";
        } else {
            modeString = "OUTPUT";
        }
        cout << "Fake digital pin mode set to " << modeString << endl;
    }


private:
    uint8_t state = LOW;
};