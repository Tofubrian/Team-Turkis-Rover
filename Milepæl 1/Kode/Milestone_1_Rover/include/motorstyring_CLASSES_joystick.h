#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

// Motor pins
const int pinA1 = 25;
const int pinA2 = 26;
const int pinB1 = 14;
const int pinB2 = 12;


// WiFi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Set up the web server
AsyncWebServer server(80);

// PWM settings
const int pwmFreq = 1000;  // PWM frequency in Hz (1 kHz)
const int pwmResolution = 8;  // 8-bit resolution
const int pwmChannelA1 = 0;
const int pwmChannelA2 = 1;
const int pwmChannelB1 = 2;
const int pwmChannelB2 = 3;

// Initialize motor controller
void initMotors() {
  ledcSetup(pwmChannelA1, pwmFreq, pwmResolution);
  ledcSetup(pwmChannelA2, pwmFreq, pwmResolution);
  ledcSetup(pwmChannelB1, pwmFreq, pwmResolution);
  ledcSetup(pwmChannelB2, pwmFreq, pwmResolution);

  ledcAttachPin(pinA1, pwmChannelA1);
  ledcAttachPin(pinA2, pwmChannelA2);
  ledcAttachPin(pinB1, pwmChannelB1);
  ledcAttachPin(pinB2, pwmChannelB2);
}

// Set motor speeds
void setMotorSpeed(int speedA1, int speedA2, int speedB1, int speedB2) {
  ledcWrite(pwmChannelA1, speedA1);
  ledcWrite(pwmChannelA2, speedA2);
  ledcWrite(pwmChannelB1, speedB1);
  ledcWrite(pwmChannelB2, speedB2);
}

// Handle the incoming joystick data
void handleJoystick(String data) {
  // Parse the JSON data
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, data);

  if (error) {
    Serial.println("Failed to parse JSON");
    return;
  }

  // Get the joystick values
  int xValue = doc["x"]; // Left/Right joystick
  int yValue = doc["y"]; // Up/Down joystick

  // Map joystick values (0-1023) to motor PWM range (0-255)
  int mappedX = map(xValue, 0, 1023, 0, 255);
  int mappedY = map(yValue, 0, 1023, 0, 255);

  // Dead zone
  if (abs(mappedX - 127) < 20) mappedX = 127;
  if (abs(mappedY - 127) < 20) mappedY = 127;

  // Forward/Backward
  if (mappedY < 127) {
    setMotorSpeed(0, mappedY, 0, mappedY);  // Move backward
  } else if (mappedY > 127) {
    setMotorSpeed(mappedY, 0, mappedY, 0);  // Move forward
  } else {
    setMotorSpeed(0, 0, 0, 0);  // Stop
  }

  // Left/Right turn
  if (mappedX < 127) {
    setMotorSpeed(0, mappedX, mappedY, 0);  // Turn left
  } else if (mappedX > 127) {
    setMotorSpeed(mappedX, 0, 0, mappedY);  // Turn right
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize motors
  initMotors();

  // Route to handle joystick data (GET request)
  server.on("/joystick", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("data")) {
      String data = request->getParam("data")->value();
      handleJoystick(data);
    }
    request->send(200, "text/plain", "Joystick Data Received");
  });

  // Start the server
  server.begin();
}

void loop() {
  // Nothing needed here, the server handles the rest
}



#ifndef MOTORSTYRING_CLASSES_JOYSTICK_H
#define MOTORSTYRING_CLASSES_JOYSTICK_H

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h> 

// Kode opdateret med kontrol af joystick forslag

class MotorController {
private:
    struct MotorPins {
        const int pinA1, pinA2, pinB1, pinB2;
    };

    MotorPins pins;
    const int pwmFreq = 1000;  // PWM frequency in Hz (1 kHz)
    const int pwmResolution = 8;  // 8-bit resolution
    const int pwmChannelA1 = 0;  // PWM channel for motor A, pin A1
    const int pwmChannelA2 = 1;  // PWM channel for motor A, pin A2
    const int pwmChannelB1 = 2;  // PWM channel for motor B, pin B1
    const int pwmChannelB2 = 3;  // PWM channel for motor B, pin B2

    
  

public:
    MotorController(int pinA1, int pinA2, int pinB1, int pinB2)
        : pins{pinA1, pinA2, pinB1, pinB2} {
        initMotors();
    }

