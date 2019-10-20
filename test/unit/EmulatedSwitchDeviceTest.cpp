#include "../main/catch.hpp"
#include "device/EmulatedSwitchDevice.hpp"
#include "mocks/FakeDigitalPin.hpp"
#include "mocks/SimpleUpdateListener.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;


TEST_CASE("EmulatedSwitchDevice")
{
    FakeDigitalPin* pin = new FakeDigitalPin();
    EmulatedSwitchDevice device(1, pin);
    SimpleUpdateListener* listener = new SimpleUpdateListener();
    device.setUpdateListener(listener);

    SECTION("should set pin to HIGH state on start") {
        //then
        REQUIRE(pin->digitalRead() == HIGH);
    }

    SECTION("should change pin state when changing state on device") {
        // given
        pin->digitalWrite(HIGH);

        // when
        device.setProperty("state", "ON");
        string stringValueString(listener->stringValue);

        //then
        REQUIRE(pin->digitalRead() == LOW);
        REQUIRE(stringValueString == "ON");
    }


    SECTION("should release emulated switch by changing pin state back after specified time (500ms)") {
        // given
        pin->digitalWrite(HIGH);

        // when
        device.setProperty("state", "ON");
        device.loop(1000L);
        device.loop(1501L);
        string stringValueString(listener->stringValue);

        //then
        REQUIRE(pin->digitalRead() == HIGH);
        REQUIRE(stringValueString == "OFF");
    }

}