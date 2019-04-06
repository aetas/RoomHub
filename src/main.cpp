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
#include "device/DevicesRegistry.hpp"

#include "device/DigitalOutputDevice.hpp"
#include "device/DigitalInputDevice.hpp"

#include "mqtt/MqttClient.hpp"
#include "mqtt/MqttEventPublisher.hpp"
#include "mqtt/MqttCommandReceiver.hpp"

#include <WiFi.h>

DigitalInputDevice* switchButton;
DigitalOutputDevice* relay;
DigitalInputDevice* motionSensor;

uint32_t lastChangeTime = 0;
uint8_t relayLastState = LOW;

DevicesRegistry devicesRegistry(NUMBER_OF_DEVICES);

MqttClient mqttClient;

// DONE test output device (relay)
// DONE test input device (switchbutton)
// DONE test input device (movement sensor)
// DONE Prepare logging and get rid of Serial.print
// DONE Implement DeviceRegistry
// TODO Implement MqttEventPublisher (real implementation)
// TODO prepare logs on web page

// Logging
#ifdef LOG_ENABLE_WEB
  BufferedLogger bufferedLogger(LOG_BUFFERED_LOGGER_BUFFER_SIZE);
  Print* logTargets[2] = {&bufferedLogger, &Serial};
  MultiLogger multiLogger(logTargets, 2);
#endif

// WiFi
#ifdef USE_WIFI
void wifiSetup() {
  Log.notice(F("Connecting to WiFi..." CR));
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Log.notice(F("Connected to WiFi on IP %s" CR), WiFi.localIP());
}
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

  for(int i = 0; i < NUMBER_OF_DEVICES; i++) {
    devicesRegistry.add(deviceFactory.create(devicesConfig[i]));
  }

  #ifdef USE_WIFI
  wifiSetup();
  WiFiClient net;
  #endif
  
  // TODO maj: prepare MQTTClient with my MqttClient
  mqttClient.begin(MQTT_HOST, MQTT_PORT, net);

  // TODO maj: HomieDevice and/or HomieNodesFactory
  // TODO maj: initialize MqttCommandReceiver and pass "messageReceived" to MQTTClient
  UpdateListener& mqttEventPublisher = MqttEventPublisher::getInstance();
  devicesRegistry.setUpdateListener(&mqttEventPublisher);
  MqttCommandReceiver& mqttCommandReceiver = MqttCommandReceiver::getInstance(&devicesRegistry, );
}

void loop() {
  uint32_t now = millis();
  devicesRegistry.loop(now);
}


HomieDevice* createHomieDevice() {
  HomieDevice* homieDevice = new HomieDevice(DEVICE_NAME, )
}