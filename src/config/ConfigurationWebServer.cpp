#include "config/ConfigurationWebServer.hpp"

#include <WebServer.h>
#include "SPIFFS.h"
#include "config/MasterConfig.hpp"

ConfigurationWebServer::ConfigurationWebServer(ConfigurationStorage& _storage): storage(_storage) {
}


void ConfigurationWebServer::startConfigServer() {
    WebServer server(80);

    server.on("/config/reset", HTTP_POST, [&server, this]() {
        String body = server.arg("plain");
        storage.resetConfig();
        server.send(201, "text/plain", "Configuration deleted");
    });

     server.on("/config/name", HTTP_POST, [&server, this]() {
        String body = server.arg("plain");
        storage.storeName(body.c_str());
        server.send(201, "text/plain", body.c_str());
    });
    
    server.on("/config/mqtt", HTTP_POST, [&server, this]() {
        String body = server.arg("plain");
        storage.storeMqttHostname(body.c_str());
        server.send(201, "text/plain", body.c_str());
    });

    server.on("/config/device", HTTP_POST, [&server, this]() {
        String body = server.arg("plain");
        if (!body.startsWith(SUPPORTED_DEVICE_FORMAT_VERSION)) {
            server.send(400, "text/plain", "Unsupported device format version");
        }
        storage.storeDeviceConfig(body.c_str());
        server.send(201, "text/plain", body.c_str());
    });

    server.on("/config/finalize", HTTP_POST, [&server, this]() {
        configurationFinished = true;
        server.send(201, "text/plain", "Configuration finalized");
    });

    server.begin();
    while(!configurationFinished) {
        server.handleClient();
    }
}