#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 

#define A1 25  // Motor A pins
#define A2 26
#define B1 14 // Motor B pins
#define B2 12

int incomingByte = 0; // for incoming serial data

void backward() {          //function of forward 
  analogWrite(A1, 255);
  analogWrite(A2, 0);
  analogWrite(B1, 255);
  analogWrite(B2, 0);
}

void forward() {         //function of backward
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(B1, 0);
  analogWrite(B2, 255);
}

// turn right loop
void turnRight() {
  analogWrite(A1, 255);
  analogWrite(A2, 0);
  analogWrite(B1, 0);
  analogWrite(B2, 255);
}

// turn left loop
void turnLeft() {
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(B1, 225);
  analogWrite(B2, 0);
}

void Stop() {
  analogWrite(A1, 0);
  analogWrite(A2, 0);
  analogWrite(B1, 0);
  analogWrite(B2, 0);
}