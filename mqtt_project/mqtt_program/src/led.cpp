//------------------------------------------
// Title: LED Class 
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: Simpled LED class to turn and L
//  LED on or off
// Inputs: 
//      pin: Pin number for LED
// Outputs:
//      Turns LED on or OFF
// Date: 11/20/2025 5:00 PM
// Compiler: xtensa-lx106-elf-g++ (GCC for ESP8266)
//  on Platform IO using Arduino Framework
// Author: Anthony Meyer Slechta
// Version:
//      V1 - Initial Iteration
//

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include "led.h"

//------------------------------------------
// Class Constructor
//------------------------------------------
Led::Led(int pin) {
    this->_pin = pin;
    pinMode(_pin, OUTPUT);
}

//------------------------------------------
// Turns LED on
//------------------------------------------
void Led::ledOn() {
    digitalWrite(_pin, HIGH);
}

//------------------------------------------
// Turns LED off
//------------------------------------------
void Led::ledOff() {
    digitalWrite(_pin, LOW);
}