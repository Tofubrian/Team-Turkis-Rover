#include <Arduino.h>


// Define pins here pretty pleaaase
// Change to the correct number
// Change pin variable name to what we build
#define LED1 12

// Copy the below code to define new pins

// #define LEDx 11


// Initialize pins so they are ready to use in code.
// Example below
void setup () {
    pinMode(redLED, OUTPUT);
    
    // Copy the below code to initialize another led

    // pinMode(LEDx, OUTPUT);
}

void LEDTurnOn () {
    digitalWrite(LED1, HIGH);

}

void LEDTurnOff () {
    digitalWrite(LED1, LOW);

}
// Tobias test test test 