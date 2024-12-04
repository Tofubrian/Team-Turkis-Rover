#include <Arduino.h>

extern int buzzerPin; // Connect the passive buzzer to digital pin 8
extern int redLEDPin; // Red LED Pin

// ************************* START BUZZER AND LED ************************* //

void buzzerSetup() {
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
  pinMode(redLEDPin, OUTPUT);    // Set the LED pin as output
  digitalWrite(redLEDPin, LOW); // Start the LED in low, so it only activates when buzzerActive is called
}

// ******* END BUZZER AND LED ******* // 

// ************************* START BUZZER AND LED FUNCTION ************************* //

void buzzerActive() {
    // Turns the buzzer on with 400hZ 
    tone(buzzerPin, 400);

    // Turns the LED backlight on
    digitalWrite(redLEDPin, HIGH);
}

// ************************* END BUZZER AND LED FUNCTION ************************* //