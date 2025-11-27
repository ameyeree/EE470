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
#ifndef LED_H
#define LED_H
#include <Arduino.h>

class Led {

    public:
        Led(int pin);
        void ledOn();
        void ledOff();

    private:
        int _pin;
};
#endif