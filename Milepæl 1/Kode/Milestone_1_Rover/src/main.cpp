/*
   L9110S-Stepper-DC-motor-Driver-Module
  made on 28 oct 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring.h> 

#define A1 25  // Motor A pins
#define A2 26
#define B1 14 // Motor B pins
#define B2 12

int incomingByte = 0; // for incoming serial data


void setup() {

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);

  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);

  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps

}
void loop() {
  forward();
  delay (3000);

  backward();
  delay (3000);

  turnLeft();
  delay (750);

  forward();
  delay (3000);

  turnRight();
  delay (750);

  backward();
  delay (3000);

  Stop();
  delay(20000);

  turnRight();
  delay(5000); 
};
