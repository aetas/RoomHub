#pragma once

struct EthernetConfiguration {
public:
    const char* macAddress;
    const char* ipAddress;
    const char* dnsAddress = "";
    const char* gateway = "";
    const char* subnetMask = "";
};
