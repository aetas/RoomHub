#include "../main/catch.hpp"
#include "device/DevicesRegistry.hpp"
#include "mocks/FakeDevice.hpp"
#include "mocks/SimpleUpdateListener.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;

TEST_CASE("DevicesRegistry controls devices") {
    
    DevicesRegistry registry(5);
    SimpleUpdateListener updateListener;

    SECTION("should set update listener for all devices in registry") {
        // given
        FakeDevice fakeDevice1(1, DeviceType::DIGITAL_OUTPUT);
        FakeDevice fakeDevice2(2, DeviceType::DIGITAL_OUTPUT);
        registry.add(&fakeDevice1);
        registry.add(&fakeDevice2);

        // when
        registry.setUpdateListener(&updateListener);
        fakeDevice1.fakeSmallIntChange(5);
        fakeDevice2.fakeSmallIntChange(3);

        // then
        fakeDevice1.fakeSmallIntChange(5);
        REQUIRE(updateListener.smallIntValue == 5);
        fakeDevice2.fakeSmallIntChange(3);
        REQUIRE(updateListener.smallIntValue == 3);
    }

    SECTION("should call loop on every device during loop") {
        // given
        FakeDevice fakeDevice1(1, DeviceType::DIGITAL_OUTPUT);
        FakeDevice fakeDevice2(2, DeviceType::DIGITAL_OUTPUT);
        registry.add(&fakeDevice1);
        registry.add(&fakeDevice2);
        
        // when
        registry.loop(1000L);

        // then
        REQUIRE(fakeDevice1.getLastLoopMs() == 1000L);
        REQUIRE(fakeDevice2.getLastLoopMs() == 1000L);
    }
}