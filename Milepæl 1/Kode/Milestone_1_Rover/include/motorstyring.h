#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 

// #define A1 25  // Motor A pins
// #define A2 26 //
// #define B1 14 // Motor B pins
// #define B2 12
// #define sensorRight 16 // Time of flight sensor

// VL53L0X sensor; // Variabel til sensor

// Struct setup for pins til hjul, kan benyttes til sensor styring senere
struct hbro
{
  const int motorPinA1; // Motor A tilbage 
  const int motorPinA2; // Motor A frem 
  const int motorPinB1; // Motor B tilbage
  const int motorPinB2; // Motor B frem
};

void initMotors (hbro motorPins)
{
    pinMode(motorPins.motorPinA1, OUTPUT);
    pinMode(motorPins.motorPinA2, OUTPUT);
    pinMode(motorPins.motorPinB1, OUTPUT);
    pinMode(motorPins.motorPinB2, OUTPUT);
};



int incomingByte = 0; // for incoming serial data

void forward(int A1, int A2, int B1, int B2) {           // Kør Forlæns
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(B1, 0);
  analogWrite(B2, 255);
}


// Sound when this function is executed
void backward(int A1, int A2, int B1, int B2) {          // Kør Baglens
  analogWrite(A1, 255);
  analogWrite(A2, 0);
  analogWrite(B1, 255);
  analogWrite(B2, 0);
}

void Stop(int A1, int A2, int B1, int B2) {              // Stop
  analogWrite(A1, 0);
  analogWrite(A2, 0);
  analogWrite(B1, 0);
  analogWrite(B2, 0);
}




/*Grunden til at turn har 225 i stedet for 255 er pga. 
for at kunne dreje et antal grader præcist, måtte 
hastigheden sættes ned for at undgå ustabillitet og hjulspin.*/

void turnRight(int A1, int A2, int B1, int B2) {        // Drej til højre
  analogWrite(A1, 225);  
  analogWrite(A2, 0);
  analogWrite(B1, 0);
  analogWrite(B2, 225);
}

void turnLeft(int A1, int A2, int B1, int B2) {         // Drej til venstre
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(B1, 225);
  analogWrite(B2, 0);
}