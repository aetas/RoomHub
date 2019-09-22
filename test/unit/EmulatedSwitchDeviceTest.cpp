#include "../main/catch.hpp"
#include "device/EmulatedSwitchDevice.hpp"
#include "mocks/FakeDigitalPin.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;


TEST_CASE("EmulatedSwitchDevice")
{
    FakeDigitalPin* pin = new FakeDigitalPin();
    EmulatedSwitchDevice device(1, pin);

    SECTION("should change pin state when changing state on device") {
        // given
        pin->digitalWrite(HIGH);

        // when
        device.setProperty("state", "ON");

        //then
        REQUIRE(pin->digitalRead() == LOW);
    }


    SECTION("should release emulated switch by changing pin state back after specified time (500ms)") {
        // given
        pin->digitalWrite(HIGH);

        // when
        device.setProperty("state", "ON");
        device.loop(1000L);
        device.loop(1501L);

        //then
        REQUIRE(pin->digitalRead() == HIGH);
    }

}