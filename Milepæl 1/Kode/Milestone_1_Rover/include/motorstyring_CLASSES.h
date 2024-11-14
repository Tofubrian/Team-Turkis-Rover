
#ifndef MOTORSTYRING_CLASSES_H
#define MOTORSTYRING_CLASSES_H

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 

class MotorController {
private:
    struct MotorPins {
        const int pinA1, pinA2, pinB1, pinB2;
    };

    MotorPins pins;
    const int pwmFreq = 1000;  // PWM frequency in Hz (1 kHz)
    const int pwmResolution = 8;  // 8-bit resolution
    const int pwmChannelA1 = 0;  // PWM channel for motor A, pin A1
    const int pwmChannelA2 = 1;  // PWM channel for motor A, pin A2
    const int pwmChannelB1 = 2;  // PWM channel for motor B, pin B1
    const int pwmChannelB2 = 3;  // PWM channel for motor B, pin B2
    
public:
    MotorController(int pinA1, int pinA2, int pinB1, int pinB2)
        : pins{pinA1, pinA2, pinB1, pinB2} {
        initMotors();
    }

    void initMotors() {
        // Set up PWM channels for each motor pin
        ledcSetup(pwmChannelA1, pwmFreq, pwmResolution);
        ledcSetup(pwmChannelA2, pwmFreq, pwmResolution);
        ledcSetup(pwmChannelB1, pwmFreq, pwmResolution);
        ledcSetup(pwmChannelB2, pwmFreq, pwmResolution);

        // Attach the motor pins to the respective PWM channels
        ledcAttachPin(pins.pinA1, pwmChannelA1);
        ledcAttachPin(pins.pinA2, pwmChannelA2);
        ledcAttachPin(pins.pinB1, pwmChannelB1);
        ledcAttachPin(pins.pinB2, pwmChannelB2);
    }

    void setMotorSpeed(int speed) {
        ledcWrite(pwmChannelA1, speed); // Activate motor A
        ledcWrite(pwmChannelA2, 0);     // Deactivate reverse for motor A
        ledcWrite(pwmChannelB1, speed); // Activate motor B
        ledcWrite(pwmChannelB2, 0);     // Deactivate reverse for motor B
    }

    void forward(int speed = 255) {
        ledcWrite(pwmChannelA1, speed);     // Forward motor A
        ledcWrite(pwmChannelA2, 0); // Deactivate forward A
        ledcWrite(pwmChannelB1, speed);     // Forward motor B
        ledcWrite(pwmChannelB2, 0); // Deactivate forward B

        Serial.println("Moving forward");
    }

    void backward(int speed = 255) {
        ledcWrite(pwmChannelA1, 0);     // Deactivate forward
        ledcWrite(pwmChannelA2, speed); // Activate reverse for motor A
        ledcWrite(pwmChannelB1, 0);     // Deactivate forward
        ledcWrite(pwmChannelB2, speed); // Activate reverse for motor B
        Serial.println("Moving back");
    }

    void stop() {
        ledcWrite(pwmChannelA1, 0);
        ledcWrite(pwmChannelA2, 0);
        ledcWrite(pwmChannelB1, 0);
        ledcWrite(pwmChannelB2, 0);
        Serial.println("Stopping motors");
    }

    void turnRight(int speed = 255) {
        ledcWrite(pwmChannelA1, speed); // Forward A
        ledcWrite(pwmChannelA2, 0);     // Deactivate reverse A
        ledcWrite(pwmChannelB1, 0);     // Deactivate forward B
        ledcWrite(pwmChannelB2, speed); // Reverse B
        Serial.println("Turning Right");
    }

    void turnLeft(int speed = 255) {
        ledcWrite(pwmChannelA1, 0);     // Deactivate forward A
        ledcWrite(pwmChannelA2, speed); // Reverse A
        ledcWrite(pwmChannelB1, speed); // Forward B
        ledcWrite(pwmChannelB2, 0);     // Deactivate reverse B
        Serial.println("Turning Left");
    }

    void turnSmoothRight(int speed = 255, int halfSpeed = 112) {
        ledcWrite(pwmChannelA1, halfSpeed);
        ledcWrite(pwmChannelA2, 0);
        ledcWrite(pwmChannelB1, speed);
        ledcWrite(pwmChannelB2, 0);
    }

    void turnSmoothLeft(int speed = 255, int halfSpeed = 112) {
    ledcWrite(pwmChannelA1, speed);
    ledcWrite(pwmChannelA2, 0);
    ledcWrite(pwmChannelB1, halfSpeed);
    ledcWrite(pwmChannelB2, 0);
    }

    void backwardSmoothRight(int speed = 255, int halfSpeed = 112) {
    ledcWrite(pwmChannelA1, 0);     // Deactivate forward
    ledcWrite(pwmChannelA2, halfSpeed); // Activate reverse for motor A
    ledcWrite(pwmChannelB1, 0);     // Deactivate forward
    ledcWrite(pwmChannelB2, speed); // Activate reverse for motor B
    Serial.println("Moving back");
    }
    
    void backwardSmoothLeft(int speed = 255, int halfSpeed = 112) {
    ledcWrite(pwmChannelA1, 0);     // Deactivate forward
    ledcWrite(pwmChannelA2, speed); // Activate reverse for motor A
    ledcWrite(pwmChannelB1, 0);     // Deactivate forward
    ledcWrite(pwmChannelB2, halfSpeed); // Activate reverse for motor B
    Serial.println("Moving back");
    }

    void forwardSaveRight() {
        backward();
        delay(700);
        turnRight();
        delay(1000);
    }

    void forwardSaveLeft() {
        backward();
        delay(700);
        turnLeft();
        delay(1000);
    }
};

#endif // MOTORSTYRING_CLASSES_H
