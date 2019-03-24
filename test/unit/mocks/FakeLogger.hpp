#pragma once

#include <Print.h>
#include <string.h>
#include <iostream>

using namespace std;

class FakeLogger : public Print {

public:
    virtual size_t write(uint8_t character) {
        buffer += character;
    };
    string getLogs() {
        return buffer;
    };

  private:
    string buffer = "";
};