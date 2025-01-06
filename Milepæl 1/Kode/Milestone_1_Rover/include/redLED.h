#include <Arduino.h>

const int redLEDPin = 4;


void redLEDloop () {
    pinMode(redLEDPin, OUTPUT);
    digitalWrite(redLEDPin, HIGH);
}

TaskHandle_t redLEDtoggle;

void redLEDtoggle(void* pvParameters) {
    while (true){
        redLEDloop();
        vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to debounce

    }
}
