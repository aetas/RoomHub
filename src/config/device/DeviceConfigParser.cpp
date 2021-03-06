#include "config/device/DeviceConfigParser.hpp"
#include "ArduinoLog.h"
#include <WString.h>
#include <stdlib.h>

DeviceConfig* DeviceConfigParser::parse(const char* line) {
    char* lineCopy = strdup(line);
    const char* version = strtok(lineCopy, SEPARATOR);

    if (strcmp(version, "1.0") != 0) {
        Log.error(F("Unsupported device config string version '%s'"), version);
        return nullptr;
    }

    uint8_t id = atoi(strtok(0, SEPARATOR));
    const char* name = strtok(0, SEPARATOR);
    DeviceType type = static_cast<DeviceType>(atoi(strtok(0, SEPARATOR)));
    uint8_t port = atoi(strtok(0, SEPARATOR));
    WireColor wireColor = static_cast<WireColor>(atoi(strtok(0, SEPARATOR)));
    uint16_t debounceMs = atoi(strtok(0, SEPARATOR));
    uint8_t pjonId = atoi(strtok(0, SEPARATOR));
    // Log.verbose(F("Parsed DeviceConfig(id=%i, name=%s, port=%i, debounceMs=%i, pjonId=%i)" CR), id, name, port, debounceMs, pjonId);
    return new DeviceConfig(id, name, type, port, wireColor, debounceMs, pjonId);
}