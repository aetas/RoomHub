#pragma once

#include "config/DeviceConfig.hpp"

#define NUMBER_OF_DEVICES 5


DeviceConfig switchButton1(1, "switch", DeviceType::DIGITAL_INPUT, 13, WireColor::BLUE, 50);
DeviceConfig currentMeasurement1(3, "current", DeviceType::ANALOG_INPUT, 2, WireColor::BROWN, 0);
DeviceConfig dht22_1(4, "dht22", DeviceType::DHT22, 2, WireColor::GREEN, 0);
DeviceConfig relay1(2, "relay", DeviceType::DIGITAL_OUTPUT, 16, WireColor::GREEN_WHITE, 0);
DeviceConfig movementSensor(5, "movement", DeviceType::DIGITAL_INPUT, 13, WireColor::BLUE, 50);

DeviceConfig devicesConfig[] = {switchButton1, currentMeasurement1, dht22_1, relay1, movementSensor};