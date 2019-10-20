#include "../main/catch.hpp"
#include "device/DigitalOutputDevice.hpp"
#include "mocks/FakeDigitalPin.hpp"
#include "mocks/SimpleUpdateListener.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;


TEST_CASE("DigitalOutputDevice")
{
    FakeDigitalPin* pin = new FakeDigitalPin();
    DigitalOutputDevice device(1, pin);

    SECTION("should set pin state to HIGH on start") {
        //then
        REQUIRE(pin->digitalRead() == HIGH);
    }

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

    SECTION("should notify update listener on state change to ON") {
        // given
        SimpleUpdateListener* listener = new SimpleUpdateListener();
        device.setUpdateListener(listener);

        // when
        device.setProperty("state", "ON");
        string stringValueString(listener->stringValue);

        // then
        REQUIRE(stringValueString == "ON");
    }

    SECTION("should notify update listener on state change to OFF") {
        // given
        SimpleUpdateListener* listener = new SimpleUpdateListener();
        device.setUpdateListener(listener);

        // when
        device.setProperty("state", "ON");
        device.setProperty("state", "OFF");
        string stringValueString(listener->stringValue);

        // then
        REQUIRE(stringValueString == "OFF");
    }
}