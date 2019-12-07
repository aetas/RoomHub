#pragma once
#include <stdint.h>

class PjonListener {
public:
  virtual void messageReceived(uint8_t deviceId, char* message, const uint32_t& now) = 0;
};