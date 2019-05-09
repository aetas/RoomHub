#pragma once

#include "stdint.h"

void ledBlink(uint32_t delayMs, uint8_t times);
bool hasTimedButtonBeenTriggered(uint8_t buttonPin, uint16_t timePressedToTrigger);