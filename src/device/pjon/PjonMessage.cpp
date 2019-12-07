#include "device/pjon/PjonMessage.hpp"
#include <WString.h>
#include <stdlib.h>

PjonMessage PjonMessage::fromString(const char* stringMessage) {
    return PjonMessage(parse(stringMessage));
}

PjonMessage::PjonMessage(const char** _tokens): tokens(_tokens) {
}

const char* PjonMessage::getType() {
    return tokens[0];
}

const char** PjonMessage::getValues() {
    return tokens + 1;
}

PjonMessage::~PjonMessage() {
    delete[] tokens;
}

const char** PjonMessage::parse(const char* stringMessage) {
    
    const char** result = new const char*[MAX_TOKENS_IN_MESSAGE];
    int i = 0;
    char* messageDup = strdup(stringMessage);
    char* token = strtok(messageDup, PJON_MESSAGE_TOKEN_SEPARATOR);
    
    while (token != NULL) {
        result[i++] = token;
        token = strtok(NULL, PJON_MESSAGE_TOKEN_SEPARATOR);
    }

    return result;
}