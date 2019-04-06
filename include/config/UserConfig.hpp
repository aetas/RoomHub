#pragma once

// -- Basic ---------------------------------------

#define DEVICE_NAME         "AetasRoomHub" // TODO maj: move to external configuration
#define FIRMWARE_NAME       "Aetas RoomHub"
#define FIRMWARE_VERSION    "3.0.0"


// -- Homie  (MQTT) -------------------------------
#define HOMIE_STATS_INTERVAL_SEC    30
#define MQTT_HOST                   "192.168.1.170"   // [MqttHost]
#define MQTT_PORT                   1883              // [MqttPort] MQTT port
#define MQTT_USER                   "garage"          // [MqttUser] MQTT user
#define MQTT_PASS                   ""                // [MqttPassword] MQTT password



// -- Logging -------------------------------------

#define LOG_LEVEL         LOG_LEVEL_VERBOSE      // [LogLevel] (LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_NOTICE, 
                                                 //             LOG_LEVEL_TRACE, LOG_LEVEL_VERBOSE)
#define LOG_ENABLE_WEB                           // [LogEnableWeb] Enables log page on [WIFI_IP_ADDRESS]/logs                     
#define LOG_BUFFERED_LOGGER_BUFFER_SIZE     1000 // [LogBufferedLoggerBufferSize] Size of the buffer - increase if web logs are cut


// -- Network --------------------------------------  // TODO maj: move to external configuration
#define USE_WIFI
#define WIFI_USE_DHCP          true                     // [WifiUseDhcp]     
#define WIFI_IP_ADDRESS        IPAddress(0,0,0,0)       // [WifiIpAddress] Set IP address when not using DHCP
#define WIFI_GATEWAY           IPAddress(192,168,1,1)   // [WifiGateway] If not using DHCP set Gateway IP address
#define WIFI_SUBNETMASK        IPAddress(255,255,255,0) // [WifiSubnetmask] If not using DHCP set Network mask
#define WIFI_DNS               IPAddress(192,168,1,1)   // [WifiDns] If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)

#define WIFI_SSID              "LesnaStreet"           // [Ssid1] Wifi SSID - comment out to use built-in portal to set up wifi on [WIFI_IP_ADDRESS]/_ac
#define WIFI_PASS              "InzynierskaWroclaw"    // [Password1] Wifi password