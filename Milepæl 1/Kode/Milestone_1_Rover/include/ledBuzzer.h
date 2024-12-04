#include <Arduino.h>

const int buzzerPin = 5; // Connect the passive buzzer to digital pin 8
const int redLEDPin = 18; // Red LED Pin

void buzzerSetup() {
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
  pinMode(redLEDPin, OUTPUT);    // Set the LED pin as output
  tone(buzzerPin, 400);  // Generate a 1000 Hz tone
  digitalWrite(redLEDPin, HIGH); // Turn on the LED
}

void buzzerActive() {
    tone(buzzerPin, 400);
    digitalWrite(redLEDPin, HIGH);
}