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
#ifndef ADC_H
#define ADC_H
#include <Arduino.h>

class Adc {
    public:
        Adc(int pin);
        float getValue();
        void printValue();
        void setInterval(unsigned long intervalMs);
        float getValueOnInterval();
        void printValueOnInterval();

    private:
        int _pin;
        float _vref = 3.3;
        unsigned long _interval;
        unsigned long _lastReadTime = 0;
};
#endif