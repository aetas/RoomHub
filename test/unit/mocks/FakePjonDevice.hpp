#pragma once

#include "device/pjon/PjonDevice.hpp"
#include <vector>
#include "WString.h"

using namespace std;

class FakePjonDevice: public PjonDevice {
public:
    FakePjonDevice(const uint16_t _id, const DeviceType _type, const uint8_t _pjonId): PjonDevice(_id, _type, _pjonId) {};
    void messageReceived(PjonMessage& pjonMessage) { 
        String type(pjonMessage.getType());
        String value(pjonMessage.getValues()[0]);
        lastMessageType = type;
        lastMessageValues.push_back(value);
        
    };
    using PjonDevice::messageReceived;
    String getLastReceivedMessageType() { return lastMessageType; };
    vector<String> getLastReceivedMessageValues() { return lastMessageValues; };

private:
    String lastMessageType = "EMPTY";
    vector<String> lastMessageValues;
};