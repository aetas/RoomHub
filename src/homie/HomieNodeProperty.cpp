#include "homie/HomieNodeProperty.hpp"

HomieNodeProperty::HomieNodeProperty(const char* _name, const bool _settable, const bool _retained, 
                                     const PropertyUnit _unit, const PropertyDataType _dataType, const char* _format)
    : name(_name), settable(_settable), retained(_retained), unit(_unit), dataType(_dataType), format(_format) {}

HomieNodeProperty::~HomieNodeProperty() {

}

const char* HomieNodeProperty::getName() {
    return name;
}

const bool HomieNodeProperty::isSettable() {
    return settable;
}
const bool HomieNodeProperty::isRetained() {
    return retained;
}
const char* HomieNodeProperty::getUnit() {
    switch(unit) {
        case PropertyUnit::COUNT: return "#";
        case PropertyUnit::DEGREE : return "*";
        case PropertyUnit::CELSIUS : return "C";
        case PropertyUnit::FAHRENHEIT : return "F";
        case PropertyUnit::LITER: return "L";
        case PropertyUnit::GALON: return "gal";
        case PropertyUnit::VOLTS: return "V";
        case PropertyUnit::WATT: return "W";
        case PropertyUnit::AMPERE: return "A";
        case PropertyUnit::PERCENT: return "%";
        case PropertyUnit::METER: return "m";
        case PropertyUnit::FEET: return "ft";
        case PropertyUnit::PASCAL: return "Pa";
        case PropertyUnit::PSI: return "psi";
        case PropertyUnit::NONE: return "";
        default: return "";
    }
}
const char* HomieNodeProperty::getDataType() {
    switch(dataType) {
        case PropertyDataType::INTEGER: return "integer";
        case PropertyDataType::FLOAT: return "float";
        case PropertyDataType::BOOLEAN: return "boolean";
        case PropertyDataType::STRING: return "string";
        case PropertyDataType::ENUM: return "enum";
        case PropertyDataType::COLOR: return "color";
        default: return "UNKNOWN";
    }
}
const char* HomieNodeProperty::getFormat() { 
    return format;
}