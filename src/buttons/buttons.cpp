#include "buttons/buttons.hpp"
#include <Arduino.h>

void ledBlink(uint32_t delayMs, uint8_t times) {
  uint8_t state = LOW;
  for(int i = 0; i < times*2; i++) {
    if(state == LOW) {
      digitalWrite(LED_BUILTIN, HIGH);
      state = HIGH;
    } else {
      digitalWrite(LED_BUILTIN, LOW);
      state = LOW;
    }
    delay(delayMs);
  }
}

bool hasTimedButtonBeenTriggered(uint8_t buttonPin, uint16_t timePressedToTrigger) {
  uint32_t buttonFirstPressedTime = 0;
  uint8_t buttonLastState = HIGH;
  int buttonState = digitalRead(buttonPin);
  while(buttonState == LOW) {
    uint32_t now = millis();
    if (buttonLastState == HIGH) {
      buttonFirstPressedTime = now;
      buttonLastState = LOW;
    } else if(now - buttonFirstPressedTime > timePressedToTrigger) {
      return true;
    }
    delay(100);
    buttonState = digitalRead(buttonPin);
  }
  return false;
}