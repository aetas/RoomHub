#include "config/ConfigurationWebServer.hpp"

#if defined(USE_WIFI)
#include <WebServer.h>
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
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
    

    while (!configurationFinished) {
        EthernetClient client = server.available();
        if (client) {
            // an http request ends with a blank line
            boolean currentLineIsBlank = true;
            String req_str = "";
            int data_length = -1;

            
            //int empty_line_count = 0;
            while (client.connected()) {
                if (client.available()) {
                    char c = client.read();

                    Serial.print(c);
                    //Serial.write(c);
                    req_str += c;
                    // if you've gotten to the end of the line (received a newline
                    // character) and the line is blank, the http request has ended
                    if (c == '\n' && currentLineIsBlank && req_str.startsWith("POST /config/reset"))
                    {
                        String temp = req_str.substring(req_str.indexOf("Content-Length:") + 15);
                        temp.trim();
                        //Serial.print("Content-Length=");
                        data_length = temp.toInt();
                        /*Serial.println(data_length);
                        writeResponse(client);
                        break;*/
                        while (data_length-- > 0)
                        {
                            c = client.read();
                            req_str += c;
                        }
                        // writeResponse(client);
                        break;
                    }

                    if (c == '\n') {
                        // you're starting a new line
                        currentLineIsBlank = true;
                    } else if (c != '\r') {
                        // you've gotten a character on the current line
                        currentLineIsBlank = false;
                    }
                    break;
                }
                

                Serial.println(req_str);

                // give the web browser time to receive the data
                delay(1);
                // close the connection:
                client.stop();
                Serial.println("client disconnected");
            }
        }
    }
}

#endif