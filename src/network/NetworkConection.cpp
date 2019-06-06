#include "network/NetworkConnection.hpp"

#include <Arduino.h>
#include <ArduinoLog.h>

const char* NetworkConnection::getIpAddress() {
  return networkConfiguration.getIpAddress().toString().c_str();
}

const char* NetworkConnection::getMacAddress() {
  return networkConfiguration.getMacAddress();
}


void NetworkConnection::connect() {
  #if defined(USE_WIFI)
  connectWiFi();
  #elif defined(USE_ETHERNET)
  connectEthernet();
  #endif
}

void NetworkConnection::checkConnection(uint32_t now) {
  #if defined(USE_WIFI)
  wifiConnectionCheck(now);
  #elif defined(USE_ETHERNET)
  // TODO maj: ethernet connection check... what to do if there is a problem?? reconnect?
  #endif
}

Client& NetworkConnection::getClient() {
    return ethClient;
}

#ifdef USE_ETHERNET
/*
 * Wiz W5500 reset function
 */
void NetworkConnection::ethernetWizReset(const uint8_t resetPin) {
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
    delay(250);
    digitalWrite(resetPin, LOW);
    delay(50);
    digitalWrite(resetPin, HIGH);
    delay(350);
}

void NetworkConnection::setEthernetConfiguration(EthernetConfiguration _ethConfig) {
    networkConfiguration = _ethConfig;
}

void NetworkConnection::connectEthernet() {
    delay(500);
    
    macCharArrayToBytes(networkConfiguration.getMacAddress(), mac);
    Ethernet.init(ETHERNET_CS_PIN);
    ethernetWizReset(ETHERNET_RESET_PIN);
    Ethernet.begin(mac, 
                   networkConfiguration.getIpAddress(), 
                   networkConfiguration.getDnsAddress(), 
                   networkConfiguration.getGateway(), 
                   networkConfiguration.getSubnetMask());
    delay(200);
}

void NetworkConnection::macCharArrayToBytes(const char* str, byte* bytes) {
    for (int i = 0; i < 6; i++) {
        bytes[i] = strtoul(str, NULL, 16);
        str = strchr(str, ':');
        if (str == NULL || *str == '\0') {
            break;
        }
        str++;
    }
}
#endif

#if defined(USE_WIFI)
void NetworkConnection::resetWiFiConfiguration() {
    WiFi.disconnect(true, true);
    delay(1000);
};
void NetworkConnection::connectWiFi() {
    WiFi.mode(WIFI_AP_STA);
    if (WiFi.psk().equals("")) {
        Log.notice(F("WiFi config not found. Starting WiFi Smart Config..."));
        WiFi.beginSmartConfig();
        while (!WiFi.smartConfigDone()) {
            delay(1000);
            Log.notice(".");
        }
    }
    if (waitForConnection(500, 5000)) {
        WiFi.localIP().toString().toCharArray(ipAddress, 16);
        WiFi.macAddress().toCharArray(macAddress, 18);
    }
}

bool NetworkConnection::waitForConnection(uint32_t retryDelayMs, uint32_t timeoutMs) {
    uint32_t now = millis();
    uint32_t startTime = now;
    uint8_t status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED && now - startTime < timeoutMs) {
        Log.notice(F("Trying to connect to WiFi (%d)..." CR), status);
        status = WiFi.begin();
        if (status == WL_CONNECT_FAILED) {
            WiFi.disconnect(true);
        }        
        delay(retryDelayMs);
        now = millis();
    }
    if (WiFi.isConnected()) {
        Log.notice(F("Connected to WiFi on IP %s" CR), WiFi.localIP().toString().c_str());
        return true;
    }
    return false;
}

void NetworkConnection::wifiConnectionCheck(uint32_t now) {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
}
#endif

