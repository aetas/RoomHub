#pragma once

#include "config/DeviceConfig.hpp"

#define NUMBER_OF_DEVICES 11


DeviceConfig switchButton1(1, "switch1", DeviceType::DIGITAL_INPUT, 1, WireColor::GREEN_WHITE, 50);
DeviceConfig switchButton2(2, "switch2", DeviceType::DIGITAL_INPUT, 4, WireColor::GREEN, 50);
DeviceConfig currentMeasurement1(3, "current", DeviceType::SCT013, 2, WireColor::BROWN, 0);
DeviceConfig dht22_1(4, "dht22", DeviceType::DHT22, 2, WireColor::GREEN, 0);
DeviceConfig relay1(5, "relay1", DeviceType::DIGITAL_OUTPUT, 5, WireColor::BLUE, 0);
DeviceConfig relay2(6, "relay2", DeviceType::DIGITAL_OUTPUT, 8, WireColor::BLUE_WHITE, 0);
DeviceConfig movementSensor1(7, "movement1", DeviceType::DIGITAL_INPUT, 9, WireColor::GREEN_WHITE, 50);
DeviceConfig movementSensor2(8, "movement2", DeviceType::DIGITAL_INPUT, 12, WireColor::GREEN, 50);
DeviceConfig switchButton3(9,  "switch3", DeviceType::DIGITAL_INPUT, 13, WireColor::BLUE_WHITE, 50);
DeviceConfig switchButton4(10, "switch4", DeviceType::DIGITAL_INPUT, 16, WireColor::BLUE_WHITE, 50);
DeviceConfig analogInput1(11, "analogInput1", DeviceType::ANALOG_INPUT, 3, WireColor::BROWN, 0);


DeviceConfig devicesConfig[] = {switchButton1, switchButton2, currentMeasurement1, dht22_1, relay1, relay2, movementSensor1, movementSensor2, switchButton3, switchButton4, analogInput1};