#include "../main/catch.hpp"
#include "homie/HomieNode.hpp"
#include "mocks/FakeMqttClient.hpp"
#include "mocks/ArduinoLog.h"

#include <typeinfo>
#include <iostream>
using namespace std;

TEST_CASE("HomieNode") {

    FakeMqttClient mqttClient;
    
    const char* deviceName = "devName";

    SECTION("should send basic, non-modifiable properties to MQTT on setup (name,type,propertiesList)") {
        // given
        HomieNodeProperty nodeProp1("testProp1", false, false, PropertyUnit::COUNT, PropertyDataType::INTEGER, "");
        HomieNodeProperty nodeProp2("testProp2", true, true, PropertyUnit::METER, PropertyDataType::ENUM, "ON,OFF");
        HomieNodeProperty* props[2] = { &nodeProp1, &nodeProp2 };
        
        HomieNode homieNode(deviceName, "1", "node1", "someType", props, 2, mqttClient);

        // when
        
        homieNode.setup();

        // then
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/$name") == "node1");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/$type") == "someType");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/$properties") == "testProp1,testProp2");
        
        // and properties
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp1/$settable") == "false");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp1/$retained") == "false");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp1/$unit") == "#");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp1/$datatype") == "integer");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp1/$format") == "");

        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp2/$settable") == "true");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp2/$retained") == "true");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp2/$unit") == "m");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp2/$datatype") == "enum");
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp2/$format") == "ON,OFF");
    }

     SECTION("should send property update to MQTT on property update") {
        // given
        HomieNodeProperty nodeProp1("testProp1", false, false, PropertyUnit::COUNT, PropertyDataType::INTEGER, "");
        HomieNodeProperty nodeProp2("testProp2", true, true, PropertyUnit::METER, PropertyDataType::ENUM, "ON,OFF");
        HomieNodeProperty* props[2] = { &nodeProp1, &nodeProp2 };
        
        HomieNode homieNode(deviceName, "1", "node1", "someType", props, 2, mqttClient);

        // when
        
        homieNode.propertyValueUpdated("testProp1", "475");

        // then
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp1") == "475");
    }


     SECTION("should subscribe for MQTT messages when property is settable") {
        // given
        HomieNodeProperty nodeProp1("testProp1", false, false, PropertyUnit::COUNT, PropertyDataType::INTEGER, "");
        HomieNodeProperty nodeProp2("testProp2", true, true, PropertyUnit::METER, PropertyDataType::ENUM, "ON,OFF");
        HomieNodeProperty* props[2] = { &nodeProp1, &nodeProp2 };
        
        HomieNode homieNode(deviceName, "1", "node1", "someType", props, 2, mqttClient);

        // when
        homieNode.setup();

        // then
        REQUIRE(mqttClient.isSubscribedTo("homie/devName/1/testProp1/set") == false);
        REQUIRE(mqttClient.isSubscribedTo("homie/devName/1/testProp2/set") == true);
    }

}