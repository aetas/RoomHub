#include <Arduino.h>
#include "config/FixedComponentsConfig.hpp"
#include "config/MasterConfig.hpp"
#include "config/SpiffsConfigurationStorage.hpp"
#include "config/ConfigurationWebServer.hpp"
#include "config/Configuration.hpp"


// Logging
#include "ArduinoLog.h"

#ifdef LOG_MQTT_ENABLED
#include "log/MultiLogger.hpp"
#include "log/BufferedLogger.hpp"
#include "mqtt/MqttLogger.hpp"
#endif

#include "device/DeviceFactory.hpp"
#include "device/pin/ExpanderPinProvider.hpp"
#include "device/DevicesRegistry.hpp"

#include "device/DigitalOutputDevice.hpp"
#include "device/DigitalInputDevice.hpp"

#include "mqtt/MqttClient.hpp"
#include "mqtt/MqttEventPublisher.hpp"
#include "mqtt/MqttCommandReceiver.hpp"

#if PJON_ENABLED == true
#include "device/pjon/PjonBus.hpp"
#include "device/pjon/PjonRegistry.hpp"
#endif

#include "stats/EspStatsData.hpp"

#include "homie/HomieDeviceFactory.hpp"

#include "network/NetworkConnection.hpp"

#include "buttons/buttons.hpp"

EspStatsData statsData;

DevicesRegistry* devicesRegistry;
HomieDevice* homieDevice;

MqttClient mqttClient;
#if PJON_ENABLED == true
PJON<SoftwareBitBang> pjon(PJON_DEVICE_ID);
PjonRegistry pjonRegistry(PJON_MAX_NUMBER_OF_DEVICES);
PjonBus pjonBus(pjon, pjonRegistry);
#endif

NetworkConnection networkConnection;

// Logging
#ifdef LOG_MQTT_ENABLED
  BufferedLogger bufferedLogger(LOG_BUFFERED_LOGGER_BUFFER_SIZE);
  Print* logTargets[2] = {&bufferedLogger, &Serial};
  MultiLogger multiLogger(logTargets, 2);
  MqttLogger* mqttLogger;
#endif

void checkForGeneralConfigResetButtonsPressed() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(EXTRA_BUTTON_CONFIG_RESET_PIN, INPUT_PULLUP);
  if (hasTimedButtonBeenTriggered(EXTRA_BUTTON_CONFIG_RESET_PIN, EXTRA_BUTTON_CONFIG_RESET_TIME_TO_RESET_MS)) {
    Log.warning(F("Reset button pressed - device configuration will be removed..."));
    ledBlink(500, 3);
    SpiffsConfigurationStorage config;
    config.resetConfig();
    ESP.restart();
  }
}

void checkForEthernetConfigResetButtonPressed() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(EXTRA_BUTTON_NETWORK_RESET_PIN, INPUT_PULLUP);
  if (hasTimedButtonBeenTriggered(EXTRA_BUTTON_NETWORK_RESET_PIN, EXTRA_BUTTON_NETWORK_RESET_TIME_TO_RESET_MS)) {
    Log.warning(F("Reset button pressed - ethernet configuration will be removed..."));
    ledBlink(300, 5);
    SpiffsConfigurationStorage config;
    config.resetEthernetConfig();
    ESP.restart();
  }
}
#ifdef USE_WIFI
void checkForWifiConfigResetButtonPressed() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(EXTRA_BUTTON_NETWORK_RESET_PIN, INPUT_PULLUP);
  if (hasTimedButtonBeenTriggered(EXTRA_BUTTON_NETWORK_RESET_PIN, EXTRA_BUTTON_NETWORK_RESET_TIME_TO_RESET_MS)) {
    Log.warning(F("Reset button pressed - wifi configuration will be removed..."));
    ledBlink(300, 5);
    networkConnection.resetWiFiConfiguration();
    SpiffsConfigurationStorage config;
    config.resetEthernetConfig();
    ESP.restart();
  }
}
#endif

