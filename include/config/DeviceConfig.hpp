#pragma once

#include <stdint.h>

enum class DeviceType {
    DIGITAL_INPUT = 1,
    DIGITAL_OUTPUT = 2,
    ANALOG_INPUT = 3,
    DHT22 = 4,
    BME280 = 5
};

enum class WireColor {
    ORANGE_WHITE = 1,
    ORANGE = 2,
    GREEN_WHITE = 3,
    BLUE = 4,
    BLUE_WHITE = 5,
    GREEN = 6,
    BROWN_WHITE = 7,
    BROWN = 8
};


class DeviceConfig {

public:
    DeviceConfig(uint16_t _id, DeviceType _type, uint8_t _portNumber, WireColor _wire);
    ~DeviceConfig();

    const uint8_t getId();
    const DeviceType getDeviceType();    
    const uint8_t getPortNumber();
    const WireColor getWireColor();

private:
    const uint16_t id;
    const DeviceType type;
    const uint8_t portNumber;
    const WireColor wire;
};