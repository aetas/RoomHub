#include "../main/catch.hpp"
#include "device/DeviceFactory.hpp"
#include "mocks/FakePinProvider.hpp"
#include "device/pjon/PjonDevice.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;



TEST_CASE("DeviceFactory creates Device from DeviceConfiguration")
{
   PinProvider& pinProvider = FakePinProvider::getInstance();
   DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);

   SECTION("should create DigitalInputDevice when DIGITAL_INPUT DeviceConfig given") {
      // given
      DeviceConfig digitalInputDeviceConfig(24, "dev1", DeviceType::DIGITAL_INPUT, 3, WireColor::BLUE, 250);
      
      // when
      Device* device = deviceFactory.create(digitalInputDeviceConfig);

      // then
      REQUIRE(device->getId() == 24);
      REQUIRE(device->getType() == DeviceType::DIGITAL_INPUT);
   }  

   SECTION("should create DigitalOutputDevice when DIGITAL_OUTPUT DeviceConfig given") {
      // given
      DeviceConfig digitalOutputDeviceConfig(36, "dev2", DeviceType::DIGITAL_OUTPUT, 16, WireColor::BLUE_WHITE, 0);

      // when
      Device* device = deviceFactory.create(digitalOutputDeviceConfig);

      // then
      REQUIRE(device->getId() == 36);
      REQUIRE(device->getType() == DeviceType::DIGITAL_OUTPUT);
   }

   SECTION("should create AnalogInputDevice when ANALOG_INPUT DeviceConfig given") {
      // given
      DeviceConfig analogInputDeviceConfig(11, "dev3", DeviceType::ANALOG_INPUT, 16, WireColor::BROWN, 0);

      // when
      Device* device = deviceFactory.create(analogInputDeviceConfig);

      // then
      REQUIRE(device->getId() == 11);
      REQUIRE(device->getType() == DeviceType::ANALOG_INPUT);
   }

   SECTION("should create Dht22Device when DHT22 DeviceConfig given") {
      // given
      DeviceConfig dht22DeviceConfig(45, "dev4", DeviceType::DHT22, 1, WireColor::GREEN, 0);

      // when
      Device* device = deviceFactory.create(dht22DeviceConfig);

      // then
      REQUIRE(device->getId() == 45);
      REQUIRE(device->getType() == DeviceType::DHT22);
   }

    SECTION("should create SCT-013 when SCT013 DeviceConfig given") {
      // given
      DeviceConfig sct013DeviceConfig(46, "sct013A", DeviceType::SCT013, 2, WireColor::BROWN, 0);

      // when
      Device* device = deviceFactory.create(sct013DeviceConfig);

      // then
      REQUIRE(device->getId() == 46);
      REQUIRE(device->getType() == DeviceType::SCT013);
   }

   SECTION("should create EmulatedSwitchDevice when EMULATED_SWITCH DeviceConfig given") {
      // given
      DeviceConfig emulatedSwitchDeviceConfig(47, "emulated switch", DeviceType::EMULATED_SWITCH, 4, WireColor::BLUE, 0);

      // when
      Device* device = deviceFactory.create(emulatedSwitchDeviceConfig);

      // then
      REQUIRE(device->getId() == 47);
      REQUIRE(device->getType() == DeviceType::EMULATED_SWITCH);
   }

   SECTION("should create Bme280Device when BME280 DeviceConfig given") {
      // given
      DeviceConfig emulatedSwitchDeviceConfig(11, "BME280", DeviceType::BME280, 4, WireColor::BROWN_WHITE, 0, 140);

      // when
      PjonDevice* device = static_cast<PjonDevice*>(deviceFactory.create(emulatedSwitchDeviceConfig));

      // then
      REQUIRE(device->getId() == 11);
      REQUIRE(device->getType() == DeviceType::BME280);
      REQUIRE(device->getPjonId() == 140);
   }
}