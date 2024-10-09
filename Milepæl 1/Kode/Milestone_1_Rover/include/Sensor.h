#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <motorstyring.h>

// Functions for the sensors goes in here

// Function for moving forward, right and left
// do while loop instead maybe? 
void sensorAuto () {
    if (sensorA > 50 && sensorB < 50) {
        turnLeft();
    }
    else if (sensorA < 50 && sensorB > 50) {
        turnRight();
    }
    else {
        forward();
    }
}