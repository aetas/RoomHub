#pragma once

#include "device/Device.hpp"
#include "device/pjon/PjonMessage.hpp"

#define PJON_MAX_MESSAGES_INTERVAL_MS   60000  // if more than 60 seconds between messages - PJON device is considered lost
#define PJON_UPTIME_NOTIFICATION_INTERVAL_MS   60000  // every 60 seconds notify about current uptime

/**
 * This class is base class for all Pjon-based devices
 * In most cases extending #messageReceived(PjonMessage pjonMessage) method should be enough.
 * You can extend #messageReceived(char* message, uint32_t now) if you need more control over message parsing, 
 * but you need to implement handling PING message for uptime yourself.
 * 
 * Remember to call PjonDevice::loop(uint32_t now) in the beginning of your implementation of loop method.
 */
class PjonDevice: public Device {
public:
  PjonDevice(const uint16_t _id, const DeviceType _type, const uint8_t _pjonId);
  uint8_t getPjonId();
  void messageReceived(const char* message, const uint32_t& now);
  virtual void messageReceived(PjonMessage& pjonMessage) = 0;
  virtual void loop(const uint32_t& currentTimeMs);
  static const char* MESSAGE_TYPE_PING;
  static const char* PROPERTY_STATE;
  static const char* PROPERTY_UPTIME;
  static const char* STATE_STARTING;
  static const char* STATE_READY;
  static const char* STATE_LOST;

protected: 
  void handlePing(const uint32_t& now, uint32_t uptime);
  void healthcheck(const uint32_t& now);
  uint32_t getUptime();

private:
  uint8_t pjonId;
  uint32_t lastMessageTime = 0;
  uint32_t lastTimeUptimeNotified = 0;
  uint32_t pjonDeviceUptime = 0;
  const char* currentState = STATE_STARTING;
};