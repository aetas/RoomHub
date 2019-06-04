#include "config/ConfigurationWebServer.hpp"

#if defined(USE_WIFI)
#include <WebServer.h>
#elif defined(USE_ETHERNET)
#include "httpserver/HttpServer.hpp"
#endif

#include "SPIFFS.h"
#include "config/MasterConfig.hpp"

ConfigurationWebServer::ConfigurationWebServer(ConfigurationStorage& _storage): storage(_storage) {
}

void ConfigurationWebServer::startConfigServer() {
    #if defined(USE_WIFI)
    startWiFiConfigServer();
    #elif defined(USE_ETHERNET)
    startEthernetConfigServer();
    #endif
}

#if defined(USE_WIFI)
void ConfigurationWebServer::startWiFiConfigServer() {
    WebServer server(80);

    server.on("/config/reset", HTTP_POST, [&server, this]() {
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

#elif defined(USE_ETHERNET)

void ConfigurationWebServer::startEthernetConfigServer()  {
    Serial.println("Starting Ethernet server...");
    EthernetServer server(80);
    server.begin();
    HttpServer httpServer;

    httpServer.on(HttpMethod::POST, "/config/reset", [&httpServer, this](const String& body) {
        storage.resetConfig();
        httpServer.send(201, "text/plain", "Configuration deleted");
    });

     httpServer.on(HttpMethod::POST, "/config/name", [&httpServer, this](const String& body) {
        storage.storeName(body.c_str());
        httpServer.send(201, "text/plain", body.c_str());
    });
    
    httpServer.on(HttpMethod::POST, "/config/mqtt", [&httpServer, this](const String& body) {
        storage.storeMqttHostname(body.c_str());
        httpServer.send(201, "text/plain", body.c_str());
    });

    httpServer.on(HttpMethod::POST, "/config/device", [&httpServer, this](const String& body) {
        if (!body.startsWith(SUPPORTED_DEVICE_FORMAT_VERSION)) {
            httpServer.send(400, "text/plain", "Unsupported device format version");
        }
        storage.storeDeviceConfig(body.c_str());
        httpServer.send(201, "text/plain", body.c_str());
    });

    httpServer.on(HttpMethod::POST, "/config/finalize", [&httpServer, this](const String& body) {
        configurationFinished = true;
        httpServer.send(201, "text/plain", "Configuration finalized");
    });
    
    while (!configurationFinished) {
        EthernetClient client = server.available();
        httpServer.handleClient(client);
    }
}

#endif