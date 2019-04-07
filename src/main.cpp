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

#include "homie/HomieDeviceFactory.hpp"

#include <WiFi.h>

#ifdef USE_WIFI
WiFiClient net;
#endif

DigitalInputDevice* switchButton;
DigitalOutputDevice* relay;
DigitalInputDevice* motionSensor;

uint32_t lastChangeTime = 0;
uint8_t relayLastState = LOW;

DevicesRegistry devicesRegistry(NUMBER_OF_DEVICES);
HomieDevice* homieDevice;

MqttClient mqttClient;


// DONE test output device (relay)
// DONE test input device (switchbutton)
// DONE test input device (movement sensor)
// DONE Prepare logging and get rid of Serial.print
// DONE Implement DeviceRegistry
// DONE Implement MqttEventPublisher (real implementation)
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
  uint8_t status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Log.trace(F("Trying to connect to WiFi (%d)..." CR), status);
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);
    delay(WIFI_CONNECT_WAIT_MS);
  }
  Log.notice(F("Connected to WiFi on IP %s" CR), WiFi.localIP().toString().c_str());
}

void wifiConnectionCheck(long now) {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
}
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
  #endif
  
  mqttClient.begin(MQTT_HOST, MQTT_PORT, net);

  char* ipValue = new char[16];
  WiFi.localIP().toString().toCharArray(ipValue, 16);
  char* macValue = new char[18];
  WiFi.macAddress().toCharArray(macValue, 18);
  WiFi.RSSI();
  homieDevice = HomieDeviceFactory::create(ipValue, macValue, devicesConfig, NUMBER_OF_DEVICES, mqttClient);
  
  homieDevice->setup();

  UpdateListener& mqttEventPublisher = MqttEventPublisher::getInstance(homieDevice);
  devicesRegistry.setUpdateListener(&mqttEventPublisher);
  MqttCommandReceiver::getInstance(&devicesRegistry, homieDevice);
  mqttClient.onMessage(MqttCommandReceiver::messageReceived);
}

void loop() {
  uint32_t now = millis();
  devicesRegistry.loop(now);
  homieDevice->loop(now);

  wifiConnectionCheck(now);

  // TODO maj: send stats with memory used and program space used
}