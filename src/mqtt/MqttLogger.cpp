#include "mqtt/MqttLogger.hpp"
#include "config/MasterConfig.hpp"

MqttLogger::MqttLogger(MqttClient& _mqttClient, BufferedLogger& _logger, const char* _topic): 
    mqttClient(_mqttClient), 
    logger(_logger), 
    topic(_topic) {
}

void MqttLogger::loop(uint32_t now) {
    if (now - lastTimeLogPublished > LOG_MQTT_INTERVAL_MS) {
        sendLogs();
        lastTimeLogPublished = now;
    }
}

void MqttLogger::sendLogs() {
    int bufferSize = logger.getBufferSize();
    if (bufferSize > 1) {
        char* bufferedLogs = new char[bufferSize];
        logger.read(bufferedLogs);
        if (!mqttClient.publish(topic, bufferedLogs, false, false)) {
            logger.clearBuffer();
        }
        delete[] bufferedLogs;
    }
}