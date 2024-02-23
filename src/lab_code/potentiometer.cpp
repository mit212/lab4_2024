#include "potentiometer.h"
#include <Arduino.h>

void setupPot() {
    // TODO: Declare the potentiometer pins as INPUT. This should only take two lines.
    // Refer to `lab_code/joystick.cpp` if needed.
    pinMode(POT1, INPUT); 
    pinMode(POT2, INPUT);
    pinMode(POT3, INPUT);
}

PotReading readPot() {
    // TODO: Use analogRead to get the potentiometer inputs and update the output struct.
    // Refer to `lab_code/joystick.cpp` if needed.
    PotReading output;
    
    output.x = analogRead(POT1)/4096.0; 
    output.y = analogRead(POT2)/4096.0; 
    output.z = analogRead(POT3)/4096.0; 

    return output;
}
