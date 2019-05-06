#pragma once

#include "config/DeviceConfig.hpp"
#include "config/SpiffsConfigurationStorage.hpp"

/*
    GREEN_WHITE = 3,
    BLUE = 4,
    BLUE_WHITE = 5,
    GREEN = 6,
*/


void prepareDevicesConfigs() {
    SpiffsConfigurationStorage configurationStorage;
    configurationStorage.resetConfig();
    configurationStorage.storeName("Workshop");
    configurationStorage.storeMqttHostname("10.0.88.100");
    configurationStorage.storeDeviceConfig("1.0;101;switch_1;1;1;3;50\n");
    configurationStorage.storeDeviceConfig("1.0;102;switch_2;1;2;4;50\n");
    configurationStorage.storeDeviceConfig("1.0;103;output_dev_1;2;16;4;50\n");
}


// DeviceConfig switchButton1_1(101, "switch1", DeviceType::DIGITAL_INPUT, 1, WireColor::GREEN_WHITE, 50);
// DeviceConfig switchButton1_2(102, "switch2", DeviceType::DIGITAL_INPUT, 1, WireColor::BLUE, 50);
// DeviceConfig switchButton1_3(103, "switch3", DeviceType::DIGITAL_INPUT, 1, WireColor::BLUE_WHITE, 50);
// DeviceConfig switchButton1_4(104, "switch4", DeviceType::DIGITAL_INPUT, 1, WireColor::GREEN, 50);

// DeviceConfig switchButton2_1(105, "switch5", DeviceType::DIGITAL_INPUT, 2, WireColor::GREEN_WHITE, 50);
// DeviceConfig switchButton2_2(106, "switch6", DeviceType::DIGITAL_INPUT, 2, WireColor::BLUE, 50);
// DeviceConfig switchButton2_3(107, "switch7", DeviceType::DIGITAL_INPUT, 2, WireColor::BLUE_WHITE, 50);
// DeviceConfig switchButton2_4(108, "switch8", DeviceType::DIGITAL_INPUT, 2, WireColor::GREEN, 50);

// DeviceConfig switchButton3_1(109, "switch9", DeviceType::DIGITAL_INPUT, 3, WireColor::GREEN_WHITE, 50);
// DeviceConfig switchButton3_2(110, "switch10", DeviceType::DIGITAL_INPUT, 3, WireColor::BLUE, 50);
// DeviceConfig switchButton3_3(111, "switch11", DeviceType::DIGITAL_INPUT, 3, WireColor::BLUE_WHITE, 50);
// DeviceConfig switchButton3_4(112, "switch12", DeviceType::DIGITAL_INPUT, 3, WireColor::GREEN, 50);

// DeviceConfig switchButton4_1(113, "switch13", DeviceType::DIGITAL_INPUT, 4, WireColor::GREEN_WHITE, 50);
// DeviceConfig switchButton4_2(114, "switch14", DeviceType::DIGITAL_INPUT, 4, WireColor::BLUE, 50);
// DeviceConfig switchButton4_3(115, "switch15", DeviceType::DIGITAL_INPUT, 4, WireColor::BLUE_WHITE, 50);
// DeviceConfig switchButton4_4(116, "switch16", DeviceType::DIGITAL_INPUT, 4, WireColor::GREEN, 50);

// DeviceConfig currentMeasurement1(3, "current", DeviceType::SCT013, 2, WireColor::BROWN, 0);
// // DeviceConfig dht22_1(4, "dht22", DeviceType::DHT22, 2, WireColor::GREEN, 0);
// DeviceConfig relay1(5, "relay1", DeviceType::DIGITAL_OUTPUT, 5, WireColor::BLUE, 0);
// DeviceConfig relay2(6, "relay2", DeviceType::DIGITAL_OUTPUT, 8, WireColor::BLUE_WHITE, 0);
// DeviceConfig movementSensor1(7, "movement1", DeviceType::DIGITAL_INPUT, 9, WireColor::GREEN_WHITE, 50);
// DeviceConfig movementSensor2(8, "movement2", DeviceType::DIGITAL_INPUT, 12, WireColor::GREEN, 50);
// DeviceConfig switchButton3(9,  "switch3", DeviceType::DIGITAL_INPUT, 13, WireColor::BLUE_WHITE, 50);
// DeviceConfig switchButton4(10, "switch4", DeviceType::DIGITAL_INPUT, 16, WireColor::BLUE_WHITE, 50);
// DeviceConfig analogInput1(11, "analogInput1", DeviceType::ANALOG_INPUT, 3, WireColor::BROWN, 0);


// DeviceConfig devicesConfig[] = {
//                                 switchButton1_1, 
//                                 switchButton1_2, 
//                                 switchButton1_3, 
//                                 switchButton1_4, 
//                                 switchButton2_1, 
//                                 switchButton2_2, 
//                                 switchButton2_3, 
//                                 switchButton2_4, 
//                                 switchButton3_1, 
//                                 switchButton3_2, 
//                                 switchButton3_3, 
//                                 switchButton3_4, 
//                                 switchButton4_1, 
//                                 switchButton4_2, 
//                                 switchButton4_3, 
//                                 switchButton4_4, 
//                                 currentMeasurement1, 
//                                 relay1, 
//                                 relay2, 
//                                 movementSensor1,
//                                 movementSensor2, 
//                                 switchButton3, 
//                                 switchButton4, 
//                                 analogInput1
//                                 };