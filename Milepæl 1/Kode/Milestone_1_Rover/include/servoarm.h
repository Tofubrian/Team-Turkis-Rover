#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 
#include <ESP32Servo.h>



class RoverArm {
private:
    // Struct to hold the servo pin configuration
    struct ServoPins {
        const int grabPin;
        const int bottomPin;
        const int rightPin;
        const int leftPin;
    };

    // Create a ServoPins struct to store pin configuration
    ServoPins pins;

    // Constants for servo PWM configuration
    const int minPulse = 500;   // Minimum pulse width (in microseconds)
    const int maxPulse = 2500;  // Maximum pulse width (in microseconds)
    const int servoFrequency = 50; // PWM frequency (50 Hz)

    // Servo objects
    Servo servoGrab; //Åben luk
    Servo servoBottom; //Rotation
    Servo servoRight; //Frem og tilbage
    Servo servoLeft; // Op og ned

public:
    // Constructor to initialize the servo pins
    RoverArm(int grabPin, int bottomPin, int rightPin, int leftPin)
        : pins{grabPin, bottomPin, rightPin, leftPin} {
        initServos();
    }

    // Function to initialize the servos
    void initServos() {
        // Attach each servo to its respective pin and set PWM properties
        servoGrab.setPeriodHertz(servoFrequency);
        servoGrab.attach(pins.grabPin, minPulse, maxPulse);

        servoBottom.setPeriodHertz(servoFrequency);
        servoBottom.attach(pins.bottomPin, minPulse, maxPulse);

        servoRight.setPeriodHertz(servoFrequency);
        servoRight.attach(pins.rightPin, minPulse, maxPulse);

        servoLeft.setPeriodHertz(servoFrequency);
        servoLeft.attach(pins.leftPin, minPulse, maxPulse);
    }

    // Function to pinch (close the grab servo)
    void pinch() {
        // Close the grab servo (move from 180 to 0 degrees)
        for (int i = 180; i > 0; i -= 3) {
            servoGrab.write(i);
            delay(20);  // Slightly longer delay to allow the servo to move
        }
    }

    // Function to open the grab servo
    void open() {
        // Open the grab servo (move from 0 to 180 degrees)
        for (int i = 0; i < 180; i += 3) {
            servoGrab.write(i);
            delay(20);  // Slightly longer delay
        }
    }
    void BottomLeft() {
        // Open the grab servo (move from 0 to 180 degrees)
        for (int i = 0; i < 180; i += 4) {
            servoBottom.write(i);
            delay(20);  // Slightly longer delay
        }
    }
    void BottomRight() {
        // Open the grab servo (move from 0 to 180 degrees)
        for (int i = 180; i > 0; i -= 4) {
            servoBottom.write(i);
            delay(20);  // Slightly longer delay
        }
    }
    void ArmForward() {
        // Open the grab servo (move from 0 to 180 degrees)
        for (int i = 180; i > 0; i -= 2) {
            servoRight.write(i);
            delay(20);  // Slightly longer delay
        }
    }
    void ArmBackward() {
        // Open the grab servo (move from 0 to 180 degrees)
        for (int i = 0; i < 180; i += 2) {
            servoRight.write(i);
            delay(20);  // Slightly longer delay
        }
    }
     void ArmUp() {
        // Open the grab servo (move from 0 to 180 degrees)
        for (int i = 180; i > 0; i -= 3) {
            servoLeft.write(i);
            delay(20);  // Slightly longer delay
        }
    }
    void ArmDown() {
        // Open the grab servo (move from 0 to 180 degrees)
        for (int i = 0; i < 180; i += 2) {
            servoLeft.write(i);
            delay(20);  // Slightly longer delay
        }
    }
};
