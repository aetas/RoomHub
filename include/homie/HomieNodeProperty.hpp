#pragma once

enum class PropertyUnit {
    CELSIUS, FAHRENHEIT, DEGREE, LITER, GALON, VOLTS, WATT, AMPERE, PERCENT, METER, FEET, PASCAL, PSI, COUNT
};

enum class PropertyDataType {
    INTEGER, FLOAT, BOOLEAN, STRING, ENUM, COLOR
};

class HomieNodeProperty {

public:
    HomieNodeProperty(const char* name, const bool _settable, const bool _retained, 
                      const PropertyUnit _unit, const PropertyDataType _dataType, const char* _format);
    ~HomieNodeProperty();
    
    const char* getName();
    const bool isSettable();
    const bool isRetained();
    const char* getUnit();
    const char* getDataType();
    const char* getFormat();

private:
    const char* name;
    const bool settable;
    const bool retained;

    const PropertyUnit unit;
    const PropertyDataType dataType;
    const char* format;
};

