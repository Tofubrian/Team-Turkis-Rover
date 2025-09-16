// #include <esp_now.h>
// #include <WiFi.h>
// #include <Wire.h>

// #pragma once

// #define VRX_PIN  36 // ESP32 pin Servo X left
// #define VRY_PIN  39 // ESP32 pin Servo Y left
// #define joystickClick 27 // Joystick pin for clicking motor left click
// #define VRX_PIN_Motor 34 // ESP32 pin motor right
// #define VRY_PIN_Motor 35 // ESP32 pin motor right 
// #define joystickClick_Motor 32 // ESP32 pin joystick click changing axes right click

// int valueX = 0; // to store the X-axis value
// int valueY = 0; // to store the Y-axis value
// int valueX_Motor = 0; // Store X-axis value for motor
// int valueY_Motor = 0; // Store X-axis value for motor

// bool toggleDrive = false;
// bool lastClickState_Motor = HIGH; // Assuming button is not pressed initially
// bool toggleServos = false;
// bool lastClickState_servos = HIGH; // Starting button not pressed

// unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
// unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers

// // Structure to send valueX and valueY
// typedef struct struct_message {
//     int positionX;
//     int positionY;
//     bool toggleState;
//     int positionXmotor;
//     int positionYmotor;
//     bool toggleDriveMode;
// } struct_message;

// // Create a struct_message called myJoystick
// struct_message myJoystick;

// // Set the receiver ESP32 board address in an array of unsigned 8 bit integers.
// uint8_t myBoardAddress[] = {0x00, 0x4b, 0x12, 0x2F, 0xbc, 0x24};

// esp_now_peer_info_t peerInfo;

// // Callback function that is run every time data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//     char macStr[18];
//     snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//     Serial.print("To receiver MAC address: ");
//     Serial.println(macStr);
//     Serial.print("Packet delivery status: ");
//     Serial.println(status == ESP_NOW_SEND_SUCCESS ? 
//     "Delivery Success, receiver acknowledge." : 
//     "Delivery Fail, no receiver acknowledge.");
// }

// void setup() {
//     // Set the ADC attenuation to 11 dB (up to ~3.3V input)
//     analogSetAttenuation(ADC_11db);

//     // Init Serial Monitor
//     Serial.begin(115200);

//     // Initialize digital pins for input
//     pinMode(joystickClick, INPUT_PULLUP);
//     pinMode(joystickClick_Motor, INPUT_PULLUP);

//     // Set device in Wi-Fi Station mode for ESP-NOW to function on WIFI.
//     WiFi.mode(WIFI_STA);

//     // Init the ESP-NOW protocol
//     if (esp_now_init() != ESP_OK) { 
//         Serial.println("Error initializing ESP-NOW"); 
//         return; 
//     }

//     // Register a callback function with ESP-NOW
//     esp_now_register_send_cb(OnDataSent);

//     // Register peer
//     memcpy(peerInfo.peer_addr, myBoardAddress, 6);
//     peerInfo.channel = 0;  
//     peerInfo.encrypt = false;

//     // Add peer        
//     if (esp_now_add_peer(&peerInfo) != ESP_OK) {
//         Serial.println("Failed to add peer");
//         return;
//     }
// }

// void loop() {
//     unsigned long currentMillis = millis();

//     // Read joystick values for motor control
//     valueX_Motor = analogRead(VRX_PIN_Motor);
//     valueY_Motor = analogRead(VRY_PIN_Motor);

//     // Handle joystick button for driving toggle mode
//     bool currentButtonState = digitalRead(joystickClick_Motor);

//     if (currentButtonState == LOW && lastClickState_Motor == HIGH && (currentMillis - lastDebounceTime) > debounceDelay) {
//         toggleDrive = !toggleDrive;
//         Serial.println("Toggle drive is: ");
//         Serial.println(toggleDrive);
        
//         lastDebounceTime = currentMillis;
//     }
//     lastClickState_Motor = currentButtonState;

//     // Read joystick values for servo control
//     valueX = analogRead(VRX_PIN);
//     valueY = analogRead(VRY_PIN);

//     // Handle joystick button for servo mode change
//     bool currentButtonStateServo = digitalRead(joystickClick);

//     if (currentButtonStateServo == LOW && lastClickState_servos == HIGH && (currentMillis - lastDebounceTime) > debounceDelay) {
//         toggleServos = !toggleServos;
//         Serial.println("Toggle servos is: ");
//         Serial.println(toggleServos);
        
//         lastDebounceTime = currentMillis;
//     }
//     lastClickState_servos = currentButtonStateServo;

//     // Fill joystick structure
//     myJoystick.positionX = valueX;
//     myJoystick.positionY = valueY;
//     myJoystick.toggleState = toggleServos;
//     myJoystick.positionXmotor = valueX_Motor;
//     myJoystick.positionYmotor = valueY_Motor;
//     myJoystick.toggleDriveMode = toggleDrive;

//     // Print joystick state for debugging
//     Serial.print("PositionX Motor: ");
//     Serial.println(myJoystick.positionXmotor);
//     Serial.print("PositionY Motor: ");
//     Serial.println(myJoystick.positionYmotor);
//     Serial.print("Toggle Drive Mode: ");
//     Serial.println(myJoystick.toggleDriveMode);

//     Serial.print("PositionX Servo: ");
//     Serial.println(myJoystick.positionX);
//     Serial.print("PositionY Servo: ");
//     Serial.println(myJoystick.positionY);
//     Serial.print("Toggle Servo Mode: ");
//     Serial.println(myJoystick.toggleState);

//     // Send the myJoystick structure via ESP-NOW
//     esp_err_t result = esp_now_send(myBoardAddress, (uint8_t *) &myJoystick, sizeof(myJoystick));
//     if (result == ESP_OK) {
//         Serial.println("Data sent successfully");
//     } else {
//         Serial.println("Error sending data");
//     }

//     // Short delay for debounce
//     delay(100);
// }
