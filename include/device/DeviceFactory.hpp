#pragma once
#include "pin/PinProvider.hpp"
#include "Device.hpp"
#include "config/device/DeviceConfig.hpp"

class DeviceFactory {

public:
    static DeviceFactory& getInstance(PinProvider& _pinProvider);
    
    DeviceFactory(DeviceFactory const&) = delete;
    void operator=(DeviceFactory const&) = delete;

    Device* create(DeviceConfig& deviceConfig);

private:
    DeviceFactory(PinProvider& _pinProvider): pinProvider(_pinProvider) {};
    PinProvider& pinProvider;
};