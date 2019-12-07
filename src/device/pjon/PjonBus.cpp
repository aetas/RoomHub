#include "device/pjon/PjonBus.hpp"
#include <ArduinoLog.h>
#include <Arduino.h>

PjonBus::PjonBus(PJON<SoftwareBitBang>& _pjon, PjonListener& _pjonListener): pjon(_pjon), pjonListener(_pjonListener) {
}

void PjonBus::begin(uint8_t pjonPin) {
  pjon.set_custom_pointer(this);
  pjon.set_error(handleErrorForwarder);
  pjon.set_receiver(receiverFunctionForwarder);
  pjon.strategy.set_pin(pjonPin);
  pjon.begin();
}
 
void PjonBus::loop(const uint32_t& now) {
  pjon.receive(50000);
  pjon.update();
}

void PjonBus::handleErrorForwarder(uint8_t code, uint16_t data, void* custom_pointer) {
  static_cast<PjonBus*>(custom_pointer)->handleError(code, data);
}

void PjonBus::handleError(uint8_t code, uint16_t data) {
  if(code == PJON_CONNECTION_LOST) {
    Log.error(F("Connection with device ID %d is lost" CR), pjon.packets[data].content[0]);
  }
  if(code == PJON_PACKETS_BUFFER_FULL) {
    Log.error(F("Packet buffer is full, has now a length of %d" CR), data);
    Log.error(F("Possible wrong bus configuration! Higher PJON_MAX_PACKETS if necessary." CR));
  }
  if(code == PJON_CONTENT_TOO_LONG) {
    Log.error(F("Content is too long, length: %d" CR), data);
  }
}

void PjonBus::receiverFunctionForwarder(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  static_cast<PjonBus*>(packet_info.custom_pointer)->receiverFunction(payload, length, packet_info);
}

void PjonBus::receiverFunction(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  // Log.trace(F("New PJON message received: " CR));
  char* message = new char[length];
  strcpy(message, (char*) payload);
  pjonListener.messageReceived(packet_info.sender_id, message, millis());
  // Log.trace("from: %i | message: %s" CR, packet_info.sender_id, message);
  
  delete[] message;
};