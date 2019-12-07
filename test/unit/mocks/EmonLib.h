#pragma once

class EnergyMonitor {
public:
    void current(unsigned int _inPinI, double _ICAL) {};
    double calcIrms(unsigned int Number_of_Samples) { return 1; };
}; 