// /* ESP-NOW sending joystick position X and Y to a specific mac address
//    Data is only send every second controlled by a delay() call.
//    The program blinks GPIO 18 for about 0.1 second for every transmission.
//    Originally by Rui Santos - Random Nerd Tutorials
//    Edited and added code by Per Dahlstroem */
// #include <esp_now.h>
// #include <WiFi.h>

// #define VRX_PIN  39 // ESP32 pin 4 GPIO39 (ADC3) connected to VRX pin
// #define VRY_PIN  36 // ESP32 pin 3 GPIO36 (ADC0) connected to VRY pin
// #define joystickClick 33 // Joystick pin for clicking

// int valueX = 0; // to store the X-axis value
// int valueY = 0; // to store the Y-axis value
// extern bool buttonPressed = false;

// // Structure  to send valueX and valueY
// // Must match the receiver structure
// typedef struct struct_message {
//   int positionX;
//   int positionY;
//   bool toggleState;
    // int positionXmotor;
    // int positionYmotor;
    // bool toggleDriveMode;
// } struct_message;

// // Create a struct_message called myJoystick
// struct_message myJoystick;

// // Set the receiver ESP32 board address in a array of unsigned 8 bit integers.
// uint8_t myBoardAddress[] = {0xD0, 0xEF, 0x76, 0xEE, 0xED, 0x24};

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


//   // Fill X and Y analog values on ADC's 
//   // i.e. joystick positions into the myJoystick data structure
//    myJoystick.positionX = valueX;
//    myJoystick.positionY = valueY;
//    myJoystick.toggleState = joystickClick;

//   // Print data to Serial Monitor on VSC
//   Serial.print("x = ");
//   Serial.println(myJoystick.positionX);
//   Serial.print("y = ");
//   Serial.println(myJoystick.positionY);

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
//   delay(50);
//   digitalWrite(18, LOW);  // Turn GPIO 18 i.e. LED off
//   Serial.println("---------------------------------------------------------------");
//   delay(0);
// }