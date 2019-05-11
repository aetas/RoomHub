#pragma once


// -- Basic ---------------------------------------

#define FIRMWARE_NAME       "Aetas RoomHub"
#define FIRMWARE_VERSION    "3.0.0"


// -- Network --------------------------------------
#define USE_WIFI


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
#define HOMIE_STATS_INTERVAL_SEC    20
#define MQTT_PORT                   1883              // MQTT port
#define MQTT_USER                   ""                // MQTT user
#define MQTT_PASS                   ""                // MQTT password


// -- EXTRA BUTTONS -------------------------------
#define EXTRA_BUTTON_CONFIG_RESET_PIN               12
#define EXTRA_BUTTON_CONFIG_RESET_TIME_TO_RESET_MS  5000
#define EXTRA_BUTTON_WIFI_RESET_PIN                 14
#define EXTRA_BUTTON_WIFI_RESET_TIME_TO_RESET_MS    5000