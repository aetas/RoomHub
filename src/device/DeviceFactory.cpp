#include <ArduinoLog.h>
#include "device/DeviceFactory.hpp"
#include "device/DigitalInputDevice.hpp"
#include "device/DigitalOutputDevice.hpp"
#include "device/AnalogInputDevice.hpp"
#include "device/Dht22Device.hpp"
#include "device/Sct013Device.hpp"
#include "device/EmulatedSwitchDevice.hpp"
#include "device/Bme280Device.hpp"
#include "config/MasterConfig.hpp"


DeviceFactory& DeviceFactory::getInstance(PinProvider& _pinProvider) {
    static DeviceFactory instance(_pinProvider);
    return instance;
}

Device* DeviceFactory::create(DeviceConfig& deviceConfig) {
    switch (deviceConfig.getDeviceType()) {
        case DeviceType::DIGITAL_INPUT: 
        {
            // Log.trace(F("DIGITAL_INPUT device created" CR));
            DigitalPin* digitalPin = pinProvider.digitalPin(deviceConfig.getPortNumber(), deviceConfig.getWireColor());
            return new DigitalInputDevice(deviceConfig.getId(), digitalPin, deviceConfig.getDebounceMs());   
        }
        case DeviceType::DIGITAL_OUTPUT:
        {
            // Log.trace(F("DIGITAL_OUTPUT device created" CR));
            DigitalPin* digitalPin = pinProvider.digitalPin(deviceConfig.getPortNumber(), deviceConfig.getWireColor());
            return new DigitalOutputDevice(deviceConfig.getId(), digitalPin);
        }
        case DeviceType::ANALOG_INPUT:
        {
            // Log.trace(F("ANALOG_INPUT device created" CR));
            AnalogPin* analogPin = pinProvider.analogPin(deviceConfig.getPortNumber());
            return new AnalogInputDevice(deviceConfig.getId(), analogPin);   
        }
        case DeviceType::DHT22:
        {
            // Log.trace(F("DHT22 device created" CR));
            DigitalPin* digitalPin = pinProvider.digitalPin(deviceConfig.getPortNumber(), deviceConfig.getWireColor());
            return new Dht22Device(deviceConfig.getId(), digitalPin);   
        }
        case DeviceType::SCT013:
        {
            // Log.trace(F("SCT013 device created" CR));
            AnalogPin* analogPin = pinProvider.analogPin(deviceConfig.getPortNumber());
            return new Sct013Device(deviceConfig.getId(), analogPin);   
        }
        case DeviceType::EMULATED_SWITCH:
        {
            // Log.trace(F("EMULATED_SWITCH device created" CR));
            DigitalPin* digitalPin = pinProvider.digitalPin(deviceConfig.getPortNumber(), deviceConfig.getWireColor());
            return new EmulatedSwitchDevice(deviceConfig.getId(), digitalPin);
        }

        #if PJON_ENABLED == true
        case DeviceType::BME280: 
        {
            // Log.trace(F("BME280 device created" CR));
            return new Bme280Device(deviceConfig.getId(), deviceConfig.getPjonId());
        }
        #endif
        
        default: {
            Log.error(F("Unknown device type with id: %d. Check PJON_ENABLED." CR), deviceConfig.getId());
            throw;
        }
    }
}