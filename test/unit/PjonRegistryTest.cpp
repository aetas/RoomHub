#include "../main/catch.hpp"
#include "mocks/FakePjonDevice.hpp"
#include "device/pjon/PjonRegistry.hpp"


#include <typeinfo>
#include <iostream>
#include <string.h>
using namespace std;

TEST_CASE("PjonRegistry")
{
    PjonRegistry pjonRegistry(10);

    SECTION("should pass message to PjonDevice of given PjonId when message received") {
        // given
        FakePjonDevice device(1, DeviceType::BME280, 145);
        pjonRegistry.addDevice(&device);

        // when
        pjonRegistry.messageReceived(145, "TEST;123", 0);

        // then
        REQUIRE(device.getLastReceivedMessageType() == "TEST");
        REQUIRE(device.getLastReceivedMessageValues()[0] == "123");
    }

    SECTION("should not pass message to PjonDevice with different PjonId when message received") {
        // given
        FakePjonDevice device1(1, DeviceType::BME280, 100);
        FakePjonDevice device2(2, DeviceType::BME280, 101);
        pjonRegistry.addDevice(&device1);
        pjonRegistry.addDevice(&device2);

        // when
        pjonRegistry.messageReceived(101, "TEST;777", 0);

        // then
        REQUIRE(device1.getLastReceivedMessageType() == "EMPTY");
        REQUIRE(device2.getLastReceivedMessageType() == "TEST");
        REQUIRE(device2.getLastReceivedMessageValues()[0] == "777");
    }
}