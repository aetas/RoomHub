#include "device/Bme280Device.hpp"
#include <string.h>
#include <stdlib.h>


const char* Bme280Device::MESSAGE_TYPE_VALUES = "VALUES";

Bme280Device::Bme280Device(const uint16_t _id, const uint8_t _pjonId): PjonDevice(_id, DeviceType::BME280, _pjonId) {}

void Bme280Device::messageReceived(PjonMessage& message) {
    
    if (strcmp(message.getType(), MESSAGE_TYPE_VALUES) == 0) {
        const char** values = message.getValues();

        float temperature = atof(values[0]) / 100;
        float humidity = atof(values[1]) / 100;
        uint32_t pressure = atoi(values[2]);

        notify("temperature", temperature);
        notify("humidity", humidity);
        notify("pressure", pressure);
    }
}