void setup() {
  Serial.begin(115200);

  #ifdef LOG_MQTT_ENABLED
    Log.begin(LOG_LEVEL, &multiLogger, false);
  #else
    Log.begin(LOG_LEVEL, &Serial, false);
  #endif

  checkForGeneralConfigResetButtonsPressed();
  
  SpiffsConfigurationStorage* storage = new SpiffsConfigurationStorage();

  #ifdef USE_ETHERNET
  checkForEthernetConfigResetButtonPressed();
  networkConnection.setEthernetConfiguration(storage->readEthernetConfiguration());
  #endif

  networkConnection.connect();
  
  #ifdef USE_WIFI
  checkForWifiConfigResetButtonPressed();
  #endif


  // Reading configuration
  Configuration config;
  ConfigurationWebServer webServer(*storage);
  config.loadConfiguration(*storage, webServer);

  #ifdef LOG_MQTT_ENABLED
  String mqttLogsTopicString = HOMIE_PREFIX "/";
  mqttLogsTopicString += config.getRoomHubName();
  mqttLogsTopicString += "/$logs";
  char* mqttLogsTopic = new char[mqttLogsTopicString.length()];
  strcpy(mqttLogsTopic, mqttLogsTopicString.c_str());
  mqttLogger = new MqttLogger(mqttClient, bufferedLogger, mqttLogsTopic);
  #endif

  setupComponents();
  // Log.trace(F("Components set up" CR));
  #if PJON_ENABLED == true
  pjonBus.begin(PJON_PIN);
  // Log.trace(F("PjonBus initialized" CR));
  #endif
  
  ExpanderPinProvider& pinProvider = ExpanderPinProvider::getInstance(expanders, &mux, MUX_COMMON_PIN);
  // Log.trace(F("PinProvider prepared" CR));
  DeviceFactory& deviceFactory = DeviceFactory::getInstance(pinProvider);
  // Log.trace(F("DeviceFactory prepared" CR));

  DeviceConfig** devicesConfig = config.getDevicesConfig();
  uint8_t numberOfDevices = config.getNumberOfDevices();
  devicesRegistry = new DevicesRegistry(config.getNumberOfDevices());
  for(int i = 0; i < numberOfDevices; i++) {
    Device* device = deviceFactory.create(*devicesConfig[i]);
    devicesRegistry->add(device);
    #if PJON_ENABLED == true
    if (devicesConfig[i]->isPjonDevice()) {
      pjonRegistry.addDevice(static_cast<PjonDevice*>(device));
    }
    #endif
  }
 
  mqttClient.begin(config.getMqttHostname(), MQTT_PORT, networkConnection.getClient());

  char* ipAddress = new char[15];
  strcpy(ipAddress, networkConnection.getIpAddress());
  homieDevice = HomieDeviceFactory::create(ipAddress, networkConnection.getMacAddress(), 
                                           config.getRoomHubName(), devicesConfig, numberOfDevices, mqttClient, statsData);
  
  homieDevice->setup();

  UpdateListener& mqttEventPublisher = MqttEventPublisher::getInstance(homieDevice);
  devicesRegistry->setUpdateListener(&mqttEventPublisher);
  MqttCommandReceiver::getInstance(devicesRegistry);
  mqttClient.onMessage(MqttCommandReceiver::messageReceived);

  delete storage;
  #ifdef LOG_MQTT_ENABLED
  mqttLogger->sendLogs();
  #endif
}

void loop() {
  uint32_t now = millis();
  devicesRegistry->loop(now);
  boolean workingCorrectly = homieDevice->loop(now);
  if (!workingCorrectly) {
    Log.error(F("HomieDevice is having MQTT connection problems..."));
  }

  networkConnection.checkConnection(now);

  #ifdef LOG_MQTT_ENABLED
  mqttLogger->loop(now);
  #endif

  #if PJON_ENABLED == true
  pjonBus.loop(now);
  #endif
}