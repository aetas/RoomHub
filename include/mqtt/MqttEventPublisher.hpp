#pragma once

#include "../device/UpdateListener.hpp"
#include "../homie/HomieDevice.hpp"

class MqttEventPublisher: public UpdateListener {

public:
    static MqttEventPublisher& getInstance(HomieDevice* homieDevice);
    
    MqttEventPublisher(MqttEventPublisher const&) = delete;
    void operator=(MqttEventPublisher const&) = delete;

    void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint8_t newValue);
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint16_t newValue);
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const char* newValue);

private:
    MqttEventPublisher(HomieDevice* _homieDevice);
    HomieDevice* homieDevice;
};