#pragma once

#include <Print.h>

class BufferedLogger : public Print {
private:
  char* buffer;
  uint16_t bufferSize;
  uint16_t bufferCurrentSize = 0;
  bool bufferOverriden = false;
  void clearBuffer();
public:
  BufferedLogger(const uint16_t _bufferSize);
  ~BufferedLogger();
  virtual size_t write(uint8_t character);
  int getBufferSize();
  bool read(char buf[]);
};
