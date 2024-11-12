#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring_CLASSES.h>
#include <ESP32Servo.h>
#include <servoarm.h>

// Definer pins osv for rover arm her
// Servo servoGrab;
// Servo servoBottom;
// Servo servoRight;
// Servo servoLeft;

// RoverArm servoMotors(17, 18, 5, 16); // Grab, Bunden, Højre, Venstre

// void setup() 
// {
//   ESP32PWM::allocateTimer(0);
//   ESP32PWM::allocateTimer(1);
//   ESP32PWM::allocateTimer(2);
//   ESP32PWM::allocateTimer(3);

//   // servoGrab.setPeriodHertz(50);    
//   // servoGrab.attach(17, 500, 2500);

//   // servoBottom.setPeriodHertz(50);    
//   // servoBottom.attach(18, 500, 2500);
  
//   // servoRight.setPeriodHertz(50);    
//   // servoRight.attach(5, 500, 2500);
  
//   // servoLeft.setPeriodHertz(50);    
//   // servoLeft.attach(16, 500, 2500);

// }

// void loop() 
// {
//   servoMotors.pinch();  // Close the grab servo
//   delay(2000);  // Wait for 2 seconds

//   servoMotors.open();  // Open the grab servo
//   delay(2000);  // Wait for 2 seconds
  
//  servoMotors.BottomLeft(); //Move the bottom servo right
//   delay(2000); //Wait for 2 seconds

//   servoMotors.BottomRight(); //Move the bottom servo left
//   delay(2000); //Wait for 2 seconds

//  servoMotors.ArmUp();
//  delay(2000);
 
//   servoMotors.ArmDown();
//  delay(2000);

//  servoMotors.ArmForward();
//  delay(2000);
  
//   servoMotors.ArmBackward();
//   delay(2000);
  
  
//   // // Grab servo   
//   // for(int i = 180; i > 0; i-=3) 
//   // {
//   //   servoGrab.write(i);
//   //   delay(10);
//   // }
//   // delay(225);
//   // for(int i = 0; i < 180; i+=3) 
//   // {
//   //   servoGrab.write(i);
//   //   delay(10);
//   // }
//   // delay(225);

//   // // Bottom servo   
//   // for(int i = 180; i > 0; i-=3) 
//   // {
//   //   servoBottom.write(i);
//   //   servoGrab.write(i);
//   //   delay(10);
//   //   servoGrab.write(i);
//   // }
//   // delay(225);
//   // for(int i = 0; i < 180; i+=3) 
//   // {
//   //   servoBottom.write(i);
//   //   delay(10);
//   // }
//   // delay(225);

//   //   // Right servo   
//   // for(int i = 180; i > 0; i-=3) 
//   // {
//   //   servoRight.write(i);
//   //   delay(10);
//   // }
//   // delay(225);
//   // for(int i = 0; i < 180; i+=3) 
//   // {
//   //   servoRight.write(i);
//   //   delay(10);
//   // }
//   // delay(225);

//   //     // Left servo   
//   // for(int i = 180; i > 0; i-=3) 
//   // {
//   //   servoLeft.write(i);
//   //   delay(10);
//   // }
//   // delay(225);
//   // for(int i = 0; i < 180; i+=3) 
//   // {
//   //   servoLeft.write(i);
//   //   delay(10);
//   // }
//   // delay(225);
// }


// // Alt fungerende kode herunder

int incomingByte = 0; // for incoming serial data

MotorController motors(25, 26, 14, 12);  // A1, A2, B1, B2

// Pins for XSHUT
#define XSHUT_RIGHT 16   // XSHUT pin for højre sensor
#define XSHUT_LEFT 17    // XSHUT pin for venstre sensor
#define XSHUT_FRONT 19    // XSHUT pin for front sensor

VL53L0X sensorRight;
VL53L0X sensorLeft;
VL53L0X sensorFront;

// Pin for buzzer module
#define buzzerPin 33    // Buzzer sensor

const int PWM_CHANNEL = 0;    // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 500;     // Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz
const int PWM_RESOLUTION = 8; // We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits 

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int LED_OUTPUT_PIN = 33;

const int DELAY_MS = 0;  // delay between fade increments

