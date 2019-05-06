#pragma once

#include "DeviceConfig.hpp"


class DeviceConfigParser {
public:
    DeviceConfig* parse(const char* line);
private:
    const char* SEPARATOR = ";";
};