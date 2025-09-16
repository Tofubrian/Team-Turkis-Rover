#ifndef LED_H
#define LED_H

#include <Arduino.h>

// Define the LED pin
const int redLEDPin = 4;

// Global variable to control the LED state
volatile bool redLEDActive = false; // Initially, LED is off

// Function to initialize the LED pin
void redLEDsetup() {
    pinMode(redLEDPin, OUTPUT);
    digitalWrite(redLEDPin, LOW);  // Ensure the LED is off initially
}

// Function to handle the red LED behavior based on redLEDActive state
void redLEDloop() {
    if (redLEDActive) {
        digitalWrite(redLEDPin, HIGH); // Turn on the LED when active
    } else {
        digitalWrite(redLEDPin, LOW);  // Turn off the LED when not active
    }
}

// Function to control the LED based on backward() action
void backwardLEDControl() {
    // You can now call this in your backward() function to activate the LED when backward() is called
    redLEDActive = true;  // Turn on the LED
    redLEDloop();         // Update the LED state
}

// Function to turn off the LED if needed
void stopBackwardLEDControl() {
    redLEDActive = false; // Turn off the LED
    redLEDloop();         // Update the LED state
}

#endif // LED_H
