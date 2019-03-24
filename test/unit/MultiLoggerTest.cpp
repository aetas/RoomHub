#include "../main/catch.hpp"
#include "mocks/FakeLogger.hpp"
#include "log/MultiLogger.hpp"

#include <typeinfo>
#include <iostream>
#include <string.h>
using namespace std;

TEST_CASE("MultiLogger")
{

    SECTION("should write to all passed loggers") {
        // given
        FakeLogger fakeLogger1;
        FakeLogger fakeLogger2;
        FakeLogger fakeLogger3;
        Print* loggers[3] = { &fakeLogger1, &fakeLogger2, &fakeLogger3 };
        MultiLogger multiLogger(loggers, 3);

        // when
        multiLogger.write('a');
        multiLogger.write('b');
        multiLogger.write('c');
        multiLogger.write('d');
        multiLogger.write('e');
        multiLogger.write('f');

        // then
        REQUIRE(fakeLogger1.getLogs() == "abcdef");
        REQUIRE(fakeLogger2.getLogs() == "abcdef");
        REQUIRE(fakeLogger3.getLogs() == "abcdef");

    }
}