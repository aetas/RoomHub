#include "network/EthernetConfiguration.hpp"

EthernetConfiguration::EthernetConfiguration() {
    #ifdef USE_ETHERNET
    strcpy(macAddress, ETHERNET_MAC);
    ipAddress.fromString(ETHERNET_IP);
    #endif
};

void EthernetConfiguration::setMacAddress(const char* _macAddress) { 
    strcpy(macAddress, _macAddress); 
};

void EthernetConfiguration::setIpAddress(const char* _ipAddress) {
    ipAddress.fromString(_ipAddress);
};

void EthernetConfiguration::setDnsAddress(const char* _dnsAddress) { 
    if (strcmp(_dnsAddress, "") == 0) { // default value
        dnsAddress = ipAddress;
        dnsAddress[3] = 1;
    } else {
        dnsAddress.fromString(_dnsAddress);
    }
};

void EthernetConfiguration::setGateway(const char* _gateway) {
    if (strcmp(_gateway, "") == 0) { // default value
        gateway = ipAddress;
    } else {
        gateway.fromString(_gateway);
    }
};

void EthernetConfiguration::setSubnetMask(const char* _subnetMask) {
    if (strcmp(_subnetMask, "") == 0) { // default value
        IPAddress subnet(255, 255, 255, 0);
        subnetMask = subnet;
    } else {
        subnetMask.fromString(_subnetMask);
    }
}


const char* EthernetConfiguration::getMacAddress() { return macAddress; };
IPAddress EthernetConfiguration::getIpAddress() { return ipAddress; };
IPAddress EthernetConfiguration::getDnsAddress() { return dnsAddress; };
IPAddress EthernetConfiguration::getGateway() { return gateway; };
IPAddress EthernetConfiguration::getSubnetMask() { return subnetMask; };