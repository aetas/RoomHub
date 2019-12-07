#pragma once

#include <stdint.h>
#include "PjonDevice.hpp"
#include "PjonListener.hpp"

class PjonRegistry: public PjonListener {
public:
  PjonRegistry(uint8_t maxNumberOfDevices);
  void addDevice(PjonDevice* pjonDevice);
  void messageReceived(uint8_t pjonDeviceId, char* message, const uint32_t& now);

private:
  PjonDevice** devices;
  uint8_t currentNumberOfDevices = 0;
};