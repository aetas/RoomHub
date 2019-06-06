#pragma once

#include <inttypes.h>
#include "config/MasterConfig.hpp"
#include "EthernetConfiguration.hpp"

#ifdef USE_WIFI
#include <WiFi.h>
#endif

#ifdef USE_ETHERNET
#include <SPI.h>
#include <Ethernet.h>
#endif

class NetworkConnection {
public:
    void connect();
    void checkConnection(uint32_t now);
    const char* getIpAddress();
    const char* getMacAddress();
    Client& getClient();

    #if defined(USE_WIFI)
    void resetWiFiConfiguration();
    #elif defined(USE_ETHERNET)
    void setEthernetConfiguration(EthernetConfiguration ethConfig);
    #endif
private:
    EthernetConfiguration networkConfiguration;

    #ifdef USE_ETHERNET
    byte* mac = new byte[6];
    
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
