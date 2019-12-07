#pragma once

#include <stdint.h>

/* ERRORS: */
#define PJON_CONNECTION_LOST     101
#define PJON_PACKETS_BUFFER_FULL 102
#define PJON_CONTENT_TOO_LONG    104
#define PJON_PACKET_MAX_LENGTH   70
#define PJON_MAX_PACKETS         5

struct PJON_Packet_Info {
  uint8_t header;
  uint16_t id;
  uint8_t receiver_id;
  uint8_t receiver_bus_id[4];
  uint8_t sender_id;
  uint8_t sender_bus_id[4];
  uint16_t port;
  void *custom_pointer;
};

typedef void (* PJON_Error)(
  uint8_t code,
  uint16_t data,
  void *custom_pointer
);

typedef void (* PJON_Receiver)(
  uint8_t *payload,
  uint16_t length,
  const PJON_Packet_Info &packet_info
);

struct PJON_Packet {
  uint8_t  attempts;
  uint8_t  content[PJON_PACKET_MAX_LENGTH];
  uint16_t length;
  uint32_t registration;
  uint16_t state;
  uint32_t timing;
};


class SoftwareBitBang {
public:
    void set_pin(uint8_t);
};

template<typename Strategy>
class PJON {
public:
    Strategy strategy;
    void begin();
    uint16_t update();
    uint16_t receive(uint32_t duration);
    void set_custom_pointer(void *pointer);
    void set_error(PJON_Error e);
    void set_receiver(PJON_Receiver r);
    PJON_Packet packets[PJON_MAX_PACKETS];
};