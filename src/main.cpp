#include <Arduino.h>
#include "config/FixedDeviceConfig.hpp"
#include "config/FixedComponentsConfig.hpp"
#include "device/DeviceFactory.hpp"
#include "device/pin/ExpanderPinProvider.hpp"

#include "device/DigitalOutputDevice.hpp"
#include "device/DigitalInputDevice.hpp"

DigitalInputDevice* switchButton;
DigitalOutputDevice* relay;

uint32_t lastChangeTime = 0;
uint8_t relayLastState = LOW;

// TODO test input device (switchbutton)
// TODO test input device (movement sensor)
// TODO Prepare logging and get rid of Serial.print
// TODO Implement DeviceRegistry
// TODO Implement MqttEventPublisher

void setup() {
  Serial.begin(115200);
  setupComponents();
  Serial.println("Components set up");
  
  ExpanderPinProvider& pinProvider = ExpanderPinProvider::getInstance(expanders, &mux);
  Serial.println("PinProvider prepared");
  DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);
  Serial.println("DeviceFactory prepared");


  Device* devices[4];
  
  for(int i = 0; i < 4; i++) {
    devices[i] = deviceFactory.create(devicesConfig[i]);
  }

  switchButton = ((DigitalInputDevice*) devices[0]);
  relay = ((DigitalOutputDevice*) devices[3]);  
}

void loop() {

  uint32_t now = millis();
  
  switchButton->loop(now);

  if (lastChangeTime + 3000 < now) {


    uint8_t value = expanders[3].digitalRead(1);
    if (value == HIGH) {
      Serial.println("HIGH");
    } else {
      Serial.println("LOW");
    }


    // if (relayLastState == HIGH) {
    //   relay->setState(LOW);
    //   relayLastState = LOW;
    //   Serial.println("LOW");
    // } else {
    //   relay->setState(HIGH);
    //   relayLastState = HIGH;
    //   Serial.println("HIGH");
    // }
    lastChangeTime = now;
  }
}
