#include "../main/catch.hpp"
#include "device/DigitalInputDevice.hpp"
#include "mocks/FakeDigitalPin.hpp"
#include "mocks/SimpleUpdateListener.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;


TEST_CASE("DigitalInputDevice")
{
    FakeDigitalPin* pin = new FakeDigitalPin();
    DigitalInputDevice device(1, pin, LOW);
    SimpleUpdateListener* listener = new SimpleUpdateListener();

    SECTION("should call update listener when pin state has changed") {   
        // given
        device.setUpdateListener(listener);

        //when
        pin->digitalWrite(HIGH);
        device.loop();

        //then
        REQUIRE(listener->smallIntValue == HIGH);
    }
}