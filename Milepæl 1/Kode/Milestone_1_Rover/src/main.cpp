// *********************** INCLUDE OF ALL LIBRARIES NEEDED ************************ //

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring_CLASSES.h>
#include <ESP32Servo.h>
#include <robotArm.h>
#include <allMotorControls.h>
#include <receiver.h>

// *********************** END INCLUDE LIBRARIES ************************ //
// ------------------------------------------------------------------------------------------------

// // Alt fungerende kode herunder

// MotorController autoMotors(25, 26, 14, 12);  // A1, A2, B1, B2
// Pin defintion moved to allMotorControls.h


// Easy way to change pin definitions without leaving main file - not connected
// Pin defintion for buzzer and LED for backlight
// int buzzerPin = 5;
// int redLEDPin = 27;
// ---------------------------------------------------------------------------------------------------------------


QueueHandle_t myQueue;  // Declare the queue handle


void setup() {
// Setting serial monitor speed for debug
  Serial.begin(115200);
  
  sensorSetup();

  // Modtager modul for ESP32
  receiverESP32();

//   // Buzzer setup import - NOT ATTACHED ON ROVERS YET, commented out
//   buzzerSetup();

  // Robot arm setup section included
  robotArmSetup();

  // Queue created here, but maybe item size needs to adjusted. idk
  myQueue = xQueueCreate(10, sizeof(int));

  // Check the queue for successful creation
  if (myQueue == NULL) {
    Serial.println("Queue failed, finitto, no go amigo");
  }
  else {
    Serial.println("Queue up and running.");
  }
    


  // *********************** DEFINITION OF THREADING TASKS ************************ //

  // ESP32 sender thread might be smart, around 20 in vTaskDelay

  // Task for tmoving servos
  // xTaskCreatePinnedToCore(
  //     moveServos,
  //     "Move Servos",
  //     10000,
  //     NULL,
  //     2,
  //     &moveServosTaskHandle,
  //     0
  // );

  // Task for implementing driving modes
  xTaskCreatePinnedToCore(
    driveToggle,
    "Switch drive modes",
    10000,
    NULL,
    1,
    &driveToggleTaskHandle,
    0
  );



  // *********************** END OF DEFINTION OF THREADING TASKS ************************ //

  
  // -----------------------------------------------------------------------------------------------
}

void loop() {
  // ------------------------------------------------------------------------------------------------
};

