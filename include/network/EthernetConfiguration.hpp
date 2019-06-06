#pragma once

#include <IPAddress.h>
#include "config/MasterConfig.hpp"

struct EthernetConfiguration {
public:
    EthernetConfiguration();
    void setMacAddress(const char* _macAddress);
    void setIpAddress(const char* _ipAddress);
    void setDnsAddress(const char* _dnsAddress);
    void setGateway(const char* _gateway);
    void setSubnetMask(const char* _subnetMask);

    const char* getMacAddress();
    IPAddress getIpAddress();
    IPAddress getDnsAddress();
    IPAddress getGateway();
    IPAddress getSubnetMask();

private:
    char* macAddress = new char[18];
    IPAddress ipAddress;
    IPAddress dnsAddress;
    IPAddress gateway;
    IPAddress subnetMask;
};
