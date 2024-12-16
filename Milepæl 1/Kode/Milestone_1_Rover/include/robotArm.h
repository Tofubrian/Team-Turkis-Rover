#include <Arduino.h>
#include <ESP32Servo.h>
#include <receiver.h>

// Servo objects
Servo baseServo;
Servo joint1Servo;
Servo joint2Servo;
Servo grabServo;

// Servo pin definitions
const int baseServoPin = 23;
const int joint1ServoPin = 32;
const int joint2ServoPin = 33;
const int grabServoPin = 19;

// Variable to store positions of servos
int currentBasePosition = 120;
int currentJoint1Position = 120;
int currentJoint2Position = 90;
int currentGrabPosition = 120;

// Constants for servo angles
const int BASE_MIN_ANGLE = 30;
const int BASE_MAX_ANGLE = 150;
const int JOINT1_MIN_ANGLE = 80;
const int JOINT1_MAX_ANGLE = 150;
const int JOINT2_MIN_ANGLE = 70;
const int JOINT2_MAX_ANGLE = 120;
const int GRAB_MIN_ANGLE = 80;
const int GRAB_MAX_ANGLE = 160;

// Movement speed
const int SERVO_STEP_SIZE = 2;  // Increment/decrement step size for movement

// Joystick dead zone
const int JOYSTICK_CENTER_MIN = 1600;
const int JOYSTICK_CENTER_MAX = 2100;

// Variables
bool toggleServos = false;  // Tracks which servos to control
bool lastClickState = HIGH; // Debounce helper for joystick button

// FreeRTOS task handle
TaskHandle_t moveServosTaskHandle;

void moveServos(void* pvParameters) {
    while (true) {
        // Read joystick values
        int xValue = myJoystick.positionX;
        
        int yValue = myJoystick.positionY;

        // Read and handle toggle state
        int clickValue = myJoystick.toggleState;

        if (clickValue == LOW && lastClickState == HIGH) {
            toggleServos = !toggleServos; // Toggle servo group
        }
        lastClickState = clickValue;

        // Debugging: Print joystick and toggle information
        Serial.print("Joystick X: "); Serial.println(xValue);
        // delay(750);
        Serial.print("Joystick Y: "); Serial.println(yValue);
        // delay(750);
        Serial.print("ToggleServos: "); Serial.println(toggleServos);

        if (toggleServos) {
            // Handle servo2 and grab control
            if (xValue < JOYSTICK_CENTER_MIN) {
                currentJoint2Position = max(currentJoint2Position - SERVO_STEP_SIZE, JOINT2_MIN_ANGLE);
            }
            else if (xValue > JOYSTICK_CENTER_MAX) {
                currentJoint2Position = min(currentJoint2Position + SERVO_STEP_SIZE, JOINT2_MAX_ANGLE);
            }
            // Write only if position changes
            joint2Servo.write(currentJoint2Position);

            if (yValue < JOYSTICK_CENTER_MIN) {
                currentGrabPosition = max(currentGrabPosition - SERVO_STEP_SIZE, GRAB_MIN_ANGLE);
            }
            else if (yValue > JOYSTICK_CENTER_MAX) {
                currentGrabPosition = min(currentGrabPosition + SERVO_STEP_SIZE, GRAB_MAX_ANGLE);
            }
            // Write only if position changes
            grabServo.write(currentGrabPosition);

            Serial.print("joint2Servo Position: "); Serial.println(currentJoint2Position);
            Serial.print("grabServo Position: "); Serial.println(currentGrabPosition);
        } 
        else {
            // Handle joint1 and base control
            if (xValue < JOYSTICK_CENTER_MIN) {
                currentJoint1Position = max(currentJoint1Position - SERVO_STEP_SIZE, JOINT1_MIN_ANGLE);
            }
            else if (xValue > JOYSTICK_CENTER_MAX) {
                currentJoint1Position = min(currentJoint1Position + SERVO_STEP_SIZE, JOINT1_MAX_ANGLE);
            }
            // Write only if position changes
            joint1Servo.write(currentJoint1Position);

            if (yValue < JOYSTICK_CENTER_MIN) {
                currentBasePosition = max(currentBasePosition - SERVO_STEP_SIZE, BASE_MIN_ANGLE);
            }
            else if (yValue > JOYSTICK_CENTER_MAX) {
                currentBasePosition = min(currentBasePosition + SERVO_STEP_SIZE, BASE_MAX_ANGLE);
            }
            // Write only if position changes
            baseServo.write(currentBasePosition);

            Serial.print("joint1Servo Position: "); Serial.println(currentJoint1Position);
            Serial.print("Base Position: "); Serial.println(currentBasePosition);
        }

        // Delay to maintain task frequency
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}



void robotArmSetup() {
    Serial.begin(115200);
    
    // Attach servos
    baseServo.attach(baseServoPin);
    joint1Servo.attach(joint1ServoPin);
    joint2Servo.attach(joint2ServoPin);
    grabServo.attach(grabServoPin);

    // Initialize servos to center position
    baseServo.write(currentBasePosition);
    joint1Servo.write(currentJoint1Position);
    joint2Servo.write(currentJoint2Position);
    grabServo.write(currentGrabPosition);

    receiverESP32();

    // Joystick button pin setup
    pinMode(buttonPressed, INPUT_PULLUP); // Use internal pull-up resistor

    // Create task for servo movement
    // xTaskCreatePinnedToCore(
    //     moveServos,
    //     "Move Servos",
    //     10000,
    //     NULL,
    //     1,
    //     &moveServosTaskHandle,
    //     0
    // );
    // xTaskCreate(
    //     moveServos,
    //     "Move Servos",
    //     2048,
    //     NULL,
    //     1,
    //     &moveServosTaskHandle
    // );
}

void emptyLoop() {
  // The main loop can be used for other tasks or remain empty
}

