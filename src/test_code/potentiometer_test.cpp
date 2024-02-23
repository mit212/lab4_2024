#include <Arduino.h>
#include "pinout.h"
#include "potentiometer.h"

PotReading pot;

void setup() {
    Serial.begin();

    setupPot();
}

void loop() {
    pot = readPot();
    Serial.printf("Pot1: %.2f  Pot2: %.3f  Pot3: %.3f\n", pot.x, pot.y, pot.z);
    
    delay(50);
}
