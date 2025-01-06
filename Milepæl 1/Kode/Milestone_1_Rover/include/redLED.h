// #include <Arduino.h>
// #include <buzzer.h>

// const int redLEDPin = 4;


// void redLEDloop () {
//     pinMode(redLEDPin, OUTPUT);
//     digitalWrite(redLEDPin, HIGH);
// }

// TaskHandle_t redLEDtoggle;

// void redLEDtoggle(void* pvParameters) {
//     while (true){
//         redLEDloop();
//         vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to debounce
//     }
// }
#ifndef LED_H
#define LED_H

#include <Arduino.h>

// Define the LED pin
const int redLEDPin = 4;

// Global variable to control the LED state
extern bool redLEDActive;

// Function to handle the red LED behavior
void redLEDloop() {
    if (redLEDActive) {
        digitalWrite(redLEDPin, HIGH); // Turn on the LED
    } else {
        digitalWrite(redLEDPin, LOW);  // Turn off the LED
    }
}

// Function to initialize the LED pin
void initializeRedLEDPin() {
    pinMode(redLEDPin, OUTPUT);
}

// Task function for the red LED
void redLEDtoggle(void* pvParameters) {
    while (true) {
        redLEDloop();                 // Call the LED loop function
        vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to manage task load
    }
}

#endif // LED_H
