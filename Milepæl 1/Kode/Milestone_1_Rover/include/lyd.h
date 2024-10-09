#include <Arduino.h>
#include <Wire.h>

//Vores lydfunktion

// Define the melody
int melody[] = {
    262, 294, 330, 349, 392, 440, 494, 523
};
// Define note durations (in milliseconds)
int noteDurations[] = {
    500, 500, 500, 500, 500, 500, 500, 500
};

void setup() {
    // No setup needed for buzzer
}

void loop() {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
        // Calculate the duration of each note
        int noteDuration = noteDurations[thisNote];
        tone(8, melody[thisNote], noteDuration);
        // Pause for the note's duration plus a bit
        delay(noteDuration);
        // Stop the tone
        noTone(8);
    }
    // Pause between repetitions
    delay(1000);
}