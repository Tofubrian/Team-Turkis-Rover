/*
   L9110S-Stepper-DC-motor-Driver-Module
  made on 28 oct 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/
// update to revert the code


// #include <joystick.h>
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring.h> 

int incomingByte = 0; // for incoming serial data

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

VL53L0X sensorRight;
VL53L0X sensorLeft;
VL53L0X sensorFront;

// Pin for buzzer module
#define buzzerPin 33    // Buzzer sensor

const int PWM_CHANNEL = 0;    // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 500;     // Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz
const int PWM_RESOLUTION = 8; // We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits 

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int LED_OUTPUT_PIN = 33;

const int DELAY_MS = 0;  // delay between fade increments

// bool isForwardSaveRightActive = false;



void setup() {

  //   // Buzzer module activation
  // pinMode(buzzerPin, OUTPUT);
  // ledcSetup(channel, 2000, 8);  // channel, initial frequency, resolution
  // ledcAttachPin(buzzerPin, channel);
  // digitalWrite(buzzerPin, HIGH); // Start with the buzzer off

    // Sets up a channel (0-15), a PWM duty cycle frequency, and a PWM resolution (1 - 16 bits) 
  // ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

  // ledcAttachPin(uint8_t pin, uint8_t channel);
  ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);
  

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);

  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);

  Serial.begin(115200); // opens serial port, sets data rate to 115200 bps

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

if (distanceFront <= 220) {
  // Obstacle in front, perform forwardSave()
  ledcWrite(PWM_CHANNEL, 500);
  forwardSaveRight();
  ledcWrite(PWM_CHANNEL, 0);

  
  // // fade up PWM on given channel
  // for(int dutyCycle = 0; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle++){   
  //   ledcWrite(PWM_CHANNEL, dutyCycle);
  //   delay(DELAY_MS);
  // }

  // // fade down PWM on given channel
  // for(int dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= 0; dutyCycle--){
  //   ledcWrite(PWM_CHANNEL, dutyCycle);   
  //   delay(DELAY_MS);
  // }

  // while (isForwardSaveRightActive) {
  //   ledcWriteTone(channel, 2000);
  //   delay(10);  // Small delay to prevent tight looping
  // }
  // ledcWriteTone(channel, 0);  // Turn off the tone when forwardSaveRight is done
}
else if (distanceFront <= 200 && distanceRight <= 200) {
  forwardSaveLeft();
}

else if (distanceFront <= 200 && distanceLeft <= 200) {
  forwardSaveRight();
}

else if (distanceLeft <= 200 && distanceRight <= 200) {
  // Obstacles on both sides, move forward cautiously
  forwardSaveRight();
  delay(100);
}
else if (distanceLeft <= 200) {
  // Obstacle on the left, turn right
  turnRight();
  delay(100);
} 
else if (distanceRight <= 200) {
  // Obstacle on the right, turn left
  turnLeft();
  delay(100);
} 
else {
  // Clear path, move forward
  forward();
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


