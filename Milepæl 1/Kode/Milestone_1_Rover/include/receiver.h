#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>

#pragma once

// Define the FreeRTOS queue
extern QueueHandle_t q; // Queue for communication between tasks


// Structure to receive joystick data
typedef struct struct_message {
    int positionX;
    int positionY;
    bool toggleState;
    int positionXmotor;
    int positionYmotor;
    bool toggleDriveMode;
} struct_message;

// Global variable to hold received data
extern struct_message myJoystick;

// Callback function to execute when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&myJoystick, incomingData, sizeof(myJoystick));

    // Serial.print("Bytes received: ");
    // Serial.println(len);
    // Serial.print("X position: ");
    // Serial.println(myJoystick.positionXmotor);
    // Serial.print("Y position: ");
    // Serial.println(myJoystick.positionYmotor);
    Serial.print("Toggle state: ");
    Serial.println(myJoystick.toggleDriveMode);

    // Send the received data to the FreeRTOS queue
    if (q != NULL) {
        if (xQueueSend(q, &myJoystick, (TickType_t)0) != pdTRUE) {
            Serial.println("Failed to send to queue");
        }
    }
}

// Listen task
void listen(void *parameter) {
    // Initialize Wi-Fi and ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        vTaskDelete(NULL); // End the task if initialization fails
        return;
    }

    // Register the receive callback
    esp_now_register_recv_cb(OnDataRecv);

    // Keep the task alive
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay to prevent task starvation
    }
}