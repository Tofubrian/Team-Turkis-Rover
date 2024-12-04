#include <Arduino.h>
#include "MotorStyring_CLASSES.h"
// #include "rover_joystick_receive.h"
// #include <receiver.h>



// ************************* START JOYSTICK ************************* //

// ******* LOCKED VALUES FOR JOYSTICK ******* // 
const int joystick_center = 1870; // Center of the joystick // 2048
const int joystick_threshold = 100; // Dead zone threshold // 200
const int joystick_max_value = 4095; // Maximum reading for x,y axis
const int joystick_min_value = 462; // Minimum reading for x,y axis
const int MOTOR_MAX_SPEED = 255; // Maximum motor speed


// ************************* END JOYSTICK ******************************* //

// ************************* START MOTOR PIN DEFINITION ******************************* //

MotorController motors(25, 26, 14, 12);  // A1, A2, B1, B2 

// ************************* END MOTOR PIN DEFINITION ******************************* //



// ************************* JOYSTICK DRIVE MODE ************************* //

void manualMode() {
    // int inputX = analogRead(ManualpinX); // Read X-axis value  
    // int inputY = analogRead(ManualpinY); // Read X-axis value

    int joyPinX = myJoystick.positionXmotor;
    int joyPinY = myJoystick.positionYmotor;


    Serial.println("X value is ");
    Serial.println(joyPinX);

    Serial.println("Y value is ");
    Serial.println(joyPinY);

    if (joyPinY > joystick_center + joystick_threshold) { // Forward
        if (joyPinX > joystick_center + joystick_threshold) {
            motors.turnSmoothLeft(); // Forward Left
            Serial.println("Turning forward left");
        }
        else if (joyPinX < joystick_center - joystick_threshold) {
            motors.turnRight(); // Forward Right
            Serial.println("Turning forward right");
        }
        else {
            motors.forward(); // Straight Forward
            Serial.println("Going forward");
        }
    }
    else if (joyPinY < joystick_center - joystick_threshold) { // Backward
        if (joyPinX > joystick_center + joystick_threshold) {
            motors.turnLeft(); // Backward Left
            Serial.println("Backwards left");
        }
        else if (joyPinX < joystick_center - joystick_threshold) {
            motors.turnRight(); // Backward Right
            Serial.println("Backwards right");
        }
        else {
            motors.backward(); // Straight Backward
            Serial.println("Going backward");
        }
    }
    else if (joyPinX > joystick_center + joystick_threshold) { // Idle movement Right
        motors.turnLeft();
        Serial.println("Turning idle left");
    }
    else if (joyPinX < joystick_center - joystick_threshold) { // Idle movement Left
        motors.turnRight();
        Serial.println("Turning idle right");
    }
    else { // Idle
        motors.stop();
        Serial.println("Idle mode");
    }
    // Delay here for smooth movements with the joystick
    delay(100);
}
// ************************* JOYSTICK END DRIVE MODE ************************* //

