//------------------------------------------
// Title: API Assignment
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: Will have an RGB Led that turns on
//  and off, as well as an RGB which will be 
//  controlled by sliders. It will then update 
//  google sheets with the state of the LED and
//  the values of R, G, and B for the RGB.
// Outputs: 
//        -- LED on or off
//        -- RGB changing colors
//        -- Update google sheets
// Date: 11/20/2025 7:15 PM
// Compiler: xtensa-lx106-elf-g++ (GCC for ESP8266)
//  on Platform IO using Arduino Framework
// Author: Anthony Meyer Slechta
// Version:
//      V1 - Just LED on or off
//      V2 - LED + RGB 
//      V3 - Google sheets (final)
//------------------------------------------

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include <Arduino.h>
#include "led_control.h"

//------------------------------------------
// Constructors
//------------------------------------------
LedController controller(D6, D5, D0, D1, D2, D7);

void setup() {
    controller.connectToWifi();

    // controller.setRGBValues(5, 10, 0);
    
}

void loop() {
  controller.checkButton();
  controller.checkRgbButton();
}
