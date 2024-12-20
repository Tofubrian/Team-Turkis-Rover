#include <Arduino.h>

const int buzzerPin = 5; // Connect the passive buzzer to digital pin 5
 

void customBuzzerLoop() {
  // Turn on the buzzer
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
  tone(buzzerPin, 400); // Generate a 400 Hz tone
//   delay(2000);          // Wait for 2 seconds

  // Turn off the buzzer
//   noTone(buzzerPin);    // Stop the buzzer
//   delay(1000);          // Wait for 1 second
}

TaskHandle_t buzzertoggle;

void buzzertoggle(void* pvParameters) {
    while (true){
        customBuzzerLoop();
        vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to debounce

    }
}