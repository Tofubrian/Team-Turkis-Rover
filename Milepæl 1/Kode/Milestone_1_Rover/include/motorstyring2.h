#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 

// #define A1 25  // Motor A pins
// #define A2 26 //
// #define B1 14 // Motor B pins
// #define B2 12
// #define sensorRight 16 // Time of flight sensor

// VL53L0X sensor; // Variabel til sensor



int incomingByte = 0; // for incoming serial data

// Struct setup for motor pins
struct hbro {
    const int motorPinA1; // Motor A tilbage 
    const int motorPinA2; // Motor A frem 
    const int motorPinB1; // Motor B tilbage
    const int motorPinB2; // Motor B frem
};

// Funktion til at initialisere motorer
void initMotors(hbro motorPins) {
    pinMode(motorPins.motorPinA1, OUTPUT);
    pinMode(motorPins.motorPinA2, OUTPUT);
    pinMode(motorPins.motorPinB1, OUTPUT);
    pinMode(motorPins.motorPinB2, OUTPUT);
}

// Motorstyringsfunktioner
void forward(hbro motorPins) {
    digitalWrite(motorPins.motorPinA1, LOW);
    analogWrite(motorPins.motorPinA2, 255);
    digitalWrite(motorPins.motorPinB1, LOW);
    analogWrite(motorPins.motorPinB2, 255);
}

void backward(hbro motorPins) {
    analogWrite(motorPins.motorPinA1, 255);
    digitalWrite(motorPins.motorPinA2, LOW);
    analogWrite(motorPins.motorPinB1, 255);
    digitalWrite(motorPins.motorPinB2, LOW);
}

void stop(hbro motorPins) {
    digitalWrite(motorPins.motorPinA1, LOW);
    digitalWrite(motorPins.motorPinA2, LOW);
    digitalWrite(motorPins.motorPinB1, LOW);
    digitalWrite(motorPins.motorPinB2, LOW);
}

void turnRight(hbro motorPins) {
    analogWrite(motorPins.motorPinA1, 225);  
    digitalWrite(motorPins.motorPinA2, LOW);
    digitalWrite(motorPins.motorPinB1, LOW);
    analogWrite(motorPins.motorPinB2, 225);
}

void turnLeft(hbro motorPins) {
    digitalWrite(motorPins.motorPinA1, LOW);
    analogWrite(motorPins.motorPinA2, 255);
    analogWrite(motorPins.motorPinB1, 225);
    digitalWrite(motorPins.motorPinB2, LOW);
}