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
    // Log.trace(F("Reading stored devices configuration..." CR));
    while (String line = file.readStringUntil('\n')) {
        if (line == nullptr) {
            // Log.trace(F("End of devices file" CR));
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

void SpiffsConfigurationStorage::storeEthernetConfig(const char* ethernetConfigString) {
    store(ETHERNET_CONFIG_FILE, ethernetConfigString);
}

EthernetConfiguration SpiffsConfigurationStorage::readEthernetConfiguration() {
    EthernetConfiguration ethConfig;
    if (!SPIFFS.begin(true)) {
        Log.error(MOUNTING_FAILED_MESSAGE);
        return ethConfig;
    }
    File file = SPIFFS.open(ETHERNET_CONFIG_FILE, FILE_READ);
    if (!file) {
        Log.warning(F("Ethernet configuration file not found. Using default Ethernet configuration values."));
        return ethConfig;
    }

    Log.notice(F("Reading ethernet configuration..." CR));
    ethConfig.setMacAddress(file.readStringUntil(';').c_str());
    Log.notice(F("MAC address: %s" CR), ethConfig.getMacAddress());
    ethConfig.setIpAddress(file.readStringUntil(';').c_str());
    Log.notice(F("IP address: %s" CR), ethConfig.getIpAddress().toString().c_str());
    ethConfig.setDnsAddress(file.readStringUntil(';').c_str());
    // Log.trace(F("DNS address: %s" CR), ethConfig.getDnsAddress().toString().c_str());
    ethConfig.setGateway(file.readStringUntil(';').c_str());
    // Log.trace(F("Gateway: %s" CR), ethConfig.getGateway().toString().c_str());
    ethConfig.setSubnetMask(file.readStringUntil(';').c_str());
    // Log.trace(F("Subnet mask: %s" CR), ethConfig.getSubnetMask().toString().c_str());

    file.close();
    return ethConfig;
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

void SpiffsConfigurationStorage::resetEthernetConfig() {
    if (!SPIFFS.begin(true)) {
        Log.error(MOUNTING_FAILED_MESSAGE);
        return;
    }
    SPIFFS.remove(ETHERNET_CONFIG_FILE);
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

bool SpiffsConfigurationStorage::isEthernetConfigurationSet() {
    if (!SPIFFS.begin(true)) {
        Log.error(F(MOUNTING_FAILED_MESSAGE));
        return false;
    }
    return SPIFFS.exists(ETHERNET_CONFIG_FILE);
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