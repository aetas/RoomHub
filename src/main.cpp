#include <Arduino.h>
#include "config/FixedDeviceConfig.hpp"
#include "config/FixedComponentsConfig.hpp"
#include "config/UserConfig.hpp"


// Logging
#include "ArduinoLog.h"
#include "log/MultiLogger.hpp"
#include "log/BufferedLogger.hpp"

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
// DONE Prepare logging and get rid of Serial.print
// TODO Implement DeviceRegistry
// TODO Implement MqttEventPublisher (real implementation)
// TODO prepare logs on web page

// Logging
#ifdef LOG_ENABLE_WEB
  BufferedLogger bufferedLogger(LOG_BUFFERED_LOGGER_BUFFER_SIZE);
  Print* logTargets[2] = {&bufferedLogger, &Serial};
  MultiLogger multiLogger(logTargets, 2);
#endif

void setup() {
  Serial.begin(115200);

 #ifdef LOG_ENABLE_WEB
    Log.begin(LOG_LEVEL, &multiLogger, false);
  #else
    Log.begin(LOG_LEVEL, &Serial, false);
  #endif

  setupComponents();
  Log.notice(F("Components set up" CR));
  
  ExpanderPinProvider& pinProvider = ExpanderPinProvider::getInstance(expanders, &mux);
  Log.notice(F("PinProvider prepared" CR));
  DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);
  Log.notice(F("DeviceFactory prepared" CR));


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
