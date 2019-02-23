#include "../main/catch.hpp"
#include "device/DigitalOutputDevice.hpp"
#include "mocks/FakeDigitalPin.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;


TEST_CASE("DigitalOutputDevice")
{
    FakeDigitalPin* pin = new FakeDigitalPin();
    DigitalOutputDevice device(1, pin);

    SECTION("should change pin state when write HIGH to device") {   
        // when
        device.setState(HIGH);

        //then
        REQUIRE(pin->digitalRead() == HIGH);
    }

    SECTION("should change pin state when write LOW to device which was previously HIGH") {   
        // when
        device.setState(HIGH);
        device.setState(LOW);

        //then
        REQUIRE(pin->digitalRead() == LOW);
    }
}