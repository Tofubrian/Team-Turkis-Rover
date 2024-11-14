#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring_CLASSES.h>
#include <ESP32Servo.h>
#include <servoarm.h>


// // Alt fungerende kode herunder

int incomingByte = 0; // for incoming serial data

// Define joystick pins
const int joystickXPin = 35;  // Joystick X-axis pin
const int joystickYPin = 34;  // Joystick Y-axis pin
const int joystickClick = 36;  // Joystick Y-axis pin

MotorController motors(25, 26, 14, 12);  // A1, A2, B1, B2

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

// const int JOYSTICK_CENTER = 512; // Center of the joystick // 2048
// const int JOYSTICK_THRESHOLD = 50; // Dead zone threshold // 200
// const int JOYSTICK_MAX_VALUE = 1023; // Maximum joystick reading on ESP32 // 4095
// const int MOTOR_MAX_SPEED = 255; // Maximum motor speed

// // Thresholds for joystick dead zone
// const int deadZoneThreshold = 50;   // Modify as needed
// const int maxSpeed = 255;           // Maximum speed for motors
// Constants
const int JOY_MAX = 4095;
const int JOY_MIN = 0;
const int JOY_CENTER = 2047;
const int Y_FORWARD_THRESHOLD = 2097;
const int Y_BACKWARD_THRESHOLD = 1997;
const int X_RIGHT_THRESHOLD = 2097;
const int X_LEFT_THRESHOLD = 1997;

void checkJoystickDirection(int xValue, int yValue) {
    if (yValue < Y_FORWARD_THRESHOLD && yValue > Y_BACKWARD_THRESHOLD && xValue < X_RIGHT_THRESHOLD && xValue < X_LEFT_THRESHOLD) {
      motors.stop();
      // Serial.println("FULL STOP");
    }
    else if (yValue > Y_FORWARD_THRESHOLD) {
      motors.forward();
      // Serial.println("Forward");
    }
    else if (yValue > Y_FORWARD_THRESHOLD && xValue > X_LEFT_THRESHOLD) {
      motors.turnSmoothLeft();
      // Serial.println("Turning Left");
    }
    else if (yValue > Y_FORWARD_THRESHOLD && xValue > X_RIGHT_THRESHOLD) {
      motors.turnSmoothRight();
      // Serial.println("Turning Right");
    }
    else if (yValue < Y_BACKWARD_THRESHOLD) {
      motors.backward();
      // Serial.println("Moving back");
    }
    else if (yValue < Y_BACKWARD_THRESHOLD && xValue > X_LEFT_THRESHOLD) {
      motors.backwardSmoothLeft();
      // Serial.println("Moving back left");
    }
    else if (yValue < Y_BACKWARD_THRESHOLD && xValue < X_RIGHT_THRESHOLD) {
      motors.backwardSmoothRight();
      // Serial.println("Moving back right");
    }
    else {

    }
}

void setup() {
  Serial.begin(115200);

// // ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);
//   ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

//   // ledcAttachPin(uint8_t pin, uint8_t channel);
//   ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);
//   Serial.begin(115200);
//   Wire.begin(); // Begin I2C communication

//   // Configure XSHUT pins for sensorLeft and sensorRight and sensorFront
//   pinMode(XSHUT_LEFT, OUTPUT);
//   pinMode(XSHUT_RIGHT, OUTPUT);
//   pinMode(XSHUT_FRONT, OUTPUT);

//   // Deactivate both sensors at the beginning
//   digitalWrite(XSHUT_LEFT, LOW);
//   digitalWrite(XSHUT_RIGHT, LOW);
//   digitalWrite(XSHUT_FRONT, LOW);
//   delay(10);  // Small delay for sensor initialization

//   // Initialize the left sensor
//   digitalWrite(XSHUT_LEFT, HIGH);
//   delay(10); // Allow time for sensor startup
//   if (!sensorLeft.init()) {
//     Serial.println("Failed to initialize left sensor!");
//     while (1) {}
//   }
//   sensorLeft.setAddress(0x31); // Set unique address for left sensor
//   sensorLeft.startContinuous();

//   // Initialize the right sensor
//   digitalWrite(XSHUT_RIGHT, HIGH);
//   delay(10); // Allow time for sensor startup
//   if (!sensorRight.init()) {
//     Serial.println("Failed to initialize right sensor!");
//     while (1) {}
//   }
//   sensorRight.setAddress(0x30); // Set unique address for right sensor
//   sensorRight.startContinuous();

//   // Initialize the right sensor
//   digitalWrite(XSHUT_FRONT, HIGH);
//   delay(10); // Allow time for sensor startup
//   if (!sensorFront.init()) {
//     Serial.println("Failed to initialize Front sensor!");
//     while (1) {}
//   }
//   sensorFront.setAddress(0x29); // Set unique address for front sensor
//   sensorFront.startContinuous();



};

