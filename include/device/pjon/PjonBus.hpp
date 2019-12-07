#pragma once

#include <stdint.h>
#define PJON_PACKET_MAX_LENGTH 70
#define PJON_INCLUDE_SWBB
#include <PJON.h>
#include "device/pjon/PjonMessage.hpp"
#include "device/pjon/PjonListener.hpp"

class PjonBus {

public:
    PjonBus(PJON<SoftwareBitBang>& _pjon, PjonListener& _pjonListener);

    void begin(uint8_t pjonPin);
    void loop(const uint32_t& now);
    void send(PjonMessage &message, const uint8_t &receiverId);
    
private:
  static void handleErrorForwarder(uint8_t code, uint16_t data, void* custom_pointer);
  void handleError(uint8_t code, uint16_t data);
  static void receiverFunctionForwarder(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info);
  void receiverFunction(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info);

  PJON<SoftwareBitBang>& pjon;
  PjonListener& pjonListener;
};