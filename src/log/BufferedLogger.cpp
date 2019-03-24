#include "log/BufferedLogger.hpp"

BufferedLogger::BufferedLogger(const uint16_t _bufferSize): bufferSize(_bufferSize) {
    buffer = new char[_bufferSize];
}

BufferedLogger::~BufferedLogger() {
    delete[] buffer;
}

size_t BufferedLogger::write(uint8_t character) {

    if (bufferCurrentSize < bufferSize) {
        buffer[bufferCurrentSize] = character;
        bufferCurrentSize++;
        if (character != '%') {
            return 1;
        }
    } else {
        bufferOverriden = true;
        clearBuffer();
        write(character);
    }
    return 0;
}

void BufferedLogger::clearBuffer() {
    this->bufferCurrentSize = 0;
}

int BufferedLogger::getBufferSize() {
    return bufferCurrentSize + 1;
}

bool BufferedLogger::read(char buf[]) {
    for (int i = 0; i < bufferCurrentSize; i++) {
        buf[i] = buffer[i];
    }
    buf[bufferCurrentSize] = '\0';
    clearBuffer();
    bool bufferOverridenWhenRead = bufferOverriden;
    bufferOverriden = false;
    return bufferOverridenWhenRead;
}