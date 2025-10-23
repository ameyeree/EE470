//------------------------------------------
// Title: Temp and Humidity Sensor
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: To collect sensor data (in this 
//  case temperature and humidity data) and
//  post the data to the mySQL database. 
//  Also utilizes getting the time from 
//  Timeapi.io and using that to time stamp
//  the sensor readings.
// Inputs: 
//      User input through usb to get timezone
//      Temperature and humidity sensor readings
//      Button press
//      Tilt Switch 
// Outputs:
//      Serial Output
//      Posting data to mySQL database
// Date: 10/16/2025 5:00 PM
// Compiler: xtensa-lx106-elf-g++ (GCC for ESP8266)
//  on Platform IO using Arduino Framework
// Author: Anthony Meyer Slechta
// Version:
//      V1 - Initial Iteration hard coded time
//      V3 - Final iteration with time
//

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include <Arduino.h>
#include "t_h_reader.h"

//------------------------------------------
// Constants
//------------------------------------------
#define SENSOR_PIN D1
#define BUTTON_PIN D2
#define TILT_PIN D6

//------------------------------------------
// Class instantiation
//------------------------------------------
TempHumidityReader th(SENSOR_PIN, BUTTON_PIN, TILT_PIN);

void setup() {

  Serial.begin(9600);

  th.connectToWifi();
  th.setTimeZone();

}

void loop() {
  th.checkButton();
  th.checkTiltSwitch();
}
