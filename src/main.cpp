#include <Arduino.h>
#include "config/FixedDeviceConfig.hpp"
#include "config/FixedComponentsConfig.hpp"
#include "device/DeviceFactory.hpp"
#include "device/pin/ExpanderPinProvider.hpp"

#include "device/DigitalOutputDevice.hpp"
#include "device/DigitalInputDevice.hpp"

#include "mqtt/MqttEventPublisher.hpp"

DigitalInputDevice* switchButton;
DigitalOutputDevice* relay;
DigitalInputDevice* motionSensor;

uint32_t lastChangeTime = 0;
uint8_t relayLastState = LOW;

UpdateListener& mqttEventPublisher = MqttEventPublisher::getInstance();

// DONE test output device (relay)
// DONE test input device (switchbutton)
// DONE test input device (movement sensor)
// TODO Prepare logging and get rid of Serial.print
// TODO Implement DeviceRegistry
// TODO Implement MqttEventPublisher (real implementation)

void setup() {
  Serial.begin(115200);
  setupComponents();
  Serial.println("Components set up");
  
  ExpanderPinProvider& pinProvider = ExpanderPinProvider::getInstance(expanders, &mux);
  Serial.println("PinProvider prepared");
  DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);
  Serial.println("DeviceFactory prepared");


  Device* devices[5];
  
  for(int i = 0; i < 5; i++) {
    devices[i] = deviceFactory.create(devicesConfig[i]);
  }

  switchButton = ((DigitalInputDevice*) devices[0]);
  relay = ((DigitalOutputDevice*) devices[3]);  
  motionSensor = ((DigitalInputDevice*) devices[4]);

  switchButton->setUpdateListener(&mqttEventPublisher);
  motionSensor->setUpdateListener(&mqttEventPublisher);
}

void loop() {

  uint32_t now = millis();
  
  switchButton->loop(now);
  motionSensor->loop(now);
}
