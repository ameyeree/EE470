//------------------------------------------
// Title: ADC Class
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: Gets the values of the ADC, has
//  an interval option, specifically for
//  debugging on this assignment. 
// Inputs: 
//      pin: Pin number for ADC, (should be A0)
// Outputs:
//      Returns voltage value
// Date: 10/16/2025 5:00 PM
// Compiler: xtensa-lx106-elf-g++ (GCC for ESP8266)
//  on Platform IO using Arduino Framework
// Author: Anthony Meyer Slechta
// Version:
//      V1 - Initial Iteration
//

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include "adc.h"

//------------------------------------------
// Class Constructor
//------------------------------------------
Adc::Adc(int pin) {
    this->_pin = pin;
    // Below note needed to analog readings
    //pinMode(_pin, OUTPUT);
}

//------------------------------------------
// Get voltage value with no delay
//------------------------------------------
float Adc::getValue() {
    return analogRead(_pin) * (_vref/1023.0);
}

//------------------------------------------
// Print voltage value
//------------------------------------------
void Adc::printValue() {
    Serial.println(this->getValue());
}

//------------------------------------------
// Set interval for interval functions
//------------------------------------------
void Adc::setInterval(unsigned long intervalMs) {
    this->_interval = intervalMs;
}


//------------------------------------------
// Get value but only at a specific time 
//  interval. This was my original idea
//  for the program, but was ultimately
//  not used.
//------------------------------------------
float Adc::getValueOnInterval() {
    unsigned long now = millis();

    if (now - _lastReadTime >= _interval) {
        _lastReadTime = now;
        return this->getValue();
    }

    return -1;
}


//------------------------------------------
// Print Value on interval
//------------------------------------------
void Adc::printValueOnInterval() {
    unsigned long now = millis();

    if (now - _lastReadTime >= _interval) {
        _lastReadTime = now;
        Serial.println(this->getValue());
    }
}