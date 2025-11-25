//------------------------------------------
// Title: LED Controller Class
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: Will have an RGB Led that turns on
//  and off, as well as an RGB which will be 
//  controlled by sliders. It will then update 
//  google sheets with the state of the LED and
//  the values of R, G, and B for the RGB.
// Inputs:
//        -- Pins for buttons and both LEDs
// Outputs: 
//        -- LED on or off
//        -- RGB changing colors
//        -- Update google sheets
// Date: 11/25/2025 12:18 PM
// Compiler: xtensa-lx106-elf-g++ (GCC for ESP8266)
//  on Platform IO using Arduino Framework
// Author: Anthony Meyer Slechta
// Version:
//      V1 - Just LED on or off
//      V2 - LED + RGB 
//      V3 - Google sheets (final)
//------------------------------------------

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


class LedController {
    public:
        LedController(int ledPin, int buttonPin, int redPin, int greenPin, int bluePin, int rgbButtonPin);
        void connectToWifi();
        void checkButton();
        void checkRgbButton();
        void ledOff();
        void ledOn();
        void setRGBValues(int r, int g, int b);
        String getState();
        String getRgbState();

        void sendRgbToSheet(int r, int g, int b);
        void sendLedToSheet(const String& state);

    private:
        int _ledPin;
        int _buttonPin;
        int _rgbButtonPin;
        int _redPin;
        int _greenPin;
        int _bluePin;
        bool btnPrsd;
        bool rgbPrsd;
        bool _ledOn;
        const char* ssid;
        const char* password;
        String url = "https://anthonymeyer.io/LED/results.txt";
        String rgbUrl = "https://anthonymeyer.io/LED/rgb.txt";
        String sheetUrl = "https://script.google.com/macros/s/AKfycbz05PJe-VmxQwDnqdsGKWAB_5DNsDVmmaBh7WXyGOC9sAPE2O_sci7HlTEBF7juXo_EFw/exec";

};
#endif