#pragma once

#include <iostream>
#include "device/pin/AnalogPin.hpp"

using namespace std;

class FakeAnalogPin: public AnalogPin {

public:
    FakeAnalogPin() {};
    uint16_t read() {
        cout << "Fake analog read called" << endl;
        return value;
    };
    void setValue(uint16_t fakeValue) {
        cout << "Fake analog value set to " << fakeValue << endl;
        value = fakeValue;
    }   

private:
    uint16_t value = 0;
};