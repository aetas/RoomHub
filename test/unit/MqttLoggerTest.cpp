#include "../main/catch.hpp"
#include "mqtt/MqttLogger.hpp"

#include "mocks/FakeMqttClient.hpp"
#include "utils/BufferedLoggerHelper.hpp"

#include <typeinfo>
#include <iostream>
#include <string.h>
using namespace std;

TEST_CASE("MqttLogger")
{

    FakeMqttClient mqttClient;
    BufferedLogger bufferedLogger(512);
    BufferedLoggerHelper loggerHelper(bufferedLogger);
    MqttLogger mqttLogger(mqttClient, bufferedLogger, "my/$logs");

  
    
    SECTION("should publish line of log from buffered logger to mqtt client") {
        // given
        loggerHelper.writeLog("some line to be logged from test");

        // when
        mqttLogger.sendLogs();

        // then
        REQUIRE(mqttClient.getValuePublishedTo("my/$logs", false) == "some line to be logged from test");
    }

    SECTION("should send logs lines one by one when buffered logs contains multiple lines") {
        // given
        loggerHelper.writeLog("this is first line\n");
        loggerHelper.writeLog("this is second line\n");
        loggerHelper.writeLog("this is third line\n");

        // when
        mqttLogger.sendLogs();

        // then
        REQUIRE(mqttClient.getValuePublishedTo("my/$logs", false, 0) == "this is first line");
        REQUIRE(mqttClient.getValuePublishedTo("my/$logs", false, 1) == "this is second line");
        REQUIRE(mqttClient.getValuePublishedTo("my/$logs", false, 2) == "this is third line");
    }  
}