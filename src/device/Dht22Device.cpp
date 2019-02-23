#include "device/Dht22Device.hpp"

Dht22Device::~Dht22Device() {
    delete digitalPin;
}