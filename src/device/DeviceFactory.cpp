#include "device/DeviceFactory.hpp"
#include "device/DigitalInputDevice.hpp"
#include "device/DigitalOutputDevice.hpp"
#include "device/AnalogInputDevice.hpp"
#include "device/Dht22Device.hpp"


DeviceFactory& DeviceFactory::getInstance(PinProvider& _pinProvider) {
    static DeviceFactory instance(_pinProvider);
    return instance;
}

Device* DeviceFactory::create(DeviceConfig& deviceConfig) {
    switch (deviceConfig.getDeviceType()) {
        case DeviceType::DIGITAL_INPUT: 
        {
            DigitalPin* digitalPin = pinProvider.digitalPin(deviceConfig.getPortNumber(), deviceConfig.getWireColor());
            return new DigitalInputDevice(deviceConfig.getId(), digitalPin, deviceConfig.getDebounceMs());   
        }
        case DeviceType::DIGITAL_OUTPUT:
        {
            DigitalPin* digitalPin = pinProvider.digitalPin(deviceConfig.getPortNumber(), deviceConfig.getWireColor());
            return new DigitalOutputDevice(deviceConfig.getId(), digitalPin);   
        }
        case DeviceType::ANALOG_INPUT:
        {
            AnalogPin* analogPin = pinProvider.analogPin(deviceConfig.getPortNumber());
            return new AnalogInputDevice(deviceConfig.getId(), analogPin);   
        }
        case DeviceType::DHT22:
        {
            DigitalPin* digitalPin = pinProvider.digitalPin(deviceConfig.getPortNumber(), deviceConfig.getWireColor());
            return new Dht22Device(deviceConfig.getId(), digitalPin);   
        }
    }
    

}