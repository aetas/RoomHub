#include "../main/catch.hpp"
#include "homie/HomieDevice.hpp"
#include "homie/HomieNode.hpp"
#include "homie/HomieNodeProperty.hpp"
#include "mocks/FakeMqttClient.hpp"
#include "mocks/ArduinoLog.h"

#include <typeinfo>
#include <iostream>
using namespace std;

Logger Log = Logger();

TEST_CASE("HomieDevice") {

    FakeMqttClient mqttClient;
    
    const char* deviceName = "devName";
    HomieNodeProperty node1prop1("testProp1", false, false, PropertyUnit::COUNT, PropertyDataType::INTEGER, "");
    HomieNodeProperty* props1[1] = { &node1prop1 };
    HomieNodeProperty node2prop1("testProp2", false, false, PropertyUnit::COUNT, PropertyDataType::INTEGER, "");
    HomieNodeProperty* props2[1] = { &node2prop1 };
    HomieNodeProperty node3prop1("testProp3", false, false, PropertyUnit::COUNT, PropertyDataType::INTEGER, "");
    HomieNodeProperty* props3[1] = { &node3prop1 };
    HomieNode homieNode1(deviceName, "1", "name1", "someType", props1, 1, mqttClient);
    HomieNode homieNode2(deviceName, "2", "name2", "diffType", props2, 1, mqttClient);
    HomieNode homieNode3(deviceName, "3", "name3", "thirdType", props3, 1, mqttClient);
    HomieNode* nodes[3] = {&homieNode1, &homieNode2, &homieNode3};
    HomieDevice homieDevice(deviceName, "8.1.7", 10, "firmware name value", "7.8.9", "192.154.1.25", "00:0a:95:9d:68:16",  nodes, 3, mqttClient);

    SECTION("should send basic, non-modifiable properties to MQTT on setup (homie,name,stats,implementation,stats interval,firmware,state)") {
        // when
        homieDevice.setup();

        // then
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$homie") == "8.1.7");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$name") == "devName");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$stats") == "uptime,signal");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$implementation") == "Aetas");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$stats/interval") == "10");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$fw/name") == "firmware name value");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$fw/version") == "7.8.9");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$localip") == "192.154.1.25");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$mac") == "00:0a:95:9d:68:16");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$state") == "ready");
    }

    SECTION("should send nodes list to MQTT on setup") {
        // when
        homieDevice.setup();

        // then
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$nodes") == "1,2,3");
    }

    SECTION("should send last will testament (LWT) to MQTT on setup") {
        // expect
        REQUIRE(mqttClient.getLastWillTo("homie/devName/$state") == "lost");
    }

    SECTION("should update stats only after interval passed") {
        // when
        homieDevice.setup();
        homieDevice.loop(0);
        homieDevice.loop(9999);
        // then
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$stats/uptime") == "0");
        
        // and when
        homieDevice.loop(10001);

        // then
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/$stats/uptime") == "10");
    }

    SECTION("should setup all nodes on device setup") {
        // when
        homieDevice.setup();

        // then
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/$name") == "name1");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/2/$name") == "name2");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/3/$name") == "name3");
    }

}