#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring_CLASSES.h>
#include <ESP32Servo.h>
#include <servoarm.h>
#include <joystick_drive.h>

  // ************************ START SERVO ARM ************************ //

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

 // ---------------------------------- LOOP CODE FOR SERVO ARM -------------------------------------------

  // void loop() 
// {
  // Grab servo   
  // for(int i = 180; i > 0; i-=3) 
  // {
  //   servoGrab.write(i);
  //   delay(10);
  // }
  // delay(225);
  // for(int i = 0; i < 180; i+=3) 
  // {
  //   servoGrab.write(i);
  //   delay(10);
  // }
  // delay(225);

  // // Bottom servo   
  // for(int i = 180; i > 0; i-=3) 
  // {
  //   servoBottom.write(i);
  //   servoGrab.write(i);
  //   delay(10);
  //   servoGrab.write(i);
  // }
  // delay(225);
  // for(int i = 0; i < 180; i+=3) 
  // {
  //   servoBottom.write(i);
  //   delay(10);
  // }
  // delay(225);

  //   // Right servo   
  // for(int i = 180; i > 0; i-=3) 
  // {
  //   servoRight.write(i);
  //   delay(10);
  // }
  // delay(225);
  // for(int i = 0; i < 180; i+=3) 
  // {
  //   servoRight.write(i);
  //   delay(10);
  // }
  // delay(225);

  //     // Left servo   
  // for(int i = 180; i > 0; i-=3) 
  // {
  //   servoLeft.write(i);
  //   delay(10);
  // }
  // delay(225);
  // for(int i = 0; i < 180; i+=3) 
  // {
  //   servoLeft.write(i);
  //   delay(10);
  // }
  // delay(225);
// }


// ************************ END SERVO ARM ************************ //

// ------------------------------------------------------------------------------------------------

// // Alt fungerende kode herunder

int incomingByte = 0; // for incoming serial data

// MotorController autoMotors(25, 26, 14, 12);  // A1, A2, B1, B2

// Pins for XSHUT
#define XSHUT_RIGHT 16   // XSHUT pin for højre sensor
#define XSHUT_LEFT 17    // XSHUT pin for venstre sensor
#define XSHUT_FRONT 19    // XSHUT pin for front sensor

VL53L0X sensorRight;
VL53L0X sensorLeft;
VL53L0X sensorFront;

// // Pin for buzzer module
// #define buzzerPin 33    // Buzzer sensor

const int PWM_CHANNEL = 0;    // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 500;     // Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz
const int PWM_RESOLUTION = 8; // We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits 

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int LED_OUTPUT_PIN = 33;

const int DELAY_MS = 0;  // delay between fade increments


void setup() {

  // Setting serial monitor port
  Serial.begin(115200);

// ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

  // ledcAttachPin(uint8_t pin, uint8_t channel);
  ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);

  Wire.begin(); // Begin I2C communication
  
  // Modtager modul for ESP32
  receiveESP32();

  // Buzzer setup import
  buzzerSetup();



  // *********************** SENSOR CONFIG START ************************ //

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

  // *********************** SENSOR CONFIG END ************************ //

  // -----------------------------------------------------------------------------------------------
}

void loop() {

  // ****** TEST OF MANUAL DRIVE MODE ****** //

  Serial.println("Starting the rover with maunal drive mode");
  manualMode();

  // Serial.println("Starting the automatic drive mode");
  // automaticDriveMode();

  

  // ************************ END MANUAL DRIVE MODE ************************ //

  // ------------------------------------------------------------------------------------------------



  // ------------------------------------------------------------------------------------------------
};

