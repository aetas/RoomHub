#pragma once

#include "MasterConfig.hpp"

// -- Homie  (MQTT) -------------------------------
#define HOMIE_STATS_INTERVAL_SEC    20
#define MQTT_PORT                   1883              // [MqttPort] MQTT port
#define MQTT_USER                   ""                // [MqttUser] MQTT user
#define MQTT_PASS                   ""                // [MqttPassword] MQTT password



// -- Logging -------------------------------------

#define LOG_LEVEL         LOG_LEVEL_VERBOSE      // [LogLevel] (LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_NOTICE, 
                                                 //             LOG_LEVEL_TRACE, LOG_LEVEL_VERBOSE)
#define LOG_ENABLE_WEB                           // [LogEnableWeb] Enables log page on [WIFI_IP_ADDRESS]/logs                     
#define LOG_BUFFERED_LOGGER_BUFFER_SIZE     1000 // [LogBufferedLoggerBufferSize] Size of the buffer - increase if web logs are cut


// -- Network --------------------------------------
#define USE_WIFI
