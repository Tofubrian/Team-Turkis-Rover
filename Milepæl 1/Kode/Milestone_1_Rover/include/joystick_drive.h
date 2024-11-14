#include <Arduino.h>
#include "MotorStyring_Classes.h"


// ************************* START JOYSTICK ************************* //

// Joystick definition and variables here
const int ManualpinX = 39;  // Joystick X-axis pin
const int ManualpinY = 36;  // Joystick Y-axis pin

// ******* LOCKED VALUES FOR JOYSTICK ******* // 
const int joystick_center = 512; // Center of the joystick // 2048
const int joystick_threshold = 50; // Dead zone threshold // 200
const int joystick_max_value = 1023; // Maximum reading for x,y axis
const int joystick_min_value = 462; // Minimum reading for x,y axis
const int MOTOR_MAX_SPEED = 255; // Maximum motor speed


// ************************* END JOYSTICK ******************************* //

// ************************* START MOTOR PIN DEFINITION ******************************* //

MotorController motors(25, 26, 14, 12);  // A1, A2, B1, B2

// ************************* END MOTOR PIN DEFINITION ******************************* //

// ------------------------------------------------------------------------------------------------

// ************************* JOYSTICK DRIVE MODE ************************* //

void manualMode() {
    int joyPinX = analogRead(ManualpinX); // Read X-axis value  
    int joyPinY = analogRead(ManualpinY); // Read X-axis value  

    Serial.println("X value is ");
    Serial.println(joyPinX);
    Serial.println("Y value is ");
    Serial.println(joyPinY);

    if (joyPinY > joystick_center + joystick_threshold) {
        motors.forward();
        Serial.println("Going forward");
    }
    else if (joyPinY > joystick_center + joystick_threshold && joyPinX > joystick_center + joystick_threshold) {
        motors.turnSmoothLeft();
        Serial.println("Turning forward left");
    }
    else if (joyPinY > joystick_center + joystick_threshold && joyPinX > joystick_center - joystick_threshold) {
        motors.turnSmoothRight();
        Serial.println("Turning forward right");
    }
    else {
        motors.stop();
        Serial.println("Idle mode");
    }

    if (joyPinY < joystick_center - joystick_threshold) {
        motors.backward();
        Serial.println("Going backward");
    }
    else if (joyPinY < joystick_center - joystick_threshold && joyPinX > joystick_center + joystick_threshold){
        motors.backwardSmoothLeft();
        Serial.println("Backwards left");
    }
    else if (joyPinY < joystick_center - joystick_threshold && joyPinX < joystick_center - joystick_threshold) {
        motors.backwardSmoothRight();
        Serial.println("Backwards right");
    }
    else {
        motors.stop();
        Serial.println("Idle mode");
    }

    // Delay here for smooth movements with the joystick
    delay(100);
}

// ************************* JOYSTICK END DRIVE MODE ************************* //

