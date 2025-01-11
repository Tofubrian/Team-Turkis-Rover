#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

// Define the buzzer pin
const int buzzerPin = 5; // Connect the passive buzzer to digital pin 5

// Global variable to control buzzer state
volatile bool buzzerActive = false; // Initially, buzzer is off

// Function to initialize the buzzer pin
void buzzerSetup() {
    pinMode(buzzerPin, OUTPUT);
    noTone(buzzerPin);  // Ensure the buzzer is off initially
}

// Function to handle the buzzer behavior based on buzzerActive state
void customBuzzerLoop() {
    if (buzzerActive) {
        tone(buzzerPin, 400); // Generate a 400 Hz tone when active
    } else {
        noTone(buzzerPin);    // Stop the buzzer tone when not active
    }
}

// Function to turn on the buzzer
void buzzerActivate() {
    buzzerActive = true;  // Turn on the buzzer
    customBuzzerLoop();   // Update the buzzer state
}

// Function to turn off the buzzer
void buzzerDeactivate() {
    buzzerActive = false;  // Turn off the buzzer
    customBuzzerLoop();    // Update the buzzer state
}

#endif // BUZZER_H
