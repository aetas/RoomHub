#include "../main/catch.hpp"
#include "config/Configuration.hpp"

#include "mocks/FakeConfigurationStorage.hpp"
#include "mocks/FakeConfigurationServer.hpp"

#include <typeinfo>
#include <iostream>
#include <string.h>
using namespace std;

TEST_CASE("Configuration")
{
    Configuration configuration;
    DeviceConfigParser deviceConfigParser;
    FakeConfigurationStorage configurationStorage(deviceConfigParser);
    FakeConfigurationServer configurationServer;

    SECTION("should read basic configuration from storage") {
        // given
        configurationStorage.storeName("Some RoomHub Name");
        configurationStorage.storeMqttHostname("192.168.144.145");

        // when
        configuration.loadConfiguration(configurationStorage, configurationServer);

        // then
        REQUIRE(string(configuration.getRoomHubName()) == "Some RoomHub Name");
        REQUIRE(string(configuration.getMqttHostname()) == "192.168.144.145");
    }

    SECTION("should read devices configuration from storage") {
        // given
        configurationStorage.storeName("Some RoomHub Name");
        configurationStorage.storeMqttHostname("192.168.144.145");
        configurationStorage.storeDeviceConfig("1.0;101;switch_1;1;1;3;50;0");
        configurationStorage.storeDeviceConfig("1.0;102;relay 123;2;2;4;150;0");

        // when
        configuration.loadConfiguration(configurationStorage, configurationServer);

        // then
        REQUIRE(configuration.getNumberOfDevices() == 2);
        DeviceConfig** devicesConfig = configuration.getDevicesConfig();
        REQUIRE(devicesConfig[0]->getId() == 101);
        REQUIRE(string(devicesConfig[0]->getName()) == "switch_1");
        REQUIRE(devicesConfig[0]->getDeviceType() == DeviceType::DIGITAL_INPUT);
        REQUIRE(devicesConfig[0]->getPortNumber() == 1);
        REQUIRE(devicesConfig[0]->getWireColor() == WireColor::GREEN_WHITE);
        REQUIRE(devicesConfig[0]->getDebounceMs() == 50);

        REQUIRE(devicesConfig[1]->getId() == 102);
        REQUIRE(string(devicesConfig[1]->getName()) == "relay 123");
        REQUIRE(devicesConfig[1]->getDeviceType() == DeviceType::DIGITAL_OUTPUT);
        REQUIRE(devicesConfig[1]->getPortNumber() == 2);
        REQUIRE(devicesConfig[1]->getWireColor() == WireColor::BLUE);
        REQUIRE(devicesConfig[1]->getDebounceMs() == 150);
    }

    SECTION("should start WebConfigurationServer when configuration is not set") {
        // given
        // No configuration set

        // when
        configuration.loadConfiguration(configurationStorage, configurationServer);

        // then
        REQUIRE(configurationServer.isRunning() == true);
    }
}