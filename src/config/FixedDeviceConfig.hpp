#pragma once

#include "config/DeviceConfig.hpp"


DeviceConfig switchButton1(1, DeviceType::DIGITAL_INPUT, 1, WireColor::BLUE);
DeviceConfig relay1(2, DeviceType::DIGITAL_OUTPUT, 1, WireColor::BLUE_WHITE);
DeviceConfig currentMeasurement1(3, DeviceType::ANALOG_INPUT, 2, WireColor::BROWN);
DeviceConfig dht22_1(4, DeviceType::DHT22, 2, WireColor::GREEN);

DeviceConfig devicesConfig[] = {switchButton1, currentMeasurement1, dht22_1, relay1};