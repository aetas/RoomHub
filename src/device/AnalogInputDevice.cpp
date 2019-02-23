#include "device/AnalogInputDevice.hpp"

AnalogInputDevice::~AnalogInputDevice() {
    delete analogPin;
}