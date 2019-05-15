#pragma once

#include <inttypes.h>
#include "config/MasterConfig.hpp"

#ifdef USE_WIFI
#include <WiFi.h>
#endif

#ifdef USE_ETHERNET
#include <SPI.h>
#include <Ethernet.h>
#endif

class NetworkConnection {
public:
    NetworkConnection();
    void connect();
    void checkConnection(uint32_t now);
    const char* getIpAddress();
    const char* getMacAddress();
    Client& getClient();

    #ifdef USE_WIFI
    void resetWiFiConfiguration();
    #endif
private:
    char* ipAddress = new char[16];
    char* macAddress = new char[18];

    #ifdef USE_ETHERNET
    byte* mac = new byte[6];
    IPAddress ip;
    EthernetClient ethClient;

    void ethernetWizReset(const uint8_t resetPin);
    void connectEthernet();
    void macCharArrayToBytes(const char* str, byte* bytes);
    #endif

    #ifdef USE_WIFI
    WiFiClient ethClient;

    void connectWiFi();
    bool waitForConnection(uint32_t retryDelayMs, uint32_t timeoutMs);
    void wifiConnectionCheck(uint32_t now);
    #endif
};
