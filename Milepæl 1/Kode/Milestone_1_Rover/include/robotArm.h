#include <Arduino.h>
#include <ESP32Servo.h>
#include <receiver.h>

#pragma once

// Pin defintion for servos on arm
// Servo objects
Servo baseServo;
Servo joint1Servo;
Servo joint2Servo;
Servo grabServo;

// Servo pin definitions
const int baseServoPin = 23;
const int joint1ServoPin = 32;
const int joint2ServoPin = 33;
const int grabServoPin = 19;

// Variable to store positions of servos, also sets starting positions for servos
int currentBasePosition = 150;
int currentJoint1Position = 120;
int currentJoint2Position = 90;
int currentGrabPosition = 120;

// Constants for servo angles
const int BASE_MIN_ANGLE = 30;
const int BASE_MAX_ANGLE = 150;
const int JOINT1_MIN_ANGLE = 80;
const int JOINT1_MAX_ANGLE = 150;
const int JOINT2_MIN_ANGLE = 70;
const int JOINT2_MAX_ANGLE = 120;
const int GRAB_MIN_ANGLE = 80;
const int GRAB_MAX_ANGLE = 160;

// Movement speed
const int SERVO_STEP_SIZE = 2;  // Increment/decrement step size for movement

// Joystick dead zone
const int JOYSTICK_CENTER_MIN = 1600;
const int JOYSTICK_CENTER_MAX = 2100;

// // Variables
// bool toggleServos = false;  // Tracks which servos to control
// bool lastClickState = HIGH; // Debounce helper for joystick button


void moveServos() {
    // Get joystick values
    int leftValueX = myJoystick.positionX;
    int leftValueY = myJoystick.positionY;
    int rightValueX = myJoystick.positionXmotor;
    int rightValueY = myJoystick.positionYmotor;

    // Debugging: Print joystick values
    Serial.print("Left Joystick X: "); Serial.println(leftValueX);
    Serial.print("Left Joystick Y: "); Serial.println(leftValueY);
    Serial.print("Right Joystick X: "); Serial.println(rightValueX);
    Serial.print("Right Joystick Y: "); Serial.println(rightValueY);

    // Control Base with Left Joystick X (leftValueX)
    if (leftValueX < JOYSTICK_CENTER_MIN) {
        currentBasePosition = max(currentBasePosition - SERVO_STEP_SIZE, BASE_MIN_ANGLE);
    }
    else if (leftValueX > JOYSTICK_CENTER_MAX) {
        currentBasePosition = min(currentBasePosition + SERVO_STEP_SIZE, BASE_MAX_ANGLE);
    }
    baseServo.write(currentBasePosition);
    Serial.print("Base Position: "); Serial.println(currentBasePosition);

    // Control Joint1 with Left Joystick Y (leftValueY)
    if (leftValueY < JOYSTICK_CENTER_MIN) {
        currentJoint1Position = max(currentJoint1Position - SERVO_STEP_SIZE, JOINT1_MIN_ANGLE);
    }
    else if (leftValueY > JOYSTICK_CENTER_MAX) {
        currentJoint1Position = min(currentJoint1Position + SERVO_STEP_SIZE, JOINT1_MAX_ANGLE);
    }
    joint1Servo.write(currentJoint1Position);
    Serial.print("Joint1 Position: "); Serial.println(currentJoint1Position);

    // Control Joint2 with Right Joystick X (rightValueX)
    if (rightValueX < JOYSTICK_CENTER_MIN) {
        currentJoint2Position = max(currentJoint2Position - SERVO_STEP_SIZE, JOINT2_MIN_ANGLE);
    }
    else if (rightValueX > JOYSTICK_CENTER_MAX) {
        currentJoint2Position = min(currentJoint2Position + SERVO_STEP_SIZE, JOINT2_MAX_ANGLE);
    }
    joint2Servo.write(currentJoint2Position);
    Serial.print("Joint2 Position: "); Serial.println(currentJoint2Position);

    // Control Grab with Right Joystick Y (rightValueY)
    if (rightValueY < JOYSTICK_CENTER_MIN) {
        currentGrabPosition = max(currentGrabPosition - SERVO_STEP_SIZE, GRAB_MIN_ANGLE);
    }
    else if (rightValueY > JOYSTICK_CENTER_MAX) {
        currentGrabPosition = min(currentGrabPosition + SERVO_STEP_SIZE, GRAB_MAX_ANGLE);
    }
    grabServo.write(currentGrabPosition);
    Serial.print("Grab Position: "); Serial.println(currentGrabPosition);

    // Optional: Delay to manage servo movement smoothness
    delay(20);
}


void robotArmSetup() {
    // Set hertz for the servos
    baseServo.setPeriodHertz(50);
    joint1Servo.setPeriodHertz(50);
    joint2Servo.setPeriodHertz(50);
    grabServo.setPeriodHertz(50);

    // Attach servos
    baseServo.attach(baseServoPin);
    joint1Servo.attach(joint1ServoPin);
    joint2Servo.attach(joint2ServoPin);
    grabServo.attach(grabServoPin);

    // Initialize servos to center position
    baseServo.write(currentBasePosition);
    joint1Servo.write(currentJoint1Position);
    joint2Servo.write(currentJoint2Position);
    grabServo.write(currentGrabPosition);
}

