#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 
#include <ESP32Servo.h>


class RoverArm {
public:
    // Initialiserer servoerne og knytter dem til deres pins
    void begin();

private:
    // Servo objekter
    Servo servoGrab;
    Servo servoBottom;
    Servo servoRight;
    Servo servoLeft;

    // Pin-konfigurationer til hver servo
    const int grabPin = 17;
    const int bottomPin = 18;
    const int rightPin = 5;
    const int leftPin = 16;

    // Pulslængde grænser
    const int minPulse = 500;
    const int maxPulse = 2500;
    const int servoFrequency = 50; // 50 Hz
};