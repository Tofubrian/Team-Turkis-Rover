#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring_CLASSES.h>
#include <receiver.h>

// Joystick predefined values
const int joystick_center = 1900; // Center of the joystick // 2048
const int joystick_threshold = 300; // Dead zone threshold // 200
const int joystick_max_value = 4095; // Maximum reading for x,y axis
const int joystick_min_value = 462; // Minimum reading for x,y axis
const int MOTOR_MAX_SPEED = 255; // Maximum motor speed

MotorController motors(25, 26, 14, 12);  // A1, A2, B1, B2

// int incomingByte = 0; // for incoming serial data

// // MotorController autoMotors(25, 26, 14, 12);  // A1, A2, B1, B2

// Pins for XSHUT
#define XSHUT_RIGHT 16   // XSHUT pin for højre sensor
#define XSHUT_LEFT 17    // XSHUT pin for venstre sensor
#define XSHUT_FRONT 18    // XSHUT pin for front sensor

VL53L0X sensorRight;
VL53L0X sensorLeft;
VL53L0X sensorFront;



const int PWM_CHANNEL = 0;    // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 500;     // Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz
const int PWM_RESOLUTION = 8; // We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits 

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int LED_OUTPUT_PIN = 33;

const int DELAY_MS = 0;  // delay between fade increments


void setupMotor() {

  // Setting serial monitor port
  Serial.begin(115200);

// ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

  // ledcAttachPin(uint8_t pin, uint8_t channel);
  ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);

  Wire.begin(); // Begin I2C communication

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



void automaticDriveMode() {

  // ------------------------------------------------------------------------------------------------

  // ************************ AUTOMATIC DRIVE MODE ************************ //

  int distanceLeft = sensorLeft.readRangeSingleMillimeters();
  int distanceRight = sensorRight.readRangeSingleMillimeters();
  int distanceFront = sensorFront.readRangeSingleMillimeters();

  Serial.print("Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" Right Distance: ");
  Serial.println(distanceRight);
  Serial.print(" Front Distance: ");
  Serial.println(distanceFront);

    if (distanceFront <= 220) {
        ledcWrite(PWM_CHANNEL, 500);
        motors.forwardSaveRight();
        ledcWrite(PWM_CHANNEL, 0);
    }
    else if (distanceFront <= 200 && distanceRight <= 200) {
        motors.forwardSaveLeft();
    }
    else if (distanceFront <= 200 && distanceLeft <= 200) {
        motors.forwardSaveRight();
    }
    else if (distanceLeft <= 200 && distanceRight <= 200) {
        motors.forwardSaveRight();
        delay(100);
    }
    else if (distanceLeft <= 200) {
        motors.turnRight();
        delay(100);
    } 
    else if (distanceRight <= 200) {
        motors.turnLeft();
        delay(100);
    } 
    else {
        motors.forward();
    }

  // Timeout handling for both sensors
  if (sensorLeft.timeoutOccurred()) { 
    Serial.println(" TIMEOUT on Left Sensor");
  }
  if (sensorRight.timeoutOccurred()) { 
    Serial.println(" TIMEOUT on Right Sensor");
  }

  if (sensorFront.timeoutOccurred()) { 
    Serial.println(" TIMEOUT on Front Sensor");
  }
}
  // ************************ END AUTOMATIC DRIVE MODE ************************ //

void manualMode() {
    // int inputX = analogRead(ManualpinX); // Read X-axis value  
    // int inputY = analogRead(ManualpinY); // Read X-axis value

    int joyPinX = myJoystick.positionXmotor;
    int joyPinY = myJoystick.positionYmotor;


    Serial.println("X value is ");
    Serial.println(joyPinX);

    Serial.println("Y value is ");
    Serial.println(joyPinY);

    if (joyPinY > joystick_center + joystick_threshold) { // Forward 
        if (joyPinX > joystick_center + joystick_threshold) {
            motors.turnSmoothLeft(); // Forward Left
            Serial.println("Turning forward left");
        }
        else if (joyPinX < joystick_center - joystick_threshold) {
            motors.turnRight(); // Forward Right
            Serial.println("Turning forward right");
        }
        else {
            motors.forward(); // Straight Forward
            Serial.println("Going forward");
        }
    }
    else if (joyPinY < joystick_center - joystick_threshold) { // Backward
        if (joyPinX > joystick_center + joystick_threshold) {
            motors.turnLeft(); // Backward Left
            Serial.println("Backwards left");
        }
        else if (joyPinX < joystick_center - joystick_threshold) {
            motors.turnRight(); // Backward Right
            Serial.println("Backwards right");
        }
        else {
            motors.backward(); // Straight Backward
            Serial.println("Going backward");
        }
    }
    else if (joyPinX > joystick_center + joystick_threshold) { // Idle movement Right
        motors.turnLeft();
        Serial.println("Turning idle left");
    }
    else if (joyPinX < joystick_center - joystick_threshold) { // Idle movement Left
        motors.turnRight();
        Serial.println("Turning idle right");
    }
    else { // Idle
        motors.stop();
        Serial.println("Idle mode");
    }
    // Delay here for smooth movements with the joystick
    delay(100);
}

// SETUP FOR BUTTON DRIVE TOGGLE //

// bool toggleDrive = false;
// bool lastClickState_Motor = false;

TaskHandle_t driveToggleTaskHandle;

void driveToggle(void* pvParameters) {
    while (true) {
        // int clickValue_motor = myJoystick.toggleDriveMode;
        
        // if (clickValue_motor == LOW && lastClickState_Motor == HIGH) {
        //     toggleDrive = !toggleDrive;
        //     Serial.println("Drive mode toggled");
        // }
        // lastClickState_Motor = clickValue_motor;
        bool toggleDrive = myJoystick.toggleDriveMode;

        // Serial.print("Drive mode: ");
        // Serial.println(toggleDrive ? "Automatic" : "Manual");
        
        if (toggleDrive) {
            automaticDriveMode();
            Serial.println("GOING AUTOMATIC");
            
        } else {
            manualMode();
            Serial.println("MANUAL");
            Serial.println(myJoystick.positionXmotor);
            Serial.print("Y position: ");
            Serial.println(myJoystick.positionYmotor);
            
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to debounce
    }
}

  // ------------------------------------------------------------------------------------------------

