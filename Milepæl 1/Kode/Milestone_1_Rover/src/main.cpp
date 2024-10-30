/*
   L9110S-Stepper-DC-motor-Driver-Module
  made on 28 oct 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/



// #include <joystick.h>
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring.h> 

int incomingByte = 0; // for incoming serial data


class Bil
int main()
{
 // Dette er tilsluttet på vores ESP32
#define A1 25  // Motor A pins
#define A2 26 // 
#define B1 14 // Motor B pins
#define B2 12
// #define LED 16

// Pins for XSHUT
#define XSHUT_RIGHT 16   // XSHUT pin for højre sensor
#define XSHUT_LEFT 17    // XSHUT pin for venstre sensor
#define XSHUT_FRONT 19    // XSHUT pin for front sensor

}


VL53L0X sensorRight;
VL53L0X sensorLeft;
VL53L0X sensorFront;




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

  Wire.begin(); // Begin I2C communication

  // Configure XSHUT pins for sensorLeft and sensorRight and sensorFront
  pinMode(XSHUT_LEFT, OUTPUT);
  pinMode(XSHUT_RIGHT, OUTPUT);
  pinMode(XSHUT_FRONT, OUTPUT);

  // Deactivate both sensors at the beginning
  digitalWrite(XSHUT_LEFT, LOW);
  digitalWrite(XSHUT_RIGHT, LOW);
  digitalWrite(XSHUT_FRONT, LOW);
  delay(10);  // Small delay for sensor initialization

  // Initialize the left sensor
  digitalWrite(XSHUT_LEFT, HIGH);
  delay(10); // Allow time for sensor startup
  if (!sensorLeft.init()) {
    Serial.println("Failed to initialize left sensor!");
    while (1) {}
  }
  sensorLeft.setAddress(0x31); // Set unique address for left sensor
  sensorLeft.startContinuous();

  // Initialize the right sensor
  digitalWrite(XSHUT_RIGHT, HIGH);
  delay(10); // Allow time for sensor startup
  if (!sensorRight.init()) {
    Serial.println("Failed to initialize right sensor!");
    while (1) {}
  }
  sensorRight.setAddress(0x30); // Set unique address for right sensor
  sensorRight.startContinuous();

  // Initialize the right sensor
  digitalWrite(XSHUT_FRONT, HIGH);
  delay(10); // Allow time for sensor startup
  if (!sensorFront.init()) {
    Serial.println("Failed to initialize Front sensor!");
    while (1) {}
  }
  sensorFront.setAddress(0x29); // Set unique address for front sensor
  sensorFront.startContinuous();




}
void loop() {
  int distanceLeft = sensorLeft.readRangeSingleMillimeters();
  int distanceRight = sensorRight.readRangeSingleMillimeters();
  int distanceFront = sensorFront.readRangeSingleMillimeters();

  Serial.print("Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" Right Distance: ");
  Serial.println(distanceRight);
  Serial.print(" Front Distance: ");
  Serial.println(distanceFront);

  if (distanceLeft <= 200) { 
    // Obstacle on the left, turn right
    turnRight();
    delay(100);
  } 
  else if (distanceRight <= 200) {
    // Obstacle on the right, turn left
    turnLeft();
    delay(100);
  } 
  else if (distanceLeft > 200 && distanceRight > 200) {
    // Clear path, move forward
    forward();
  }

  else if (distanceFront <= 220) {
    forwardSave();
  }

  // Timeout handling for both sensors
  if (sensorLeft.timeoutOccurred()) { 
    Serial.println(" TIMEOUT on Left Sensor");
  }
  if (sensorRight.timeoutOccurred()) { 
    Serial.println(" TIMEOUT on Right Sensor");
  }

  if (sensorFront.timeoutOccurred()) { 
    Serial.println(" TIMEOUT on Front Sensor");
  }

  delay(50); // Small delay for stability in loop



  // forward();
  // delay (3000);

  // backward();
  // delay (3000);

  // turnLeft();
  // delay (750);

  // forward();
  // delay (3000);

  // turnRight();
  // delay (750);

  // backward();
  // delay (3000);

  // Stop();
  // delay(20000);

  // turnRight();
  // delay(5000); 

  // // if statement for sensor driving, struct defineret i motorstyring.h
};


