//------------------------------------------
// Title: MQTT Assignment
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: Create three nodes to publish
//  and subscribe to to turn an LED on or off
//  send a 1 or 0 value at the press of a button,
//  and publish potentiometer values every 15 to 20 seconds
// Outputs: 
//        -- LED on or off
//        -- Publish values of potentiometer
//        -- Button press 1 on release, 0 5 seconds later
// Date: 11/20/2025 7:15 PM
// Compiler: Simulator Version 6.8/Platform IO
// Author: Anthony Meyer Slechta
// Version:
//      V1 - Just LED and delayed manual publish
//      V2 - Final Version
//------------------------------------------

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include <Arduino.h>
#include "mqtt.h"

//------------------------------------------
// Constructors
//------------------------------------------
Mqtt mqtt;

void setup() {
    // Enable serial communication at 115200 baud rate
    Serial.begin(115200);
    mqtt.setup();
}


void loop() {
    mqtt.loop();
}
