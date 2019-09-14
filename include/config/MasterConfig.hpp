#pragma once


// -- Basic ---------------------------------------

#define FIRMWARE_NAME       "Aetas RoomHub"
#define FIRMWARE_VERSION    "3.1.0-RC7-WIFI"


// -- Network --------------------------------------
#define USE_WIFI                                 // Use WiFi for network (e.g. to connect to MQTT) - use this or USE_ETHERNET, never both
// #define USE_ETHERNET                                // Use wired ethernet for network - use this or USE_WIFI, never both
// #define ETHERNET_MAC            "5F:D9:98:B9:10:49" // Ethernet MAC address (have to be unique between devices in the same network)
// #define ETHERNET_IP             "192.168.1.2"       // IP address of RoomHub when on Ethernet connection

// #define ETHERNET_RESET_PIN      11      // ESP32 pin where reset pin from W5500 is connected
// #define ETHERNET_CS_PIN         5       // ESP32 pin where CS pin from W5500 is connected



// -- WIFI ----------------------------------------

#define WIFI_CONNECT_DELAY_MS       1000
#define WIFI_CONNECT_TIMEOUT_MS     10000


// -- Logging -------------------------------------

#define LOG_LEVEL         LOG_LEVEL_VERBOSE      // (LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_NOTICE, 
                                                 //  LOG_LEVEL_TRACE, LOG_LEVEL_VERBOSE)
#define LOG_BUFFERED_LOGGER_BUFFER_SIZE     512  // Size of the buffer - increase if logs on MQTT topic are cut
#define LOG_MQTT_ENABLED                         // Enables publishing logs to MQTT topic ([HOMIE_PREFIX]/[HUB_NAME]/$logs, e.g. 'homie/livingroom/$logs') 
#define LOG_MQTT_INTERVAL_MS                1000 // Specify how often logs are published to MQTT


// -- Homie (MQTT) --------------------------------
#define HOMIE_STATS_INTERVAL_SEC    30
#define MQTT_PORT                   1883              // MQTT port
#define MQTT_USER                   ""                // MQTT user
#define MQTT_PASS                   ""                // MQTT password


// -- EXTRA BUTTONS -------------------------------
#define EXTRA_BUTTON_CONFIG_RESET_PIN               12
#define EXTRA_BUTTON_CONFIG_RESET_TIME_TO_RESET_MS  5000
#define EXTRA_BUTTON_NETWORK_RESET_PIN              14
#define EXTRA_BUTTON_NETWORK_RESET_TIME_TO_RESET_MS 5000

