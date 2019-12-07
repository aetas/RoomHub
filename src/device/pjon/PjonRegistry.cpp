#include "device/pjon/PjonRegistry.hpp"

PjonRegistry::PjonRegistry(uint8_t maxNumberOfDevices) {
  devices = new PjonDevice *[maxNumberOfDevices];
}

void PjonRegistry::addDevice(PjonDevice *pjonDevice) {
  // Log.trace(F("PJON device registered (pjonId=%i | id=%i)" CR), pjonDevice->getPjonId(), pjonDevice->getId());
  devices[currentNumberOfDevices++] = pjonDevice;
}

void PjonRegistry::messageReceived(uint8_t pjonDeviceId, char *message, const uint32_t& now) {
  for(uint8_t i = 0; i < currentNumberOfDevices; i++) {
    if (devices[i]->getPjonId() == pjonDeviceId) {
      // Log.trace(F("PJON message received to known device %i" CR), pjonDeviceId);
      devices[i]->messageReceived(message, now);
      return;
    }
  }
}