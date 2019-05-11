#pragma once

#include "log/BufferedLogger.hpp"
#include <string.h>

using namespace std;

class BufferedLoggerHelper {
public:
    BufferedLoggerHelper(BufferedLogger& _bufferedLogger): bufferedLogger(_bufferedLogger) {}
    void writeLog(string log) {
        
        for (int i = 0; i < log.size(); i++) {
            char c = log.at(i);
            bufferedLogger.write(c);
        }
    }
private:
    BufferedLogger& bufferedLogger;
};