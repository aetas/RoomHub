#include "../main/catch.hpp"
#include "device/Bme280Device.hpp"
#include "mocks/SimpleUpdateListener.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;


TEST_CASE("Bme280Device")
{
    Bme280Device device(1, 51);
    SimpleUpdateListener updateListener;
    device.setUpdateListener(&updateListener);

    SECTION("should notify about temperature, humidity and pressure when receiving new PJON message with values") {
        // when
        PjonMessage pjonMessage = PjonMessage::fromString("VALUES;2296;5435;99241");
        device.messageReceived(pjonMessage);

        // then
        float temperature = updateListener.receivedFloatValues["temperature"];
        float humidity = updateListener.receivedFloatValues["humidity"];
        uint32_t pressure = updateListener.receivedBigIntValues["pressure"];

        REQUIRE(temperature == 22.96f);
        REQUIRE(humidity == 54.35f);
        REQUIRE(pressure == 99241);

    }


    SECTION("should notify about state set to ready when received message in last 60 seconds") {
        // given
        const char* message = "PING;120";
        uint32_t time = 0;
        device.messageReceived(message, time);

        // when
        device.loop(59999);

        // then
        String state(updateListener.receivedStringValues["state"]);
        REQUIRE(state == "ready");
    }

    SECTION("should notify about lost device when not received any message for 60 seconds") {
        // given
        const char* message = "PING;150";
        uint32_t time = 60000;
        device.messageReceived(message, time);

        // when
        device.loop(time + 60001);

        // then
        String state(updateListener.receivedStringValues["state"]);
        REQUIRE(state == "lost");
    }

    SECTION("should notify about ready device when device was lost for some time but received new message") {
        // given
        const char* message = "PING;150";
        uint32_t time = 60000;
        device.messageReceived(message, time);

        // when
        device.loop(time + 60001);
        uint32_t newTime = 121000;
        device.messageReceived(message, newTime);
        device.loop(newTime);

        // then
        String state(updateListener.receivedStringValues["state"]);
        REQUIRE(state == "ready");
    }

    SECTION("should notify about uptime every 60 seconds") {
        // when
        const char* message = "PING;150";
        uint32_t time = 61000;
        device.messageReceived(message, time);
        device.loop(time);

        // then
        uint32_t uptime(updateListener.receivedBigIntValues["uptime"]);
        REQUIRE(uptime == 150);

        // when
        uint32_t newTime = 122000;
        const char* newMessage = "PING;210";
        device.messageReceived(newMessage, newTime);
        device.loop(newTime);

        // then
        uint32_t newUptime(updateListener.receivedBigIntValues["uptime"]);
        REQUIRE(newUptime == 210);
    }
}