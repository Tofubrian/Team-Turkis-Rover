#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 

#define A1 25  // Motor A pins
#define A2 26
#define B1 14 // Motor B pins
#define B2 12

int incomingByte = 0; // for incoming serial data

void forward() {           // Kør Forlæns
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(B1, 0);
  analogWrite(B2, 255);
}

void backward() {          // Kør Baglens
  analogWrite(A1, 255);
  analogWrite(A2, 0);
  analogWrite(B1, 255);
  analogWrite(B2, 0);
}

void Stop() {              // Stop
  analogWrite(A1, 0);
  analogWrite(A2, 0);
  analogWrite(B1, 0);
  analogWrite(B2, 0);
}

void turnRight() {       // Drej til højre
  analogWrite(A1, 225);  
  analogWrite(A2, 0);
  analogWrite(B1, 0);
  analogWrite(B2, 225);
}

void turnLeft() {        // Drej til venstre
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(B1, 225);
  analogWrite(B2, 0);
}
/*Grunden til at turn har 225 i stedet for 255 er pga. 
for at kunne dreje et antal grader præcist, måtte 
hastigheden sættes ned for at undgå ustabillitet og hjulspin.*/