void setup() {

// ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

  // ledcAttachPin(uint8_t pin, uint8_t channel);
  ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);
  Serial.begin(115200);
  Wire.begin(); // Begin I2C communication

  // Configure XSHUT pins for sensorLeft and sensorRight and sensorFront
  pinMode(XSHUT_LEFT, OUTPUT);
  pinMode(XSHUT_RIGHT, OUTPUT);
  pinMode(XSHUT_FRONT, OUTPUT);

  // Deactivate both sensors at the beginning
  digitalWrite(XSHUT_LEFT, LOW);
  digitalWrite(XSHUT_RIGHT, LOW);
  digitalWrite(XSHUT_FRONT, LOW);
  delay(10);  // Small delay for sensor initialization

  // Initialize the left sensor
  digitalWrite(XSHUT_LEFT, HIGH);
  delay(10); // Allow time for sensor startup
  if (!sensorLeft.init()) {
    Serial.println("Failed to initialize left sensor!");
    while (1) {}
  }
  sensorLeft.setAddress(0x31); // Set unique address for left sensor
  sensorLeft.startContinuous();

  // Initialize the right sensor
  digitalWrite(XSHUT_RIGHT, HIGH);
  delay(10); // Allow time for sensor startup
  if (!sensorRight.init()) {
    Serial.println("Failed to initialize right sensor!");
    while (1) {}
  }
  sensorRight.setAddress(0x30); // Set unique address for right sensor
  sensorRight.startContinuous();

  // Initialize the right sensor
  digitalWrite(XSHUT_FRONT, HIGH);
  delay(10); // Allow time for sensor startup
  if (!sensorFront.init()) {
    Serial.println("Failed to initialize Front sensor!");
    while (1) {}
  }
  sensorFront.setAddress(0x29); // Set unique address for front sensor
  sensorFront.startContinuous();

  // // Setup code for joystick mapping
  // // Connect to WiFi
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");

  // // Initialize motors
  // initMotors();

  // // Route to handle joystick data (GET request)
  // server.on("/joystick", HTTP_GET, [](AsyncWebServerRequest *request){
  //   if (request->hasParam("data")) {
  //     String data = request->getParam("data")->value();
  //     handleJoystick(data);
  //   }
  //   request->send(200, "text/plain", "Joystick Data Received");
  // });

  // // Start the server
  // server.begin();


}

void loop() {

  motors.forward();
  delay(500);

  motors.backward();
  delay(500);

  motors.turnRight();
  delay(500);

  motors.turnLeft();
  delay(500);
  // int distanceLeft = sensorLeft.readRangeSingleMillimeters();
  // int distanceRight = sensorRight.readRangeSingleMillimeters();
  // int distanceFront = sensorFront.readRangeSingleMillimeters();

  // Serial.print("Left Distance: ");
  // Serial.print(distanceLeft);
  // Serial.print(" Right Distance: ");
  // Serial.println(distanceRight);
  // Serial.print(" Front Distance: ");
  // Serial.println(distanceFront);

  //   if (distanceFront <= 220) {
  //       ledcWrite(PWM_CHANNEL, 500);
  //       motors.forwardSaveRight();
  //       ledcWrite(PWM_CHANNEL, 0);
  //   }
  //   else if (distanceFront <= 200 && distanceRight <= 200) {
  //       motors.forwardSaveLeft();
  //   }
  //   else if (distanceFront <= 200 && distanceLeft <= 200) {
  //       motors.forwardSaveRight();
  //   }
  //   else if (distanceLeft <= 200 && distanceRight <= 200) {
  //       motors.forwardSaveRight();
  //       delay(100);
  //   }
  //   else if (distanceLeft <= 200) {
  //       motors.turnRight();
  //       delay(100);
  //   } 
  //   else if (distanceRight <= 200) {
  //       motors.turnLeft();
  //       delay(100);
  //   } 
  //   else {
  //       motors.forward();
  //   }

  // // Timeout handling for both sensors
  // if (sensorLeft.timeoutOccurred()) { 
  //   Serial.println(" TIMEOUT on Left Sensor");
  // }
  // if (sensorRight.timeoutOccurred()) { 
  //   Serial.println(" TIMEOUT on Right Sensor");
  // }

  // if (sensorFront.timeoutOccurred()) { 
  //   Serial.println(" TIMEOUT on Front Sensor");
  // }
};

