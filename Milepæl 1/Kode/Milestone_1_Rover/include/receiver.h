/*
  ESP-NOW joystick X and Y position receiver 
  Oroiginally by Rui Santos - Random Nerd Tutorials
  Edited by Per Dahlstroem*/

#include <esp_now.h>
#include <WiFi.h>

int valueX = 0; // to store the X-axis value
int valueY = 0; // to store the Y-axis value
extern bool buttonPressed = false; 

// Structure  to receive valueX and valueY
// Must match the sender structure
typedef struct struct_message {
  int positionX;
  int positionY;
  bool toggleState;
  int positionXmotor;
  int positionYmotor;
  bool toggleDriveMode;
} struct_message;

// Create a struct_message called myJoystick
struct_message myJoystick;

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&myJoystick, incomingData, sizeof(myJoystick));

    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("X position: ");
    Serial.println(myJoystick.positionX);
    Serial.print("Y position: ");
    Serial.println(myJoystick.positionY);
    Serial.print("Toggle state: ");
    Serial.println(myJoystick.toggleState ? "Pressed" : "Released");
}

void receiverESP32() {
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, register Call Back CB function
  // OnDataRecv to read received packet info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

