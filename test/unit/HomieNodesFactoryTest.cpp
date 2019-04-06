#include "../main/catch.hpp"
#include "homie/HomieNodeFactory.hpp"
#include "mocks/FakeMqttClient.hpp"

#include <typeinfo>
#include <iostream>
using namespace std;

// TEST_CASE("HomieNodeFactory") {

//     FakeMqttClient mqttClient;

    
//     SECTION("should set last will message to set state to 'lost'") {
//         // given
//         DeviceConfig digitalInputDeviceConfig(24, DeviceType::DIGITAL_INPUT, 3, WireColor::BLUE, 250);
//         DeviceConfig analogInputDeviceConfig(11, DeviceType::ANALOG_INPUT, 16, WireColor::BROWN, 0);
//         DeviceConfig digitalOutputDeviceConfig(36, DeviceType::DIGITAL_OUTPUT, 16, WireColor::BLUE_WHITE, 0);
//         DeviceConfig devices[] = {digitalInputDeviceConfig, analogInputDeviceConfig, digitalOutputDeviceConfig};

//         // when
//         HomieNode** nodes = HomieNodeFactory::createNodes(devices, 3, "deviceName", mqttClient);
//         for(uint8_t i = 0; i < 3; i++) {
//             nodes[i]->setup();
//         }
        

//         // then
//         // REQUIRE(mqttClient.getValuePublishedTo("homie/"));
        
//     }
// }