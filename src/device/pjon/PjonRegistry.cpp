#include "device/pjon/PjonRegistry.hpp"

PjonRegistry::PjonRegistry(uint8_t maxNumberOfDevices) {
  devices = new PjonDevice *[maxNumberOfDevices];
}

void PjonRegistry::addDevice(PjonDevice *pjonDevice) {
  devices[currentNumberOfDevices++] = pjonDevice;
}

void PjonRegistry::messageReceived(uint8_t pjonDeviceId, char *message, const uint32_t& now) {
  for(uint8_t i = 0; i < currentNumberOfDevices; i++) {
        if (devices[i]->getPjonId() == pjonDeviceId) {
            devices[i]->messageReceived(message, now);
            return;
        }
    }
}