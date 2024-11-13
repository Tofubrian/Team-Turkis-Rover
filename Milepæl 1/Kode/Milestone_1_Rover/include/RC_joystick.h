#include <Arduino.h>
#include "MotorStyring_Classes.h"

// Definer pins for receiver-kanalerne
const int steeringPin = 5;   // Kanal 1 fra receiver (til drejning)
const int throttlePin = 6;   // Kanal 2 fra receiver (til frem og tilbage)

// Initialiser MotorController
MotorController motors(25, 26, 14, 12);  // Definer dine motorpins her

void setup() {
    Serial.begin(9600); // Start Serial Monitor for debugging
    pinMode(steeringPin, INPUT);
    pinMode(throttlePin, INPUT);
    motors.initMotors(); // Initialiser motorerne
}

void loop() {
    // Læs PWM-pulslængde fra hver kanal
    unsigned long steeringValue = pulseIn(steeringPin, HIGH);
    unsigned long throttleValue = pulseIn(throttlePin, HIGH);

    // Map throttleValue (frem/tilbage) til motorhastighed (0 til 255)
    int speed = map(throttleValue, 1000, 2000, 0, 255);

    // Map steeringValue (drejning) til drejehastighed (0 til 255)
    int turnSpeed = map(steeringValue, 1000, 2000, 0, 255);

    // Styr baseret på controllerens input
    if (throttleValue > 1500) {
        motors.forward(speed);  // Fremad, når throttle er over midtpunkt
        Serial.println("Kører fremad");
    } 
    else if (throttleValue < 1500) {
        motors.backward(speed); // Tilbage, når throttle er under midtpunkt
        Serial.println("Kører tilbage");
    } 
    else {
        motors.stop(); // Stop motorerne, hvis throttle er omkring midten
        Serial.println("Stoppet");
    }

    // Drejning baseret på steering (CH1)
    if (steeringValue > 1600) {
        motors.turnRight(turnSpeed); // Drej højre, når steering er over midtpunkt
        Serial.print("Drejer højre med hastighed: ");
        Serial.println(turnSpeed);
    } 
    else if (steeringValue < 1400) {
        motors.turnLeft(turnSpeed); // Drej venstre, når steering er under midtpunkt
        Serial.print("Drejer venstre med hastighed: ");
        Serial.println(turnSpeed);
    }

    delay(100); // Vent lidt før næste opdatering for stabilitet
}
