#pragma once

#include <inttypes.h>

class Uptime {
public:
    uint32_t uptimeSec(const uint32_t& currentTimeMs) {
        if (currentTimeMs < lastMillis) {
            rollovers++;
        }
        lastMillis = currentTimeMs;
        return (0xFFFFFFFF / 1000 ) * rollovers + (lastMillis / 1000);
    };

private:
    uint16_t rollovers = 0;
    uint32_t lastMillis = 0;
};