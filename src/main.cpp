#include <Arduino.h>
#include "config/FixedComponentsConfig.hpp"
#include "config/MasterConfig.hpp"
#include "config/SpiffsConfigurationStorage.hpp"
#include "config/ConfigurationWebServer.hpp"
#include "config/Configuration.hpp"


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

#include "buttons/buttons.hpp"

#ifdef USE_WIFI
WiFiClient net;
#endif

DevicesRegistry* devicesRegistry;
HomieDevice* homieDevice;

MqttClient mqttClient;


// DONE test output device (relay)
// DONE test input device (switchbutton)
// DONE test input device (movement sensor)
// DONE Prepare logging and get rid of Serial.print
// DONE Implement DeviceRegistry
// DONE Implement MqttEventPublisher (real implementation)
// DONE review code and push to repo
// DONE quick and dirty test for ConfigurationWebServer
// DONE proper implementation for ConfigurationWebServer
// DONE: call reset wifi config on button pressed for 5 seconds
// TODO maj: prepare logs on web page
// TODO maj: send stats with memory used and program space used
// TODO maj: comment out all trace and verbose logs

// Logging
#ifdef LOG_ENABLE_WEB
  BufferedLogger bufferedLogger(LOG_BUFFERED_LOGGER_BUFFER_SIZE);
  Print* logTargets[2] = {&bufferedLogger, &Serial};
  MultiLogger multiLogger(logTargets, 2);
#endif

void checkForResetButtonsPressed() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(EXTRA_BUTTON_CONFIG_RESET_PIN, INPUT_PULLUP);
  pinMode(EXTRA_BUTTON_WIFI_RESET_PIN, INPUT_PULLUP);
  if (hasTimedButtonBeenTriggered(EXTRA_BUTTON_CONFIG_RESET_PIN, EXTRA_BUTTON_CONFIG_RESET_TIME_TO_RESET_MS)) {
    Log.warning(F("Reset button pressed - device configuration will be removed..."));
    ledBlink(500, 3);
    SpiffsConfigurationStorage config;
    config.resetConfig();
    ESP.restart();
  }
  if (hasTimedButtonBeenTriggered(EXTRA_BUTTON_WIFI_RESET_PIN, EXTRA_BUTTON_WIFI_RESET_TIME_TO_RESET_MS)) {
    Log.warning(F("Reset button pressed - wifi configuration will be removed..."));
    ledBlink(300, 5);
    resetWiFiConfiguration();
    ESP.restart();
  }
}

void setup() {
  Serial.begin(115200);

  #ifdef LOG_ENABLE_WEB
    Log.begin(LOG_LEVEL, &multiLogger, false);
  #else
    Log.begin(LOG_LEVEL, &Serial, false);
  #endif
  
  #ifdef USE_WIFI
  connectWiFi();
  #endif
  
  checkForResetButtonsPressed();

  // Reading configuration
  Configuration config;
  SpiffsConfigurationStorage* storage = new SpiffsConfigurationStorage();
  ConfigurationWebServer webServer(*storage);
  config.loadConfiguration(*storage, webServer);

  setupComponents();
  Log.notice(F("Components set up" CR));
  
  ExpanderPinProvider& pinProvider = ExpanderPinProvider::getInstance(expanders, &mux, MUX_COMMON_PIN);
  Log.trace(F("PinProvider prepared" CR));
  DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);
  Log.trace(F("DeviceFactory prepared" CR));

  DeviceConfig** devicesConfig = config.getDevicesConfig();
  uint8_t numberOfDevices = config.getNumberOfDevices();
  devicesRegistry = new DevicesRegistry(config.getNumberOfDevices());
  for(int i = 0; i < numberOfDevices; i++) {
    devicesRegistry->add(deviceFactory.create(*devicesConfig[i]));
  }

  mqttClient.begin(config.getMqttHostname(), MQTT_PORT, net);

  char* ipValue = new char[16];
  WiFi.localIP().toString().toCharArray(ipValue, 16);
  char* macValue = new char[18];
  WiFi.macAddress().toCharArray(macValue, 18);
  WiFi.RSSI();
  homieDevice = HomieDeviceFactory::create(ipValue, macValue, config.getRoomHubName(), devicesConfig, numberOfDevices, mqttClient);
  
  homieDevice->setup();

  UpdateListener& mqttEventPublisher = MqttEventPublisher::getInstance(homieDevice);
  devicesRegistry->setUpdateListener(&mqttEventPublisher);
  MqttCommandReceiver::getInstance(devicesRegistry, homieDevice);
  mqttClient.onMessage(MqttCommandReceiver::messageReceived);

  delete storage;
  Log.trace(F("Total heap = %i" CR), ESP.getHeapSize());
  Log.trace(F("Free heap = %i" CR), ESP.getFreeHeap());
}

void loop() {
  uint32_t now = millis();
  devicesRegistry->loop(now);
  homieDevice->loop(now);

  wifiConnectionCheck(now);

}