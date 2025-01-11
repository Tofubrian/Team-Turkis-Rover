// // #include <Arduino.h>

// // const int buzzerPin = 5; // Connect the passive buzzer to digital pin 5
 

// // void customBuzzerLoop() {
// //   // Turn on the buzzer
// //   pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
// //   tone(buzzerPin, 400); // Generate a 400 Hz tone
// //   //   delay(2000);          // Wait for 2 seconds

// //   // Turn off the buzzer
// //   //   noTone(buzzerPin);    // Stop the buzzer
// //   //   delay(1000);          // Wait for 1 second
// // }

// // TaskHandle_t buzzertoggle;

// // void buzzertoggle(void* pvParameters) {
// //     while (true){
// //         customBuzzerLoop();
// //         vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to debounce

// //     }
// // }
// #ifndef BUZZER_H
// #define BUZZER_H

// #include <Arduino.h>

// // Task handle for the buzzer to run passively
// TaskHandle_t buzzertoggleTaskHandle;

// // Define the buzzer pin
// const int buzzerPin = 5; // Connect the passive buzzer to digital pin 5

// // Global variable to control buzzer state
// extern volatile bool buzzerActive;

// // // Function to initialize the buzzer pin
// void buzzerSetup() {
//     pinMode(buzzerPin, OUTPUT);
//     noTone(buzzerPin);
// }

// // Function to handle the buzzer behavior
// void customBuzzerLoop() {
//     if (buzzerActive) {
//         tone(buzzerPin, 400); // Generate a 400 Hz tone
//     } else {
//         // Buzzer do nothing
//     }
// }

// // Task function for the buzzer
// void buzzertoggle(void* pvParameters) {
//     while (true) {
//         customBuzzerLoop();          // Call the buzzer loop function
//         vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to manage task load
//     }
// }

// #endif // BUZZER_H

