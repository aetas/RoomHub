#include "../main/catch.hpp"
#include "config/DeviceConfigParser.hpp"

#include <typeinfo>
#include <iostream>
#include <string.h>
using namespace std;

TEST_CASE("DeviceConfigParser")
{
    DeviceConfigParser parser;

    SECTION("should parse semicolon-separated-values to DeviceConfig") {
        // given:
        // version;id;name;type_int;port;wire_color_int;debounce
        const char* line = "1.0;103;test device name;2;16;4;100";
        
        // when
        DeviceConfig* device = parser.parse(line);

        // then
        REQUIRE(device != nullptr);
        REQUIRE(device->getId() == 103);
        REQUIRE(strcmp(device->getName(), "test device name") == 0);
        REQUIRE(device->getDeviceType() == DeviceType::DIGITAL_OUTPUT);
        REQUIRE(device->getPortNumber() == 16);
        REQUIRE(device->getWireColor() == WireColor::BLUE);
        REQUIRE(device->getDebounceMs() == 100);
    }

    SECTION("should return null if version is not supported (1.0 for now)") {
        // given:
        // version;id;name;type_int;port;wire_color_int;debounce
        const char* line = "2.0;103;test device name;2;16;4;100";

        // when
        DeviceConfig* device = parser.parse(line);

        // then
        REQUIRE(device == nullptr);
    }
}