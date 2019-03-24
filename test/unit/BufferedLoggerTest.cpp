#include "../main/catch.hpp"
#include "log/BufferedLogger.hpp"

#include <typeinfo>
#include <iostream>
#include <string.h>
using namespace std;

TEST_CASE("BufferedLogger")
{

    SECTION("should write characters to buffer") {
        // given
        BufferedLogger logger(6);
        logger.write('a');
        logger.write('b');
        logger.write('c');
        logger.write('d');
        logger.write('e');
        logger.write('f');

        // when
        char* bufferedLogs = new char[logger.getBufferSize()];
        logger.read(bufferedLogs);
        string bufferedLogsString(bufferedLogs);

        // then
        REQUIRE(bufferedLogsString == "abcdef");
    }

    SECTION("should clean buffer when reading") {
        // given
        BufferedLogger logger(50);
        logger.write('t');
        logger.write('e');
        logger.write('s');
        logger.write('t');

        // when
        char* bufferedLogs = new char[10];
        logger.read(bufferedLogs);
        logger.write('a');
        logger.write('e');
        logger.write('t');
        logger.write('a');
        logger.write('s');
        bool overriden = logger.read(bufferedLogs);
        string bufferedLogsString(bufferedLogs);

        // then
        REQUIRE(overriden == false);
        REQUIRE(bufferedLogsString == "aetas");
    }

    SECTION("should clean buffer and return true on reading when buffer has been overriden") {
        // given
        BufferedLogger logger(4);
        logger.write('1');
        logger.write('2');
        logger.write('3');
        logger.write('4');
        logger.write('5');
        logger.write('6');

        // when
        char* bufferedLogs = new char[logger.getBufferSize()];
        bool overriden = logger.read(bufferedLogs);
        string bufferedLogsString(bufferedLogs);

        // then
        REQUIRE(overriden == true);
        REQUIRE(bufferedLogsString == "56");
    }
}