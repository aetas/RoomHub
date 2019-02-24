#include <Arduino.h>
#include "config/FixedDeviceConfig.hpp"
#include "config/FixedComponentsConfig.hpp"
#include "device/DeviceFactory.hpp"
#include "device/pin/ExpanderPinProvider.hpp"

#include "device/DigitalOutputDevice.hpp"
#include "device/DigitalInputDevice.hpp"

DigitalInputDevice* switchButton;
DigitalOutputDevice* relay;

uint16_t lastChangeTime = 0;
uint8_t relayLastState = LOW;

void setup() {
  Serial.begin(115200);
  
  ExpanderPinProvider& pinProvider = ExpanderPinProvider::getInstance(expanders[0], mux);
  DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);

  Device* devices[4];
  
  for(int i = 0; i < 4; i++) {
    devices[i] = deviceFactory.create(devicesConfig[i]);
  }

  switchButton = ((DigitalInputDevice*) devices[0]);
  relay = ((DigitalOutputDevice*) devices[3]);
  
}

void loop() {
  uint32_t now = millis();
  if (lastChangeTime + 3000 < now) {
    if (relayLastState == HIGH) {
      relay->setState(LOW);
    } else {
      relay->setState(HIGH);
    }
    lastChangeTime = now;
  }
}