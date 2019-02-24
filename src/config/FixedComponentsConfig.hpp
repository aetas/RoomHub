#include <Adafruit_MCP23017.h>
#include <CD74HC4067.h>

#define EXPANDERS_NUMBER 4
#define MUX_COMMON_PIN 36
#define MUX_S0 27
#define MUX_S1 26
#define MUX_S2 33
#define MUX_S3 32

Adafruit_MCP23017* expanders[EXPANDERS_NUMBER];

CD74HC4067* mux = new CD74HC4067(MUX_S0, MUX_S1, MUX_S2, MUX_S3);

void setupComponents() {

    for(uint8_t i = 0; i < EXPANDERS_NUMBER; i++) {
        expanders[i] = new Adafruit_MCP23017();
        expanders[i]->begin(i);
    }

    pinMode(MUX_COMMON_PIN, INPUT);
}





    
    
    