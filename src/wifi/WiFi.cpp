#include "wifi/WiFi.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoLog.h>

void resetWiFiConfiguration() {
    WiFi.disconnect(true, true);
    delay(1000);
};


bool waitForConnection(uint32_t retryDelayMs, uint32_t timeoutMs) {
    uint32_t now = millis();
    uint32_t startTime = now;
    uint8_t status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED && now - startTime < timeoutMs) {
        Log.trace(F("Trying to connect to WiFi (%d)..." CR), status);
        status = WiFi.begin();
        if (status == WL_CONNECT_FAILED) {
            WiFi.disconnect(true);
        }        
        delay(retryDelayMs);
        now = millis();
    }
    if (WiFi.isConnected()) {
        Log.notice(F("Connected to WiFi on IP %s" CR), WiFi.localIP().toString().c_str());
        return true;
    }
    return false;
}

void connectWiFi() {
    WiFi.mode(WIFI_AP_STA);
    if (WiFi.psk().equals("")) {
        Log.notice(F("WiFi config not found. Starting WiFi Smart Config..."));
        WiFi.beginSmartConfig();
        while (!WiFi.smartConfigDone()) {
            delay(1000);
            Log.notice(".");
        }
    }
    waitForConnection(500, 5000);
}


void wifiConnectionCheck(long now) {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
}

void firstTimeMqttConfiguration() {
    
};