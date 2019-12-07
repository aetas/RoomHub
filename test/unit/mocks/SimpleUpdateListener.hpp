#pragma once

#include "device/UpdateListener.hpp"
#include "WString.h"
#include <map>
#include <iostream>

using namespace std;

class SimpleUpdateListener: public UpdateListener {

public:
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint8_t& newValue) { 
        cout << "SimpleUpdateListener: " << "value updated (smallInt) " << propertyName << " = " << newValue << endl;
        receivedSmallIntValues[propertyName] = newValue;
        smallIntValue = newValue; valueUpdatedCalledTimes++; 
    };
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const uint32_t& newValue) { 
        cout << "SimpleUpdateListener: " << "value updated (bigInt) " << propertyName << " = " << newValue << endl;
        receivedBigIntValues[propertyName] = newValue;
        bigIntValue = newValue; valueUpdatedCalledTimes++; 
    };
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const float& newValue) { 
        cout << "SimpleUpdateListener: " << "value updated (float) " << propertyName << " = " << newValue << endl;
        receivedFloatValues[propertyName] = newValue;
        floatValue = newValue; valueUpdatedCalledTimes++; 
    };
    void valueUpdated(const uint8_t deviceId, const char* propertyName, const char* newValue) { 
        cout << "SimpleUpdateListener: " << "value updated (string) " << propertyName << " = " << newValue << endl;
        receivedStringValues[propertyName] = newValue;
        stringValue = newValue; valueUpdatedCalledTimes++; 
    };

    uint8_t smallIntValue = 1;
    uint32_t bigIntValue = 0;
    uint32_t floatValue = 0;
    const char* stringValue = "";
    uint8_t valueUpdatedCalledTimes = 0;

    map<String, uint32_t> receivedBigIntValues;
    map<String, uint8_t> receivedSmallIntValues;
    map<String, float> receivedFloatValues;
    map<String, String> receivedStringValues;
};