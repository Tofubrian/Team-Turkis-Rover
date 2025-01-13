// #ifndef TOGGLEMODE_H
// #define TOGGLEMODE_H

// #include <Arduino.h>
// #include <receiver.h> // Assumes joystick input is handled here
// #include <allMotorControls.h>  // For automaticDriveMode and manualMode
// #include <robotArm.h>          // For moveServos
// #include <toggleMode.h>

// #pragma once

// extern TaskHandle_t switchModeTaskTaskHandle;

// // Global variable to control the toggle state
// // extern volatile bool toggleDrive; // This is the joystick's toggle state
// extern volatile int currentMode = 0;  // Variable to track the current mode (0 = Manual, 1 = Automatic, 2 = Move Servos)
// bool toggleSwitchMode = myJoystick.toggleDriveMode;
// // volatile int currentMode = 0;  // Initialize the mode, e.g., 0 for Manual Mode

// // Function to handle switching between the functions
// void switchModeTask(void* pvParameters) {
//     while (true) {
//         Serial.print("TOGGLE STATE: "); 
//         Serial.println(toggleSwitchMode); // Debug statement
//         // Detect joystick button press to switch mode
//         if (toggleSwitchMode) {  // Replace with your joystick button detection method
//             // Change the mode in a cyclic manner (0 -> 1 -> 2 -> 0)
//             currentMode = (currentMode + 1) % 3;
//             Serial.println("CURRENT MODE IS: ");
//             Serial.println(currentMode);

//             // Add a small debounce delay to avoid multiple presses
//             vTaskDelay(pdMS_TO_TICKS(300));  // Adjust delay as necessary to debounce the button press
//         }

//         // Switch between modes based on the value of currentMode
//         switch (currentMode) {
//             case 0: // Manual Mode
//                 Serial.println("Switching to Manual Mode: 0");
//                 manualMode();  // Call manual mode function
//                 break;

//             case 1: // Automatic Mode
//                 Serial.println("Switching to Automatic Mode: 1");
//                 automaticDriveMode();  // Call automatic drive mode function
//                 break;

//             case 2: // Move Servos Mode
//                 Serial.println("Switching to Move Servos Mode: 2");
//                 moveServos();  // Call move servos function (define this if needed)
//                 break;

//             default:
//                 Serial.println("Invalid mode");
//                 break;
//         }

//         // Optional: Add a small delay to avoid too fast toggling
//         vTaskDelay(pdMS_TO_TICKS(20)); // Adjust delay as necessary to prevent too frequent switching
//     }
// }

// #endif // TOGGLEMODE_H
// #ifndef TOGGLEMODE_H
// #define TOGGLEMODE_H

// #include <Arduino.h>
// #include <receiver.h> // Assumes joystick input is handled here
// #include <allMotorControls.h>  // For automaticDriveMode and manualMode
// #include <robotArm.h>          // For moveServos

// #pragma once

// extern TaskHandle_t switchModeTaskTaskHandle;



// // Function to handle switching between the functions
// void switchModeTask(void* pvParameters) {
//     while (true) {

//         int currentMode;  // Declare `currentMode` as an extern variable (if defined elsewhere)
//         // Detect joystick button press to switch mode
//         bool toggleSwitchMode = myJoystick.toggleDriveMode; // Read the current state of the joystick

//         Serial.print("TOGGLE STATE: "); 
//         Serial.println(toggleSwitchMode); // Debug statement

//         if (toggleSwitchMode) {  // Replace with your joystick button detection method
//             // Change the mode in a cyclic manner (0 -> 1 -> 2 -> 0)
//             currentMode = (currentMode + 1) % 3;
//             Serial.println("CURRENT MODE IS: ");
//             Serial.println(currentMode);

//             // Add a small debounce delay to avoid multiple presses
//             vTaskDelay(pdMS_TO_TICKS(300));  // Adjust delay as necessary to debounce the button press
//         }

//         // Switch between modes based on the value of currentMode
//         switch (currentMode) {
//             case 0: // Manual Mode
//                 Serial.println("Switching to Manual Mode: 0");
//                 manualMode();  // Call manual mode function
//                 break;

//             case 1: // Automatic Mode
//                 Serial.println("Switching to Automatic Mode: 1");
//                 automaticDriveMode();  // Call automatic drive mode function
//                 break;

//             case 2: // Move Servos Mode
//                 Serial.println("Switching to Move Servos Mode: 2");
//                 moveServos();  // Call move servos function (define this if needed)
//                 break;

//             default:
//                 Serial.println("Invalid mode");
//                 break;
//         }

//         // Optional: Add a small delay to avoid too fast toggling
//         vTaskDelay(pdMS_TO_TICKS(20)); // Adjust delay as necessary to prevent too frequent switching
//     }
// }

// #endif // TOGGLEMODE_H

#ifndef TOGGLEMODE_H
#define TOGGLEMODE_H

#include <Arduino.h>
#include <receiver.h> // Assumes joystick input is handled here
#include <allMotorControls.h>  // For automaticDriveMode and manualMode
#include <robotArm.h>          // For moveServos

#pragma once

extern TaskHandle_t switchModeTaskTaskHandle;

// Function to handle switching between the functions
void switchModeTask(void* pvParameters) {
    int currentMode = 0;  // Declare `currentMode` as a local variable
    bool lastToggleSwitchMode = false;  // Track the last state to detect changes

    while (true) {
        // Detect joystick button press to switch mode
        bool toggleSwitchMode = myJoystick.toggleDriveMode; // Read the current state of the joystick

        Serial.print("TOGGLE STATE: "); 
        Serial.println(toggleSwitchMode); // Debug statement

        // Detect a change in the toggle switch state (edge detection)
        if (toggleSwitchMode && !lastToggleSwitchMode) {
            // Change the mode in a cyclic manner (0 -> 1 -> 2 -> 0)
            currentMode = (currentMode + 1) % 3;
            Serial.println("CURRENT MODE IS: ");
            Serial.println(currentMode);
        }
        lastToggleSwitchMode = toggleSwitchMode; // Update the last state

        // Switch between modes based on the value of currentMode
        switch (currentMode) {
            case 0: // Manual Mode
                Serial.println("Switching to Manual Mode: 0");
                manualMode();  // Call manual mode function
                break;

            case 1: // Automatic Mode
                Serial.println("Switching to Automatic Mode: 1");
                automaticDriveMode();  // Call automatic drive mode function
                break;

            case 2: // Move Servos Mode
                Serial.println("Switching to Move Servos Mode: 2");
                moveServos();  // Call move servos function (define this if needed)
                break;

            default:
                Serial.println("Invalid mode");
                break;
        }

        // Optional: Add a small delay to avoid too fast toggling
        vTaskDelay(pdMS_TO_TICKS(20)); // Adjust delay as necessary to prevent too frequent switching
    }
}

#endif // TOGGLEMODE_H

