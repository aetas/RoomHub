#pragma once

#include "config/ConfigurationServer.hpp"

class FakeConfigurationServer: public ConfigurationServer {
public:
    void startConfigServer() { running = true; }
    bool isRunning() { return running; }
private:
    bool running = false;
};