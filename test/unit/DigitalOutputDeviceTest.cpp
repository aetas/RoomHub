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

    SECTION("should change pin state when changing state on device") {   
        // when
        device.setProperty("state", "OFF");

        //then
        REQUIRE(pin->digitalRead() == HIGH);
    }

    SECTION("should change pin state when changing state to ON on device which was previously OFF") {   
        // when
        device.setProperty("state", "OFF");
        device.setProperty("state", "ON");

        //then
        REQUIRE(pin->digitalRead() == LOW);
    }
}