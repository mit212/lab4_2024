# Lab 4: PID Tuning and Wireless Comms

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

- [Lab 4: PID Tuning and Wireless Comms](#lab-4-pid-tuning-and-wireless-comms)
  - [1 Validate Hardware Setup](#1-validate-hardware-setup)
    - [1.1 Validate Microcontroller](#11-validate-microcontroller)
    - [1.2 Validate Motors](#12-validate-motors)
    - [1.3 Validate Encoders](#13-validate-encoders)
    - [1.4 Validate Joystick](#14-validate-joystick)
  - [2 Potentiometers](#2-potentiometers)
    - [2.1 Wire Potentiometers](#21-wire-potentiometers)
    - [2.2 Read Potentiometers](#22-read-potentiometers)
  - [3 Tune PID Using Potentiometers](#3-tune-pid-using-potentiometers)
    - [3.1 Constant Setpoint](#31-constant-setpoint)
    - [3.2 Step Response in Joint Space](#32-step-response-in-joint-space)
  - [4 Joystick Control](#4-joystick-control)
  - [5 Make It Wireless!](#5-make-it-wireless)
  - [6 are there other sensors we want to expose them to in this lab?](#6-are-there-other-sensors-we-want-to-expose-them-to-in-this-lab)
  - [7 Feedback Form](#7-feedback-form)

## 1 Validate Hardware Setup
Estimated time of completion: 10 min

Like in the previous labs, we first want to make sure the parts work individually! Faulty wiring or hardware can be very difficult to debug in complex systems.

### 1.1 Validate Microcontroller

**Make sure that motor power is turned off any time you are uploading code to your microcontroller.** The arm has a tendency to spin around and hit itself if motor power is on during upload. As a reminder, motor power should only be on when you expect the motors to move. Otherwise, please keep motor power off. 

<details> <summary> <i> How to know if the motor power is on? </i> </summary>

The yellow LED on the motor driver indicates whether motor power is on or off.
</details>

Clone this repository and run `robot/blink_test.cpp`. You should see the onboard LED change colors! 

<details> <summary> <i> Forget how to clone? </i> </summary>

Please refer to the [instructions from Lab 1](
https://github.com/mit212/lab1_2024?tab=readme-ov-file#31-git-clone).

</details>

### 1.2 Validate Motors

Orient the arm straight up, in default starting position. Run `test_code/motor_drive_test.cpp` to validate your motor setup. You should see both motors oscillating back and forth. Remember, motor 1 is attached to the base and motor 2 is attached to the second link. 

### 1.3 Validate Encoders

Run `test_code/encoder_test.cpp` to validate your encoder setup. Open the Serial Monitor to see the output and confirm that both the direction and the magnitude make sense!

### 1.4 Validate Joystick

Run `lab_code/joystick.cpp` and `test_code/joystick_test.cpp` to validate your joystick setup. **This means you should move both files into the `robot/` directory.** You should be able to see joystick readings within the range `[-1, 1]`.

## 2 Potentiometers
Estimated time of completion: 25 min

### 2.1 Wire Potentiometers

We will be using potentiometers to quickly and easily tune our PID controller without having to constantly reupload code. First, please wire 3 potentiometers to your microcontroller.

<details>
    <summary><i> What is a potentiometer?</i>
    </summary>
  A potentiometer is an electrical component that functions as a variable resistor or a voltage divider. It consists of a resistive element, such as a carbon track, and a movable wiper contact that slides along the element. By moving the wiper, you can change the resistance between the wiper and each end of the track, which allows you to adjust the level of current flowing through a circuit, or to change the voltage at the wiper, which can be used to control various devices such as the volume on a radio or the position of a servo motor in robotics.
  </details>

### 2.2 Read Potentiometers
Complete the `TODO`s in `include/pinout.h`, `include/potentiometer.h` and `lab_code/potentiometer.cpp`. To validate your code, run `lab_code/potentiometer.cpp` and `test_code/potentiometer_test.cpp`.

## 3 Tune PID Using Potentiometers
Estimated time of completion: 20 min

We will be using the file `lab_code/pid_tune.cpp` to tune our PID controller.

### 3.1 Constant Setpoint
First, define the setpoint to be `(M_PI/2, 0)` in joint space by uncommenting `#define Constant` and commenting out `#define SquareWave`. Then, use the potentiometers to change the PID gains. If your PID controller is properly tuned and you disturb the arm in any direction, the arm should quickly return to the setpoint `(M_PI/2, 0)` with minimal overshoot, oscillations, and steady state error. You can validate the response by running `matlab/PIDSerialRead.m`.

### 3.2 Step Response in Joint Space
Once the PID controller is properly tuned to follow a constant setpoint, the next step is to follow a square wave in joint space by commenting out `#define Constant` and uncommenting `#define SquareWave`. Once again, the step response should have minimal overshoot, oscillations, and steady state error.

## 4 Joystick Control
Estimated time of completion: 10 min

Open `drawing.cpp` and update gains. Then run it with joystick control, see if that works better than last lab.

## 5 Make It Wireless!

Rewire so that joystick on a separate system
Enable wireless comms code

## 6 are there other sensors we want to expose them to in this lab?

## 7 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback. 

| :white_check_mark: CHECKOFF X :white_check_mark:   |
|:---------------------------------------------------|
| Show the feedback form completion screen to a TA or LA. |


[^1]: Version 1 - 2020: Dr. Harrison Chin  
  Version 2 - 2021: Phillip Daniel  
  Version 3 - 2023: Ravi Tejwani and Kentaro Barhydt  
  Version 4 - 2024: Jinger Chong, Josh Sohn
