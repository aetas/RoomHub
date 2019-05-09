#include "config/SpiffsConfigurationStorage.hpp"
#include <SPIFFS.h>
#include <ArduinoLog.h>

SpiffsConfigurationStorage::~SpiffsConfigurationStorage() {
    delete[] devicesConfigs;
}

void SpiffsConfigurationStorage::storeName(const char* name) {
    store(NAME_CONFIG_FILE, name);
}

const char* SpiffsConfigurationStorage::readName() {
    return read(NAME_CONFIG_FILE);
}

void SpiffsConfigurationStorage::storeMqttHostname(const char* mqttHostname) {
    store(MQTT_CONFIG_FILE, mqttHostname);
}

const char* SpiffsConfigurationStorage::readMqttHostname() {
    return read(MQTT_CONFIG_FILE);
}

void SpiffsConfigurationStorage::storeDeviceConfig(const char* deviceConfigString) {
    uint8_t length = strlen(deviceConfigString) + 1;
    char* deviceConfigStringWithEndLine = new char[length];
    strcpy(deviceConfigStringWithEndLine, deviceConfigString);
    strcat(deviceConfigStringWithEndLine, "\n");
    store(DEVICES_CONFIG_FILE, deviceConfigStringWithEndLine, true);
}

DeviceConfig** SpiffsConfigurationStorage::readDevicesConfig() {
    if (!SPIFFS.begin(true)) {
        Log.error(MOUNTING_FAILED_MESSAGE);
        return NULL;
    }
    File file = SPIFFS.open(DEVICES_CONFIG_FILE, FILE_READ);
    if (!file) {
        Log.error(OPENING_FILE_FAILED_MESSAGE, DEVICES_CONFIG_FILE);
        return NULL;
    }
    uint8_t deviceNumber = 0;
    Log.notice(F("Reading stored devices configuration..." CR));
    while (String line = file.readStringUntil('\n')) {
        if (line == nullptr) {
            Log.trace(F("End of devices file" CR));
            break;
        }
        // Log.verbose("%s" CR, line.c_str());
        devicesConfigs[deviceNumber++] = deviceConfigParser.parse(line.c_str());
    }
    file.close();
    char devicesCountBuff[3];
    store(DEVICES_COUNT_CONFIG_FILE, itoa(deviceNumber, devicesCountBuff, 10));
    return devicesConfigs;
}

uint8_t SpiffsConfigurationStorage::numberOfDevices() {
    return atoi(read(DEVICES_COUNT_CONFIG_FILE));
}

void SpiffsConfigurationStorage::resetConfig() {
    if (!SPIFFS.begin(true)) {
        Log.error(MOUNTING_FAILED_MESSAGE);
        return;
    }
    SPIFFS.remove(MQTT_CONFIG_FILE);
    SPIFFS.remove(DEVICES_CONFIG_FILE);
    SPIFFS.remove(NAME_CONFIG_FILE);
}

bool SpiffsConfigurationStorage::isMqttConfigurationSet() {
    if (!SPIFFS.begin(true)) {
        Log.error(MOUNTING_FAILED_MESSAGE);
        return false;
    }
    return SPIFFS.exists(MQTT_CONFIG_FILE);
}

bool SpiffsConfigurationStorage::isDevicesConfigurationSet() {
    if (!SPIFFS.begin(true)) {
        Log.error(F(MOUNTING_FAILED_MESSAGE));
        return false;
    }
    return SPIFFS.exists(DEVICES_CONFIG_FILE);
}

void SpiffsConfigurationStorage::store(const char* filename, const char* value, bool append) {
    if (!SPIFFS.begin(true)) {
        Log.error(MOUNTING_FAILED_MESSAGE);
        return;
    }
    File file;
    if (append) {
        file = SPIFFS.open(filename, FILE_APPEND);
    } else {
        file = SPIFFS.open(filename, FILE_WRITE);
    }
    if (!file) {
        Log.error(OPENING_FILE_FAILED_MESSAGE, filename);
        return;
    }
    file.print(value);
    file.close();
}

const char* SpiffsConfigurationStorage::read(const char* filename) {
    if (!SPIFFS.begin(true)) {
        Log.error(MOUNTING_FAILED_MESSAGE);
        return "";
    }
    File file = SPIFFS.open(filename, FILE_READ);
    if (!file) {
        Log.error(OPENING_FILE_FAILED_MESSAGE, filename);
        return "";
    }
    String result = file.readString();
    char* value = new char[result.length()];
    strcpy(value, result.c_str());
    file.close();
    return value;
}