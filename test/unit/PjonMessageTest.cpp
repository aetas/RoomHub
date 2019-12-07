#include "../main/catch.hpp"
#include "device/pjon/PjonMessage.hpp"


#include <typeinfo>
#include <iostream>
#include <string.h>
using namespace std;

TEST_CASE("PjonMessage")
{
    SECTION("should parse PjonMessage from string") {
        // given
        char* stringMessage = "VALUE;123;456;789456";
        
        // when
        PjonMessage message = PjonMessage::fromString(stringMessage);

        // then
        const char** values = message.getValues();
        REQUIRE(string(message.getType()) == "VALUE");
        REQUIRE(string(values[0]) == "123");
        REQUIRE(string(values[1]) == "456");
        REQUIRE(string(values[2]) == "789456");

    }
}