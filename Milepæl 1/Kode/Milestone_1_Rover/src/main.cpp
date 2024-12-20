// *********************** INCLUDE OF ALL LIBRARIES NEEDED ************************ //

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring_CLASSES.h>
#include <allMotorcontrols.h>
#include "receiver.h" // Include the receiver header for the listen task
#include <robotArm.h>

// *********************** END INCLUDE LIBRARIES ************************ //

// Task handles
TaskHandle_t ListenerTask;
TaskHandle_t ActionTask;
TaskHandle_t moveServosTaskHandle;

// FreeRTOS queue
QueueHandle_t q = NULL;
struct_message myJoystick;  // Definition of the global joystick data structure

// Act task to process received data
void act(void *parameter) {
    struct_message receivedData; // Struct to store received data
    for (;;) {
        // Wait for data from the queue
        if (xQueueReceive(q, &receivedData, portMAX_DELAY) == pdPASS) {
            Serial.println("Data received on Core 1:");
            Serial.print("X: ");
            Serial.println(receivedData.positionXmotor);
            Serial.print("Y: ");
            Serial.println(receivedData.positionYmotor);
            Serial.print("Toggle State: ");
            Serial.println(receivedData.toggleDriveMode);
        }
        vTaskDelay(pdMS_TO_TICKS(20)); // Delay for processing
    }
}

void setup() {
    // Setting serial monitor speed for debug
    Serial.begin(115200);

    // Setup motor functions
    setupMotor();

    // Setup servo arm
    robotArmSetup();

    // Create the queue to store struct_message data
    q = xQueueCreate(20, sizeof(struct_message));
    if (q != NULL) {
        Serial.println("Queue created successfully");
    } else {
        Serial.println("Failed to create queue");
        return;
    }

    // *********************** DEFINITION OF THREADING TASKS ************************ //

    // Create the listener task on core 0
    xTaskCreatePinnedToCore(
        listen,         // Function to implement the task
        "ListenerTask", // Name of the task
        10000,          // Stack size in words
        NULL,           // Task input parameter
        2,              // Priority of the task
        &ListenerTask,  // Task handle
        0);             // Core on which to run

    // Create the action task on core 1
    xTaskCreatePinnedToCore(
        act,            // Function to implement the task
        "ActionTask",   // Name of the task
        10000,          // Stack size in words
        NULL,           // Task input parameter
        1,              // Priority of the task
        &ActionTask,    // Task handle
        1);             // Core on which to run
    
    xTaskCreatePinnedToCore(
        driveToggle,            // Function to implement the task
        "Drive Mode Toggle",   // Name of the task
        10000,          // Stack size in words
        NULL,           // Task input parameter
        1,              // Priority of the task
        &driveToggleTaskHandle,    // Task handle
        1);

    xTaskCreatePinnedToCore(
        moveServos, // Function to implement the task
        "Move Servos", // Name of the task
        10000, // Stack size in words
        NULL, // Task input parameter
        1, // Priority of the the task
        &moveServosTaskHandle, // Task handle
        2); // Core to run on

    // *********************** END OF DEFINITION OF THREADING TASKS ************************ //
}

void loop() {
    // loopAutomatic(); // Custom function from your library
}
