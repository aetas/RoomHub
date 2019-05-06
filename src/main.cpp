#include <Arduino.h>
#include "config/FixedDeviceConfig.hpp"
#include "config/FixedComponentsConfig.hpp"
#include "config/UserConfig.hpp"
#include "config/SpiffsConfigurationStorage.hpp"


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

#include "homie/HomieDeviceFactory.hpp"

#ifdef USE_WIFI
#include <WiFi.h>
#include "wifi/WiFi.h"
#endif

#ifdef USE_WIFI
WiFiClient net;
#endif

DigitalInputDevice* switchButton;
DigitalOutputDevice* relay;
DigitalInputDevice* motionSensor;

uint32_t lastChangeTime = 0;
uint8_t relayLastState = LOW;

DevicesRegistry* devicesRegistry;
HomieDevice* homieDevice;

MqttClient mqttClient;


// DONE test output device (relay)
// DONE test input device (switchbutton)
// DONE test input device (movement sensor)
// DONE Prepare logging and get rid of Serial.print
// DONE Implement DeviceRegistry
// DONE Implement MqttEventPublisher (real implementation)
// TODO maj: review code and push to repo
// TODO maj: quick and dirty test for ConfigurationWebServer
// TODO maj: proper implementation for ConfigurationWebServer
// TODO maj: call reset wifi config on button pressed for 5 seconds
// TODO maj: prepare logs on web page
// TODO maj: send stats with memory used and program space used
// TODO maj: comment out all trace logs

// Logging
#ifdef LOG_ENABLE_WEB
  BufferedLogger bufferedLogger(LOG_BUFFERED_LOGGER_BUFFER_SIZE);
  Print* logTargets[2] = {&bufferedLogger, &Serial};
  MultiLogger multiLogger(logTargets, 2);
#endif

void messageReceivedTest(String &topic, String &payload) {
  Log.notice(F("MQTT message received: %s <- %s" CR), topic, payload);
}

void setup() {
  Serial.begin(115200);

  #ifdef LOG_ENABLE_WEB
    Log.begin(LOG_LEVEL, &multiLogger, false);
  #else
    Log.begin(LOG_LEVEL, &Serial, false);
  #endif

  Log.trace(F("Total heap = %i" CR), ESP.getHeapSize());
  Log.trace(F("Free heap = %i" CR), ESP.getFreeHeap());
  
  #ifdef USE_WIFI
  connectWiFi();
  #endif

  // Reading configuration 
  prepareDevicesConfigs(); // TODO maj: temporary for testing - replace it with ConfigurationWebServer
  SpiffsConfigurationStorage config;
  const char* hubName = config.readName();
  Log.trace(F("hubName = %s" CR), hubName);
  const char* mqttHostname = config.readMqttHostname();
  Log.trace(F("MqttHostname = %s" CR), mqttHostname);
  DeviceConfig** devicesConfig = config.readDevicesConfig();
  uint8_t devicesCount = config.numberOfDevices();
  Log.notice(F("Devices (%i) configuration read from memory" CR), devicesCount);
  

  Log.trace(F("Total heap = %i" CR), ESP.getHeapSize());
  Log.trace(F("Free heap = %i" CR), ESP.getFreeHeap());

  setupComponents();
  Log.notice(F("Components set up" CR));
  
  ExpanderPinProvider& pinProvider = ExpanderPinProvider::getInstance(expanders, &mux, MUX_COMMON_PIN);
  Log.notice(F("PinProvider prepared" CR));
  DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);
  Log.notice(F("DeviceFactory prepared" CR));

  devicesRegistry = new DevicesRegistry(devicesCount);
  for(int i = 0; i < devicesCount; i++) {
    devicesRegistry->add(deviceFactory.create(*devicesConfig[i]));
  }

  mqttClient.begin(mqttHostname, MQTT_PORT, net);

  char* ipValue = new char[16];
  WiFi.localIP().toString().toCharArray(ipValue, 16);
  char* macValue = new char[18];
  WiFi.macAddress().toCharArray(macValue, 18);
  WiFi.RSSI();
  homieDevice = HomieDeviceFactory::create(ipValue, macValue, hubName, devicesConfig, devicesCount, mqttClient);
  
  homieDevice->setup();

  UpdateListener& mqttEventPublisher = MqttEventPublisher::getInstance(homieDevice);
  devicesRegistry->setUpdateListener(&mqttEventPublisher);
  MqttCommandReceiver::getInstance(devicesRegistry, homieDevice);
  mqttClient.onMessage(MqttCommandReceiver::messageReceived);
  Log.trace(F("Total heap = %i" CR), ESP.getHeapSize());
  Log.trace(F("Free heap = %i" CR), ESP.getFreeHeap());
}

void loop() {
  uint32_t now = millis();
  devicesRegistry->loop(now);
  homieDevice->loop(now);

  wifiConnectionCheck(now);

}