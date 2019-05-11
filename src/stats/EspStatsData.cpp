#include "stats/EspStatsData.hpp"

#include <Esp.h>

#include "config/MasterConfig.hpp"

#ifdef USE_WIFI
#include <WiFi.h>
#endif

uint32_t EspStatsData::getFreeHeapInBytes() {
    return ESP.getFreeHeap();
}
uint8_t EspStatsData::getSignalStrength() {
    #ifdef USE_WIFI
        int8_t rssi = WiFi.RSSI();
        if (rssi < -92) {
            return 1;
        } else if (rssi > -21) {
            return 100;
        }
        return round((-0.0154*rssi*rssi)-(0.3794*rssi)+98.182);
    #else
        return 0;
    #endif
}