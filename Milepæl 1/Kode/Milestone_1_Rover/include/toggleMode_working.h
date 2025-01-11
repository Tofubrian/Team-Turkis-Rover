// #ifndef TOGGLEMODE_H
// #define TOGGLEMODE_H

// #include <Arduino.h>
// #include <receiver.h> // Assumes joystick input is handled here
// #include <allMotorControls.h>  // For automaticDriveMode and manualMode
// #include <robotArm.h>          // For moveServos



// extern TaskHandle_t switchModeTaskTaskHandle;

// // Global variable to control the toggle state
// extern volatile bool toggleState; // This is the joystick's toggle state
// extern volatile int currentMode;  // Variable to track the current mode (0 = Manual, 1 = Automatic, 2 = Move Servos)

// volatile int currentMode = 0;  // Initialize the mode, e.g., 0 for Manual Mode

// // Function to handle switching between the functions
// void switchModeTask(void* pvParameters) {
//     while (true) {
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
