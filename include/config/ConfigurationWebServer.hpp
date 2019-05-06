#pragma once

#include "ConfigurationStorage.hpp"

class ConfigurationWebServer {
public:
    ConfigurationWebServer(ConfigurationStorage& storage);
    void startConfigServer();
private:
    ConfigurationStorage& storage;
    bool configurationFinished = false;
};
