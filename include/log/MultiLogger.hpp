#pragma once

#include <Print.h>


class MultiLogger: public Print {

public:
  MultiLogger(Print* _targets[], int _targetsNumber) : targets(_targets), targetsNumber(_targetsNumber) {};

  size_t write(uint8_t character) {
    size_t lastValue = 0;
    for(int i = 0; i < targetsNumber; i++)
    {
      lastValue = targets[i]->write(character);
    }
    return lastValue;
  }

private:
  Print** targets;
  int targetsNumber;
};
