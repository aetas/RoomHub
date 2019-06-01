#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "EthernetConfiguration.hpp"

class SerialEthernetConfigurator {
public:
    void configureBySerial(Stream& serial);
    const EthernetConfiguration getConfiguration();

private:
    char* readValue(Stream& serial);
    EthernetConfiguration ethConfig;
};

const EthernetConfiguration SerialEthernetConfigurator::getConfiguration() {
    return ethConfig;
}

char* SerialEthernetConfigurator::readValue(Stream& serial) {
    while (true) {
        if(serial.available() > 0) {
            String receivedString = serial.readStringUntil('\n');
            char* receivedValue = new char[receivedString.length()]();
            strcpy(receivedValue, receivedString.c_str());
            return receivedValue;
        }
    }
}

void SerialEthernetConfigurator::configureBySerial(Stream& serial) {
    Log.notice(F("Configuration through SERIAL. Waiting for commands..."));
    
    serial.print("MAC address: ");
    ethConfig.macAddress = readValue(serial);
    serial.println(ethConfig.macAddress);
    
    serial.print("IP address: ");
    ethConfig.ipAddress = readValue(serial);
    serial.println(ethConfig.ipAddress);

    serial.print("DNS (optional): ");
    ethConfig.dnsAddress = readValue(serial);
    serial.println(ethConfig.dnsAddress);

    serial.print("Gateway (optional): ");
    ethConfig.gateway = readValue(serial);
    serial.println(ethConfig.gateway);
    
    serial.print("Subnet mask (optional): ");
    ethConfig.subnetMask = readValue(serial);
    serial.println(ethConfig.subnetMask);
}