
#ifndef MOTORSTYRING_CLASSES_H
#define MOTORSTYRING_CLASSES_H

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 

// class SensorController {
// private:
//     VL53L0X sensorRight;
//     VL53L0X sensorLeft;
//     VL53L0X sensorFront;
//     const int XSHUT_RIGHT, XSHUT_LEFT, XSHUT_FRONT;

// public:
//     SensorController(int xshutRight, int xshutLeft, int xshutFront)
//         : XSHUT_RIGHT(xshutRight), XSHUT_LEFT(xshutLeft), XSHUT_FRONT(xshutFront) {
//         initSensors();
//     }

//     void initSensors() {
        
//         pinMode(XSHUT_LEFT, OUTPUT);
//         pinMode(XSHUT_RIGHT, OUTPUT);
//         pinMode(XSHUT_FRONT, OUTPUT);

//         digitalWrite(XSHUT_LEFT, LOW);
//         digitalWrite(XSHUT_RIGHT, LOW);
//         digitalWrite(XSHUT_FRONT, LOW);
//         delay(10);

//         initSensor(XSHUT_LEFT, sensorLeft, 0x31, "left");
//         initSensor(XSHUT_RIGHT, sensorRight, 0x30, "right");
//         initSensor(XSHUT_FRONT, sensorFront, 0x29, "front");
//     }

//     void initSensor(int xshutPin, VL53L0X& sensor, uint8_t address, const char* name) {
//         digitalWrite(xshutPin, HIGH);
//         delay(10);
//         if (!sensor.init()) {
//             Serial.print("Failed to initialize ");
//             Serial.print(name);
//             Serial.println(" sensor!");
//             while (1) {}
//         }
//         sensor.setAddress(address);
//         sensor.startContinuous();
//     }

//     int getDistanceLeft() {
//         return sensorLeft.readRangeSingleMillimeters();
//     }

//     int getDistanceRight() {
//         return sensorRight.readRangeSingleMillimeters();
//     }

//     int getDistanceFront() {
//         return sensorFront.readRangeSingleMillimeters();
//     }

//     void checkTimeouts() {
//         if (sensorLeft.timeoutOccurred()) { 
//             Serial.println(" TIMEOUT on Left Sensor");
//         }
//         if (sensorRight.timeoutOccurred()) { 
//             Serial.println(" TIMEOUT on Right Sensor");
//         }
//         if (sensorFront.timeoutOccurred()) { 
//             Serial.println(" TIMEOUT on Front Sensor");
//         }
//     }
// };

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

    void accelerateForward(int targetSpeed, int increment = 5, int delayMs = 100) {
        static int currentSpeed = 0; // Maintain current speed
        static unsigned long lastUpdateTime = 0; // Track the last update time

        unsigned long currentTime = millis();
        // Check if enough time has passed to update the speed
        if (currentTime - lastUpdateTime >= delayMs) {
            lastUpdateTime = currentTime;

            // Use a for loop to increment the speed
            for (int speed = currentSpeed; speed <= targetSpeed; speed += increment) {
                // Update motor speeds
                Serial.println("Accelerating.");
                Serial.println(speed);
                ledcWrite(pwmChannelA1, speed); // Activate motor A
                ledcWrite(pwmChannelA2, 0);      // Deactivate reverse for motor A
                ledcWrite(pwmChannelB1, speed); // Activate motor B
                ledcWrite(pwmChannelB2, 0);      // Deactivate reverse for motor B

                // Delay for a smoother acceleration
                delay(delayMs);

                // Break if we've reached the target speed
                if (speed >= targetSpeed) {
                    currentSpeed = targetSpeed; // Update currentSpeed to the target
                    Serial.println("At full speed.");
                    break; // Exit the loop once we've reached full speed
                }
            }
        }
    }



    void forward(int speed = 255) {
        accelerateForward(speed);
        setMotorSpeed(speed); // Maintain full speed
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
