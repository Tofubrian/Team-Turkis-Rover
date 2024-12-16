// /* ESP-NOW sending joystick position X and Y to a specific mac address
//    Data is only send every second controlled by a delay() call.
//    The program blinks GPIO 18 for about 0.1 second for every transmission.
//    Originally by Rui Santos - Random Nerd Tutorials
//    Edited and added code by Per Dahlstroem */
// #include <esp_now.h>
// #include <WiFi.h>

// #pragma once

// #define VRX_PIN  36 // ESP32 pin Servo X
// #define VRY_PIN  37 // ESP32 pin Servo Y
// #define joystickClick 21 // Joystick pin for clicking motor
// #define VRX_PIN_Motor 32 // ESP32 pin Servo X
// #define VRY_PIN_Motor 39 // ESP32 pin Servo Y
// #define joystickClick_Motor 38 // ESP32 pin joystick click changing axes


// int valueX = 0; // to store the X-axis value
// int valueY = 0; // to store the Y-axis value
// extern bool buttonPressed = false;
// int valueX_Motor = 0; // Store X-axis value for motor
// int valueY_Motor = 0; // Store X-axis value for motor
// extern bool buttonPressed_Motor = false; // Starting the bool for motor off

// // Structure  to send valueX and valueY
// // Must match the receiver structure
// typedef struct struct_message {
//   int positionX;
//   int positionY;
//   bool toggleState;
//   int positionXmotor;
//   int positionYmotor;
//   bool toggleDriveMode;
// } struct_message;

// // Create a struct_message called myJoystick
// struct_message myJoystick;

// // Set the receiver ESP32 board address in a array of unsigned 8 bit integers.
// uint8_t myBoardAddress[] = {0xd0, 0xef, 0x76, 0xf0, 0x01, 0x6c};

// esp_now_peer_info_t peerInfo;

// // Callback function that is run every time data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   char macStr[18];
//   snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//   mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//   Serial.print("To receiver MAC address: ");Serial.println(macStr);
//   Serial.print("Packet delivery status: ");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? 
//   "Delivery Success, receiver acknowledge." : 
//   "Delivery Fail, no receiver acknowledge.");
// }

// void setup() {
//   // Set the ADC attenuation to 11 dB (up to ~3.3V input)
//   analogSetAttenuation(ADC_11db);

//   // Init Serial Monitor
//   Serial.begin(115200);

//   // initialize digital pin GPIO 18 as an output.
//   pinMode(joystickClick, INPUT_PULLUP);
//   pinMode(joystickClick_Motor, INPUT_PULLUP);

//   // Set device in Wi-Fi Station mode for ESP-NOW to function on WIFI.
//   // ESP-NOW does not require connection to an AP to function.
//   WiFi.mode(WIFI_STA);

//   // Init the ESP-NOW protocol
//   if (esp_now_init() != ESP_OK) {Serial.println("Error initializing ESP-NOW"); return;}

//   // Register a call Back or CB function with ESP-NOW to be called when the
//   // ESP-NOW function esp_now_send() sends data to get the status of the transmission.
//   esp_now_register_send_cb(OnDataSent);

//   // Register peer
//   memcpy(peerInfo.peer_addr, myBoardAddress, 6);
//   peerInfo.channel = 0;  
//   peerInfo.encrypt = false;

//   // Add peer        
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
// }

// void loop() {
//   // Read X and Y analog values on ADC's
//   valueX = analogRead(VRX_PIN);
//   valueY = analogRead(VRY_PIN);
//   buttonPressed = digitalRead(joystickClick);
//   valueX_Motor = analogRead(VRX_PIN_Motor);
//   valueY_Motor = analogRead(VRY_PIN_Motor);
//   buttonPressed_Motor = digitalRead(joystickClick_Motor);


//   // Fill X and Y analog values on ADC's 
//   // i.e. joystick positions into the myJoystick data structure
//    myJoystick.positionX = valueX;
//    myJoystick.positionY = valueY;
//    myJoystick.toggleState = joystickClick;
//    myJoystick.positionXmotor = valueX_Motor;
//    myJoystick.positionYmotor = valueY_Motor;
//    myJoystick.toggleDriveMode = joystickClick_Motor;

//   // Print data to Serial Monitor on VSC
//   Serial.print("x = ");
//   Serial.println(myJoystick.positionX);
//   delay(500);
//   Serial.print("y = ");
//   Serial.println(myJoystick.positionY);
//   delay(500);
//   Serial.print("x motor = ");
//   Serial.println(myJoystick.positionXmotor);
//   delay(500);
//   Serial.print("y motor = ");
//   Serial.println(myJoystick.positionYmotor);
//   delay(500);


//   // Send the myJoystick structure via ESP-NOW
//   esp_err_t result = esp_now_send(myBoardAddress, (uint8_t *) &myJoystick, sizeof(myJoystick));
//   if (result == ESP_OK) {
//     uint8_t mac[6]; WiFi.macAddress(mac);
//     char macStr[18];
//     snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
//     mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
//     Serial.print(sizeof(myJoystick)); Serial.print(" byte data emitted with success from mac address:");
//     Serial.println(macStr);
//     digitalWrite(18, HIGH); // Turn GPIO 18 i.e. LED on
//   }
//   else {
//     Serial.println("Error emitting data");
//   }
//   // delay(50);
//   // digitalWrite(18, LOW);  // Turn GPIO 18 i.e. LED off
//   // Serial.println("---------------------------------------------------------------");
//   // delay(0);
// }