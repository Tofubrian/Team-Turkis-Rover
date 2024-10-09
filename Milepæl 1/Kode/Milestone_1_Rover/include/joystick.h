// Libraries for controlling joystick over wifi
#include <Arduino.h>


// All joystick coding goes in here

// Funciton for changing between manual and automatic driving

enum driveMode {manuel, automatic}; // Holder styr på de 2 måder der kan køres
driveMode currentMode = manuel;

// Bool to change between true and false, change between defined enum modes
bool joystickListen() {
    static bool clickstate = false;
    return clickstate = !clickstate;
}

// Function for toggling between manual and auto
void toggleMode() {               // 4
    currentMode = (currentMode == MANUAL) ? AUTOMATIC : MANUAL;
}

// Activate with a while loop?
