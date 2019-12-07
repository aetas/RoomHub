#include "device/pjon/PjonDevice.hpp"
#include <WString.h>
#include <stdlib.h>

const char* PjonDevice::MESSAGE_TYPE_PING = "PING";
const char* PjonDevice::PROPERTY_STATE = "state";
const char* PjonDevice::PROPERTY_UPTIME = "uptime";
const char* PjonDevice::STATE_STARTING = "starting";
const char* PjonDevice::STATE_READY = "ready";
const char* PjonDevice::STATE_LOST = "lost";

PjonDevice::PjonDevice(const uint16_t _id, const DeviceType _type, const uint8_t _pjonId)
    : Device(_id, _type), pjonId(_pjonId) {}

uint8_t PjonDevice::getPjonId() {
    return pjonId;
}

void PjonDevice::messageReceived(const char* message, const uint32_t& now) {
    PjonMessage pjonMessage = PjonMessage::fromString(message);
    if (strcmp(pjonMessage.getType(), MESSAGE_TYPE_PING) == 0) {
        const char* uptimeString = pjonMessage.getValues()[0];
        uint32_t uptime = atoi(uptimeString);
        handlePing(now, uptime);
    } else {
        this->messageReceived(pjonMessage);
    }
    lastMessageTime = now;
    if (strcmp(currentState, STATE_STARTING) == 0 || strcmp(currentState, STATE_LOST) == 0) {
        currentState = STATE_READY;
        notify(PROPERTY_STATE, STATE_READY);
    }
}

void PjonDevice::handlePing(const uint32_t& now, uint32_t uptime) {
    pjonDeviceUptime = uptime;
}
 
void PjonDevice::healthcheck(const uint32_t& now) {
    if (now - lastMessageTime > PJON_MAX_MESSAGES_INTERVAL_MS) {
        currentState = STATE_LOST;
        notify(PROPERTY_STATE, STATE_LOST);
    }
}

void PjonDevice::loop(const uint32_t& currentTimeMs) {
    healthcheck(currentTimeMs);
    if (currentTimeMs - lastTimeUptimeNotified > PJON_UPTIME_NOTIFICATION_INTERVAL_MS) {
        lastTimeUptimeNotified = currentTimeMs;
        notify(PROPERTY_UPTIME, pjonDeviceUptime);
    }
}

uint32_t PjonDevice::getUptime() {
    return pjonDeviceUptime;
}