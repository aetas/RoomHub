#include "device/pin/ExpanderPinProvider.hpp"

ExpanderPinProvider::ExpanderPinProvider() {

}

ExpanderPinProvider& ExpanderPinProvider::getInstance() {
    static ExpanderPinProvider instance;
    return instance;
}

DigitalPin* ExpanderPinProvider::digitalPin(const uint8_t portNumber, const WireColor& wireColor) {
    uint8_t expanderAddress;
    uint8_t expanderPinNumber;
    
    // 
    // 
    // 
    // 
    // 

}