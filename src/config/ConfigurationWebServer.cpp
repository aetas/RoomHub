#include "config/ConfigurationWebServer.hpp"

#include <WebServer.h>
#include "SPIFFS.h"
#include "config/MasterConfig.hpp"

// TODO maj: does it work at all??
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
        server.send(201, "text/plain", "Name stored");
    });
    
    server.on("/config/mqtt", HTTP_POST, [&server, this]() {
        String body = server.arg("plain");
        storage.storeMqttHostname(body.c_str());
        server.send(201, "text/plain", "MQTT configuration stored");
    });

    server.on("/config/device", HTTP_POST, [&server, this]() {
        String body = server.arg("plain");
        storage.storeDeviceConfig(body.c_str());
        server.send(201, "text/plain", "Device configuration stored");
    });

    server.on("/config/finalize", HTTP_POST, [&server, this]() {
        configurationFinished = true;
        server.send(201, "text/plain", "Configuration finalized");
    });

    while(!configurationFinished) {
        server.handleClient();
    }
}