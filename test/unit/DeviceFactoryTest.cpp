#include "../main/catch.hpp"
#include "device/DeviceFactory.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;



TEST_CASE("DeviceFactory creates Device from DeviceConfiguration")
{
   PinProvider& pinProvider = PinProvider::getInstance();
   DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);

   SECTION("should create DigitalInputDevice when DIGITAL_INPUT DeviceConfig given") {
      // given
      DeviceConfig digitalInputDeviceConfig(24, DeviceType::DIGITAL_INPUT, 3, WireColor::BLUE);
      
      // when
      Device* device = deviceFactory.create(digitalInputDeviceConfig);

      // then
      REQUIRE(device->getId() == 24);
      REQUIRE(device->getType() == DeviceType::DIGITAL_INPUT);
   }  

   SECTION("should create DigitalOutputDevice when DIGITAL_OUTPUT DeviceConfig given") {
      // given
      DeviceConfig digitalOutputDeviceConfig(36, DeviceType::DIGITAL_OUTPUT, 16, WireColor::BLUE_WHITE);

      // when
      Device* device = deviceFactory.create(digitalOutputDeviceConfig);

      // then
      REQUIRE(device->getId() == 36);
      REQUIRE(device->getType() == DeviceType::DIGITAL_OUTPUT);
   }

   SECTION("should create AnalogInputDevice when ANALOG_INPUT DeviceConfig given") {
      // given
      DeviceConfig digitalOutputDeviceConfig(11, DeviceType::ANALOG_INPUT, 16, WireColor::BROWN);

      // when
      Device* device = deviceFactory.create(digitalOutputDeviceConfig);

      // then
      REQUIRE(device->getId() == 11);
      REQUIRE(device->getType() == DeviceType::ANALOG_INPUT);
   }

   SECTION("should create Dht22Device when DHT22 DeviceConfig given") {
      // given
      DeviceConfig dht22DeviceConfig(45, DeviceType::DHT22, 1, WireColor::GREEN);

      // when
      Device* device = deviceFactory.create(dht22DeviceConfig);

      // then
      REQUIRE(device->getId() == 45);
      REQUIRE(device->getType() == DeviceType::DHT22);
   }

}