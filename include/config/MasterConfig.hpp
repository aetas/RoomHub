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
#define LOG_ENABLE_WEB                           // Enables log page on [WIFI_IP_ADDRESS]/logs                     
#define LOG_BUFFERED_LOGGER_BUFFER_SIZE     1000 // [LogBufferedLoggerBufferSize] Size of the buffer - increase if web logs are cut


// -- Homie  (MQTT) -------------------------------
#define HOMIE_STATS_INTERVAL_SEC    20
#define MQTT_PORT                   1883              // [MqttPort] MQTT port
#define MQTT_USER                   ""                // [MqttUser] MQTT user
#define MQTT_PASS                   ""                // [MqttPassword] MQTT password


// -- EXTRA BUTTONS -------------------------------
#define EXTRA_BUTTON_RESET_PIN                  12
#define EXTRA_BUTTON_RESET_TIME_TO_RESET_MS     5000