void loop() {



  int xValue = analogRead(joystickXPin);  // Read X-axis
  int yValue = analogRead(joystickYPin);  // Read Y-axis
  int Click = analogRead(joystickClick);  // Read Y-axis
  
  int xValue10bit = xValue / 4;
  int yValue10bit = yValue / 4;
  int Click10bit = Click / 4;
  // Call control function with joystick values
  // checkJoystickDirection(xValue, yValue);
  Serial.println("xValue is ");
  Serial.println(xValue10bit);
  delay(1000);
  Serial.println("yValue is ");
  Serial.println(yValue10bit);
  delay(1000);
  Serial.println("Click is ");
  Serial.println(Click10bit);
  delay(1000);
  

  delay(100);  // Add a short delay to smooth out movement

//   int xValue = analogRead(joystickXPin);  // Read X-axis
//   int yValue = analogRead(joystickYPin);  // Read Y-axis

//   // Calculate the deviation from the center
//   int xDeviation = xValue - JOYSTICK_THRESHOLD;
//   int yDeviation = yValue - JOYSTICK_THRESHOLD;

//   // Apply dead zone
//   // int speedX = (abs(xDeviation) > JOYSTICK_THRESHOLD) ? map(abs(xDeviation), 0, JOYSTICK_MAX_VALUE - JOYSTICK_CENTER, 0, MOTOR_MAX_SPEED) : 0;
//   // int speedY = (abs(yDeviation) > JOYSTICK_THRESHOLD) ? map(abs(yDeviation), 0, JOYSTICK_MAX_VALUE - JOYSTICK_CENTER, 0, MOTOR_MAX_SPEED) : 0;



// // Determine motor direction and speed
// if (yDeviation > JOYSTICK_CENTER) {
//     if (xDeviation > JOYSTICK_CENTER) {
//         motors.turnSmoothRight();  // Move forward and right
//         Serial.println("Moving forward and turning right");
//     } else if (xDeviation < JOYSTICK_CENTER) {
//         motors.turnSmoothLeft();  // Move forward and left
//         Serial.println("Moving forward and turning left");
//     } else {
//         motors.forward();  // Move straight forward
//         Serial.println("Moving forward");
//     }
// } 
// else if (yDeviation < JOYSTICK_CENTER) {
//     if (xDeviation > JOYSTICK_CENTER) {
//         motors.backwardSmoothRight();  // Move backward and right
//         Serial.println("Moving backward and turning right");
//     } else if (xDeviation < JOYSTICK_CENTER) {
//         motors.backwardSmoothLeft();  // Move backward and left
//         Serial.println("Moving backward and turning left");
//     } else {
//         motors.backward();  // Move straight backward
//         Serial.println("Moving backward");
//     }
// } 
// else if (xDeviation > JOYSTICK_CENTER) {
//     motors.turnRight();  // Turn right only
//     Serial.println("Turning right");
// } 
// else if (xDeviation < JOYSTICK_CENTER) {
//     motors.turnLeft();  // Turn left only
//     Serial.println("Turning left");
// } 
// else {
//     motors.stop();  // Joystick is in the center, stop motors
//     Serial.println("Stopping");
// }

// delay(100);  // Small delay to smooth movement

  // Serial.println("Made it into the loop");

  // int xValue = analogRead(joystickXPin);  // Read X-axis
  // int yValue = analogRead(joystickYPin);  // Read Y-axis

  // // Map joystick values to motor speed (0-255)
  // int speedX = map(abs(xValue - 512), 0, 512, 0, maxSpeed);
  // int speedY = map(abs(yValue - 512), 0, 512, 0, maxSpeed);

  // // Determine the direction based on joystick position
  // if (yValue > 512 + deadZoneThreshold) {
  //   motors.forward(speedY);  // Forward
  //   Serial.println("Moving forward ");
  //   Serial.println(speedY);
  // } 
  // else if (yValue < 512 - deadZoneThreshold) {
  //   motors.backward(speedY);  // Backward
  //   Serial.println("Moving backwards ");
  //   Serial.println(speedY);
  // } 
  // else if (xValue > 512 + deadZoneThreshold) {
  //   motors.turnRight(speedX);  // Turn right
  //   Serial.println("Moving right ");
  //   Serial.println(speedY);
  // } 
  // else if (xValue < 512 - deadZoneThreshold) {
  //   motors.turnLeft(speedX);  // Turn left
  //   Serial.println("Moving left ");
  //   Serial.println(speedY);
  // } 
  // else {
  //   motors.stop();  // Joystick is in the dead zone, stop motors
  // }

  // delay(100);  // Small delay to smooth movement
};




// KODE DER KAN KØRE AUTOMATISK

  // int distanceLeft = sensorLeft.readRangeSingleMillimeters();
  // int distanceRight = sensorRight.readRangeSingleMillimeters();
  // int distanceFront = sensorFront.readRangeSingleMillimeters();

  // Serial.print("Left Distance: ");
  // Serial.print(distanceLeft);
  // Serial.print(" Right Distance: ");
  // Serial.println(distanceRight);
  // Serial.print(" Front Distance: ");
  // Serial.println(distanceFront);

  //   if (distanceFront <= 220) {
  //       ledcWrite(PWM_CHANNEL, 500);
  //       motors.forwardSaveRight();
  //       ledcWrite(PWM_CHANNEL, 0);
  //   }
  //   else if (distanceFront <= 200 && distanceRight <= 200) {
  //       motors.forwardSaveLeft();
  //   }
  //   else if (distanceFront <= 200 && distanceLeft <= 200) {
  //       motors.forwardSaveRight();
  //   }
  //   else if (distanceLeft <= 200 && distanceRight <= 200) {
  //       motors.forwardSaveRight();
  //       delay(100);
  //   }
  //   else if (distanceLeft <= 200) {
  //       motors.turnRight();
  //       delay(100);
  //   } 
  //   else if (distanceRight <= 200) {
  //       motors.turnLeft();
  //       delay(100);
  //   } 
  //   else {
  //       motors.forward();
  //   }

  // // Timeout handling for both sensors
  // if (sensorLeft.timeoutOccurred()) { 
  //   Serial.println(" TIMEOUT on Left Sensor");
  // }
  // if (sensorRight.timeoutOccurred()) { 
  //   Serial.println(" TIMEOUT on Right Sensor");
  // }

  // if (sensorFront.timeoutOccurred()) { 
  //   Serial.println(" TIMEOUT on Front Sensor");
  // }


