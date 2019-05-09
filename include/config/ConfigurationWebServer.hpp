#pragma once

#include "ConfigurationServer.hpp"
#include "ConfigurationStorage.hpp"

class ConfigurationWebServer: public ConfigurationServer {
public:
    ConfigurationWebServer(ConfigurationStorage& storage);
    void startConfigServer();
private:
    ConfigurationStorage& storage;
    bool configurationFinished = false;
};
