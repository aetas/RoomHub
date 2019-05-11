#include "../main/catch.hpp"

#include "device/DevicesRegistry.hpp"
#include "mocks/FakeMqttClient.hpp"
#include "homie/HomieDevice.hpp"
#include "mocks/FakeDevice.hpp"
#include "mocks/FakeStatsData.hpp"
#include "mqtt/MqttCommandReceiver.hpp"


TEST_CASE("MqttCommandReceiver") {

    DevicesRegistry registry(5);
    
    
    FakeMqttClient mqttClient;
    FakeStatsData statsData;
    
    const char* deviceName = "devName";
    HomieNodeProperty node1prop1("testProp1", false, false, PropertyUnit::COUNT, PropertyDataType::INTEGER, "");
    HomieNodeProperty* props1[1] = { &node1prop1 };
    HomieNode homieNode1(deviceName, "1", "name1", "someType", props1, 1, mqttClient);
    HomieNode* nodes[1] = {&homieNode1};
    HomieDevice homieDevice(deviceName, 10, "firmware name value", "7.8.9", "192.154.1.25", "00:0a:95:9d:68:16", nodes, 1, mqttClient, statsData);

    MqttCommandReceiver& commandReceiver = MqttCommandReceiver::getInstance(&registry, &homieDevice);
    

    SECTION("should change device state when command receiver receives command") {
        // given
        FakeDevice fakeDevice1(1, DeviceType::DIGITAL_OUTPUT);
        FakeDevice fakeDevice2(2, DeviceType::DIGITAL_OUTPUT);
        registry.add(&fakeDevice1);
        registry.add(&fakeDevice2);

        // when
        String id = "1";
        String propertyName = "testProp1";
        byte* value = (unsigned char*)("newState123");
        const char* topic = "homie/devName/1/testProp1/set";
        MqttCommandReceiver::messageReceived(topic, value, 12);

        // then
        REQUIRE(fakeDevice1.currentPropertyValue("testProp1") == "newState123");
    }

      SECTION("should send MQTT message when new value is set") {
        // given
        FakeDevice fakeDevice1(1, DeviceType::DIGITAL_OUTPUT);
        registry.add(&fakeDevice1);

        // when
        byte* value = (unsigned char*)"newState456";
        const char* topic = "homie/devName/1/testProp1/set";
        MqttCommandReceiver::messageReceived(topic, value, 12);

        // then
        REQUIRE(mqttClient.getValuePublishedTo("homie/devName/1/testProp1") == "newState456");
    }
}