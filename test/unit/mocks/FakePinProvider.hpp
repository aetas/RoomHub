#include "device/pin/PinProvider.hpp"
#include "FakeDigitalPin.hpp"
#include "FakeAnalogPin.hpp"

class FakePinProvider: public PinProvider {

public:
    static FakePinProvider& getInstance() {
       static FakePinProvider instance;
        return instance;
    };
    
    FakePinProvider(FakePinProvider const&) = delete;
    void operator=(FakePinProvider const&) = delete;

    DigitalPin* digitalPin(const uint8_t portNumber, const WireColor& wireColor) {
        return new FakeDigitalPin();
    };
    
    AnalogPin* analogPin(const uint8_t portNumber) {
        return new FakeAnalogPin();
    };

private:
    FakePinProvider() {};
};