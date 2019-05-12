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
    DigitalInputDevice device(1, pin, 0);
    SimpleUpdateListener* listener = new SimpleUpdateListener();

    SECTION("should call update listener when pin state has changed") {   
        // given
        device.setUpdateListener(listener);
        listener->smallIntValue = HIGH;

        // when
        pin->digitalWrite(LOW);
        device.loop(0);

        // then
        REQUIRE(listener->smallIntValue == LOW);
    }

    SECTION("should not fail when listener not set") {   
        // when
        pin->digitalWrite(LOW);
        device.loop(0);

        // then
        // do not crash because of NULL
    }

    SECTION("should ignore state change when it is shorter than debounceMs") {   
        // given
        DigitalInputDevice deviceWithDebounce(1, pin, 200);
        deviceWithDebounce.setUpdateListener(listener);
        listener->smallIntValue = HIGH;
        
        // when
        pin->digitalWrite(LOW);
        deviceWithDebounce.loop(0);
        deviceWithDebounce.loop(199);

        // then
        REQUIRE(listener->smallIntValue == HIGH);
    }

    SECTION("should update state when change duration is higher than debounceMs") {   
        // given
        DigitalInputDevice deviceWithDebounce(1, pin, 200);
        deviceWithDebounce.setUpdateListener(listener);
        listener->smallIntValue = HIGH;
        
        // when
        pin->digitalWrite(LOW);
        deviceWithDebounce.loop(0);
        deviceWithDebounce.loop(201);

        // then
        REQUIRE(listener->smallIntValue == LOW);
    }

    SECTION("should ignore state change when state has been bouncing during debounceMs") {   
        // given
        DigitalInputDevice deviceWithDebounce(1, pin, 100);
        deviceWithDebounce.setUpdateListener(listener);
        listener->smallIntValue = HIGH;
        
        // when
        pin->digitalWrite(LOW);
        deviceWithDebounce.loop(0);
        pin->digitalWrite(HIGH);
        deviceWithDebounce.loop(50);
        pin->digitalWrite(LOW);
        deviceWithDebounce.loop(101);

        // then
        REQUIRE(listener->smallIntValue == HIGH);
    }

    SECTION("should not send updated value when value has not changed and debounceMs == 0") {   
        // given
        DigitalInputDevice deviceWithoutDebounce(1, pin, 0);
        deviceWithoutDebounce.setUpdateListener(listener);
        listener->smallIntValue = HIGH;
        
        // when
        pin->digitalWrite(HIGH);
        deviceWithoutDebounce.loop(0);
        deviceWithoutDebounce.loop(1);
        deviceWithoutDebounce.loop(2);

        // then
        REQUIRE(listener->valueUpdatedCalledTimes == 0);
    }
}