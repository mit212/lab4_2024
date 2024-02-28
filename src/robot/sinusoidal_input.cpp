#include <Arduino.h>
#include "PID.h"
#include "SimpleFilters.h"
#include "EncoderVelocity.h"
#include "pinout.h"
#include "util.h"
#include "MotorDriver.h"
#include "potentiometer.h"

//#define SerialMonitor
#define MatlabPlot

//#define MOTOR1
#define MOTOR2

#ifdef MOTOR1
    // TODO: Put your gains here!
    #define Ti1 0.0183
    #define Td1 0.0021
    #define Kp1 9.36
    #define alpha1 10
    MotorDriver motor1(DIR1, PWM1, 0);  
    EncoderVelocity encoder(ENCODER1_A_PIN, ENCODER1_B_PIN, CPR_60_RPM, 0.2);
    LeadLagFilter leadLag1(alpha1, Td1, Ti1);
    double setpoint1 = 0;
    double position1 = 0;
    double controlEffort1 = 0;
    
    #define MAX_FREQ_1 10.0 //rad/s
    #define MAX_AMPLITUDE_1 M_PI/8 //rad
    double freq1 = MAX_FREQ_1/2;
    double amplitude1 = MAX_AMPLITUDE_1/4;
#endif

#ifdef MOTOR2
    // TODO: Put your gains here!
    #define Ti2 0.0275
    #define Td2 0.0032
    #define Kp2 10
    #define alpha2 1
    MotorDriver motor2(DIR2, PWM2, 1);  
    EncoderVelocity encoder(ENCODER2_A_PIN, ENCODER2_B_PIN, CPR_60_RPM, 0.2);
    LeadLagFilter leadLag2(alpha2, Td2, Ti2);
    double setpoint2 = 0;
    double position2 = 0;
    double controlEffort2 = 0;

    #define MAX_FREQ_2 15 //rad/s
    #define MAX_AMPLITUDE_2 M_PI/4 //rad
    double freq2 = MAX_FREQ_2/2;
    double amplitude2 = MAX_AMPLITUDE_2/6;

#endif

PotReading potReading;

void setup() {
    #ifdef MOTOR1
        motor1.setup();
    #endif
    #ifdef MOTOR2
        motor2.setup();
    #endif
    setupPot();
    Serial.begin(); 
}

void loop() {
    // Update sinusiodal setpoint at 2kHz
    EVERY_N_MICROS(500) {
        #ifdef MOTOR1
            setpoint1 = amplitude1*sin(freq1*millis()/1000.0);
        #endif
        #ifdef MOTOR2
            setpoint2 = amplitude2*sin(freq2*millis()/1000.0);
        #endif
    }

    //update PID at 5khz
    EVERY_N_MICROS(200) {
        #ifdef MOTOR1
            position1 = encoder.getPosition();
            controlEffort1 = Kp1*leadLag1.calculate(setpoint1-position1);
            motor1.drive(controlEffort1);
        #endif
        #ifdef MOTOR2
            position2 = -encoder.getPosition();
            controlEffort2 = Kp2*leadLag2.calculate(setpoint2-position2);
            motor2.drive(controlEffort2);
        #endif
    }

    // Update gains at 2Hz
    EVERY_N_MICROS(500) {
        potReading = readPot();
        double alpha = potReading.x * 10;
        double Td = potReading.y * 500;
        double Ti = potReading.z * 10;
        leadLag2.setParameters(alpha, Td, Ti);
    }


    // Print values at 50Hz
    EVERY_N_MILLIS(20) {
            // Print values to serial monitor
            #ifdef SerialMonitor
            // Print values to serial monitor
            #ifdef MOTOR1
                Serial.printf("Setpoint (rad): %.2f, Position (rad): %.2f, Control Effort: %.2f\n",
                          setpoint1, position1, controlEffort1);
            #endif
            #ifdef MOTOR2
                Serial.printf("Setpoint (rad): %.2f, Position (rad): %.2f, Control Effort: %.2f\n",
                          setpoint2, position2, controlEffort2);
            #endif
            #endif

            #ifdef MatlabPlot
                #ifdef MOTOR1
                    Serial.printf("%.3f\t%.3f\t%.3f\n", millis()/1000.0, setpoint1, position1);
                #endif
                #ifdef MOTOR2
                    Serial.printf("%.3f\t%.3f\t%.3f\n", millis()/1000.0, setpoint2, position2);
                #endif  
            #endif
        }
}
