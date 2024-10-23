/*
   L9110S-Stepper-DC-motor-Driver-Module
  made on 28 oct 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/



#include <joystick.h>
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring.h> 


// Dette er tilsluttet på vores ESP32
#define A1 25  // Motor A pins
#define A2 26 // 
#define B1 14 // Motor B pins
#define B2 12
#define sensorRight 16 // Time of flight sensor

hbro motors = {A1, A2, B1, B2};

// Globale variabler vi skal bruge
VL53L0X sensor;


int incomingByte = 0; // for incoming serial data


void setup() {

  // Motor setup
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);

  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);

  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps


  // Sensor setup 
  Serial.begin(9600);
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();
}

// Loop der kører automatisk kørsel
void loop()
{
  Serial.print(sensor.readRangeSingleMillimeters());
  int distance = sensor.readRangeSingleMillimeters();
  if (distance <= 50) {
    turnLeft();
  }
  else if (distance > 50) {
    forward();
  }
  //delay(50);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
}

// Loop der kører funktioner som er skrevet på forhånd
// void loop() {
//   forward();
//   delay (3000);

//   backward();
//   delay (3000);

//   turnLeft();
//   delay (750);

//   forward();
//   delay (3000);

//   turnRight();
//   delay (750);

//   backward();
//   delay (3000);

//   Stop();
//   delay(20000);

//   turnRight();
//   delay(5000); 

//   // if statement for sensor driving, struct defineret i motorstyring.h
// };




// Insert delay somehow so the function is not constantly called or listened to
// void driveToggle () {
//   while (true) {
//     if (joystickListen()) toggleMode();
//     return 0;
//   }
// };