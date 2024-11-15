#include <Arduino.h>
#include "MotorStyring_Classes.h"


// ************************* START JOYSTICK ************************* //

// Joystick definition and variables here
const int ManualpinX = 35;  // Joystick X-axis pin
const int ManualpinY = 34;  // Joystick Y-axis pin

// ******* LOCKED VALUES FOR JOYSTICK ******* // 
const int joystick_center = 520; // Center of the joystick // 2048
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

    if (joyPinY > joystick_center + joystick_threshold) { // Forward
        if (joyPinX > joystick_center + joystick_threshold) {
            motors.turnSmoothLeft(); // Forward Left
            Serial.println("Turning forward left");
        }
        else if (joyPinX < joystick_center - joystick_threshold) {
            motors.turnSmoothRight(); // Forward Right
            Serial.println("Turning forward right");
        }
        else {
            motors.forward(); // Straight Forward
            Serial.println("Going forward");
        }
    }
    else if (joyPinY < joystick_center - joystick_threshold) { // Backward
        if (joyPinX > joystick_center + joystick_threshold) {
            motors.backwardSmoothLeft(); // Backward Left
            Serial.println("Backwards left");
        }
        else if (joyPinX < joystick_center - joystick_threshold) {
            motors.backwardSmoothRight(); // Backward Right
            Serial.println("Backwards right");
        }
        else {
            motors.backward(); // Straight Backward
            Serial.println("Going backward");
        }
    }
    else if (joyPinX > joystick_center + joystick_threshold) { // Idle movement Right
        motors.turnSmoothLeft();
        Serial.println("Turning idle left");
    }
    else if (joyPinX < joystick_center - joystick_threshold) { // Idle movement Left
        motors.turnSmoothRight();
        Serial.println("Turning idle right");
    }
    else { // Idle
        motors.stop();
        Serial.println("Idle mode");
    }
    
    // Delay here for smooth movements with the joystick
    delay(100);

    // if (joyPinY > joystick_center + joystick_threshold) {
    //     motors.forward();
    //     Serial.println("Going forward");
    // }
    // else if (joyPinY > joystick_center + joystick_threshold && joyPinX > joystick_center + joystick_threshold) {
    //     motors.turnSmoothLeft();
    //     Serial.println("Turning forward left");
    // }
    // else if (joyPinY > joystick_center + joystick_threshold && joyPinX > joystick_center - joystick_threshold) {
    //     motors.turnSmoothRight();
    //     Serial.println("Turning forward right");
    // }
    // else if (joyPinY < joystick_center - joystick_threshold) {
    //     motors.backward();
    //     Serial.println("Going backward");
    // }
    // else if (joyPinY < joystick_center - joystick_threshold && joyPinX > joystick_center + joystick_threshold){
    //     motors.backwardSmoothLeft();
    //     Serial.println("Backwards left");
    // }
    // else if (joyPinY < joystick_center - joystick_threshold && joyPinX < joystick_center - joystick_threshold) {
    //     motors.backwardSmoothRight();
    //     Serial.println("Backwards right");
    // }
    // else {
    //     motors.stop();
    //     Serial.println("Idle mode");
    // }

    // // Delay here for smooth movements with the joystick
    // delay(100);
}

// ************************* JOYSTICK END DRIVE MODE ************************* //

