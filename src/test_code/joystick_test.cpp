#include <Arduino.h>
#include "pinout.h"
#include "joystick.h"

JoystickReading joystick;

void setup() {
    Serial.begin();

    setupJoystick();
}

void loop() {
    joystick = readJoystick();
    Serial.printf("X: %d, Y: %d\n", joystick.x, joystick.y);
    
    delay(50);
}
