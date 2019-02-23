#include "device/pin/PinProvider.hpp"

PinProvider::PinProvider() {
    
}

PinProvider& PinProvider::getInstance() {
    static PinProvider instance;
    return instance;
}