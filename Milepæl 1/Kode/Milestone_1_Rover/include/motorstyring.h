// #include <Arduino.h>
// #include <Wire.h>
// #include <VL53L0X.h> 

// #define A1 25  // Motor A pins
// #define A2 26 //
// #define B1 14 // Motor B pins
// #define B2 12
// #define sensorRight 16 // Time of flight sensor

// VL53L0X sensor; // Variabel til sensor

// Struct setup for pins til hjul, kan benyttes til sensor styring senere
// struct hbro
// {
//   const int motorPinA1; // Motor A tilbage 
//   const int motorPinA2; // Motor A frem 
//   const int motorPinB1; // Motor B tilbage
//   const int motorPinB2; // Motor B frem
// };

// void initMotors (hbro motorPins)
// {
//     pinMode(motorPins.motorPinA1, OUTPUT);
//     pinMode(motorPins.motorPinA2, OUTPUT);
//     pinMode(motorPins.motorPinB1, OUTPUT);
//     pinMode(motorPins.motorPinB2, OUTPUT);
// };



// int incomingByte = 0; // for incoming serial data

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 

#define A1 25  // Motor A pins
#define A2 26
#define B1 14 // Motor B pins
#define B2 12

// Pin for buzzer module
// #define buzzerPin 33    // Buzzer sensor

const int channel = 0;     // LEDC channel (0-15)


// Struct setup for pins til hjul, kan benyttes til sensor styring senere
struct hbro
{
  const int motorPinA1; // 
  const int motorPinA2; // 
  const int motorPinB1;
  const int motorPinB2;
};

void initMotors (hbro motorPins)
{
    pinMode(motorPins.motorPinA1, OUTPUT);
    pinMode(motorPins.motorPinA2, OUTPUT);
    pinMode(motorPins.motorPinB1, OUTPUT);
    pinMode(motorPins.motorPinB2, OUTPUT);
};


// void playTone(){
//   ledcWriteTone(channel, 1200);
// }



void backward() {           // Kør Forlæns
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(B1, 0);
  analogWrite(B2, 255);
  
}


// Sound when this function is executed
void forward() {          // Kør Baglens
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

void turnRight() {        // Drej til højre
  analogWrite(A1, 225);
  analogWrite(A2, 0);
  analogWrite(B1, 0);
  analogWrite(B2, 225);
}

void turnLeft() {         // Drej til venstre
  analogWrite(A1, 0);
  analogWrite(A2, 255);
  analogWrite(B1, 225);
  analogWrite(B2, 0);
}

void forwardSaveRight () {

  // Motor control code
  backward();
  delay(700);
  turnRight();
  delay(1000);

}

void forwardSaveLeft () {
 
  
  // Your existing forwardSaveRight() code here
  backward();
  delay(700);
  turnLeft();
  delay(1000);


  

}