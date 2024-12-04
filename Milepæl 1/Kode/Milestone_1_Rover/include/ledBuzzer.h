#include <Arduino.h>

const int buzzerPin = 5; // Connect the passive buzzer to digital pin 8
const int redLEDPin = 27; // Red LED Pin

void buzzerSetup() {
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
  pinMode(redLEDPin, OUTPUT);    // Set the LED pin as output
  digitalWrite(redLEDPin, LOW); // Start the LED in low, so it only activates when buzzerActive is called
}

void buzzerActive() {
    tone(buzzerPin, 400);
    digitalWrite(redLEDPin, HIGH);
}