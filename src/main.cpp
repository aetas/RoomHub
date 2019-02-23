#include <Arduino.h>
#include "config/FixedDeviceConfig.hpp"


void setup() {
  Serial.begin(115200);
  
  for(int i = 0; i < 4; i++)
  {
    Serial.println(static_cast<int>(devicesConfig[i].getDeviceType()));
  }

  digitalWrite(13, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}