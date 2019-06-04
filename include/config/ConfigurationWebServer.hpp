#pragma once

#include "MasterConfig.hpp"
#include "ConfigurationServer.hpp"
#include "ConfigurationStorage.hpp"

#if defined(USE_ETHERNET)
#include <SPI.h>
#include <Ethernet.h> 
#endif

class ConfigurationWebServer: public ConfigurationServer {
public:
    ConfigurationWebServer(ConfigurationStorage& storage);
    void startConfigServer();
private:
    ConfigurationStorage& storage;
    bool configurationFinished = false;

    const char* SUPPORTED_DEVICE_FORMAT_VERSION = "1.0";

    #if defined(USE_WIFI)
    void startWiFiConfigServer();
    #elif defined(USE_ETHERNET)
    void startEthernetConfigServer();
    // TODO maj: reset ethernet configuration to defaults to be able to configure new IP and MAC
    // void ethernetHandleReset(WebServer &server, WebServer::ConnectionType type, char* urlTail, bool tailComplete);
    #endif
};