    void initMotors() {
        // Set up PWM channels for each motor pin
        ledcSetup(pwmChannelA1, pwmFreq, pwmResolution);
        ledcSetup(pwmChannelA2, pwmFreq, pwmResolution);
        ledcSetup(pwmChannelB1, pwmFreq, pwmResolution);
        ledcSetup(pwmChannelB2, pwmFreq, pwmResolution);

        // Attach the motor pins to the respective PWM channels
        ledcAttachPin(pins.pinA1, pwmChannelA1);
        ledcAttachPin(pins.pinA2, pwmChannelA2);
        ledcAttachPin(pins.pinB1, pwmChannelB1);
        ledcAttachPin(pins.pinB2, pwmChannelB2);
    }

    void setMotorSpeed(int speed) {
        ledcWrite(pwmChannelA1, speed); // Activate motor A
        ledcWrite(pwmChannelA2, 0);     // Deactivate reverse for motor A
        ledcWrite(pwmChannelB1, speed); // Activate motor B
        ledcWrite(pwmChannelB2, 0);     // Deactivate reverse for motor B
    }

    void accelerateForward(int targetSpeed, int increment = 5, int delayMs = 100) {
        static int currentSpeed = 0; // Maintain current speed
        static unsigned long lastUpdateTime = 0; // Track the last update time

        unsigned long currentTime = millis();
        // Check if enough time has passed to update the speed
        if (currentTime - lastUpdateTime >= delayMs) {
            lastUpdateTime = currentTime;

            // Use a for loop to increment the speed
            for (int speed = currentSpeed; speed <= targetSpeed; speed += increment) {
                // Update motor speeds
                Serial.println("Accelerating.");
                Serial.println(speed);
                ledcWrite(pwmChannelA1, speed); // Activate motor A
                ledcWrite(pwmChannelA2, 0);      // Deactivate reverse for motor A
                ledcWrite(pwmChannelB1, speed); // Activate motor B
                ledcWrite(pwmChannelB2, 0);      // Deactivate reverse for motor B

                // Delay for a smoother acceleration
                delay(delayMs);

                // Break if we've reached the target speed
                if (speed >= targetSpeed) {
                    currentSpeed = targetSpeed; // Update currentSpeed to the target
                    Serial.println("At full speed.");
                    break; // Exit the loop once we've reached full speed
                }
            }
        }
    }



    void forward(int speed = 255) {
        accelerateForward(speed);
        
    }

    void backward(int speed = 255) {
        ledcWrite(pwmChannelA1, 0);     // Deactivate forward
        ledcWrite(pwmChannelA2, speed); // Activate reverse for motor A
        ledcWrite(pwmChannelB1, 0);     // Deactivate forward
        ledcWrite(pwmChannelB2, speed); // Activate reverse for motor B
        Serial.println("Moving back");
    }

    void stop() {
        ledcWrite(pwmChannelA1, 0);
        ledcWrite(pwmChannelA2, 0);
        ledcWrite(pwmChannelB1, 0);
        ledcWrite(pwmChannelB2, 0);
        Serial.println("Stopping motors");
    }

    void turnRight(int speed = 255) {
        ledcWrite(pwmChannelA1, speed); // Forward A
        ledcWrite(pwmChannelA2, 0);     // Deactivate reverse A
        ledcWrite(pwmChannelB1, 0);     // Deactivate forward B
        ledcWrite(pwmChannelB2, speed); // Reverse B
        Serial.println("Turning Right");
    }

    void turnLeft(int speed = 255) {
        ledcWrite(pwmChannelA1, 0);     // Deactivate forward A
        ledcWrite(pwmChannelA2, speed); // Reverse A
        ledcWrite(pwmChannelB1, speed); // Forward B
        ledcWrite(pwmChannelB2, 0);     // Deactivate reverse B
        Serial.println("Turning Left");
    }

    void turnSmoothRight(int speed = 255, int halfSpeed = 112) {
        ledcWrite(pwmChannelA1, halfSpeed);
        ledcWrite(pwmChannelA2, 0);
        ledcWrite(pwmChannelB1, speed);
        ledcWrite(pwmChannelB2, 0);
    }

        void turnSmoothLeft(int speed = 255, int halfSpeed = 112) {
        ledcWrite(pwmChannelA1, speed);
        ledcWrite(pwmChannelA2, 0);
        ledcWrite(pwmChannelB1, halfSpeed);
        ledcWrite(pwmChannelB2, 0);
    }

    void forwardSaveRight() {
        backward();
        delay(700);
        turnRight();
        delay(1000);
    }

    void forwardSaveLeft() {
        backward();
        delay(700);
        turnLeft();
        delay(1000);
    }
};

#endif // MOTORSTYRING_CLASSES_JOYSTICK_H
