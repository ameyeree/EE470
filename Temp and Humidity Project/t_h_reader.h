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
// Date: 10/16/2025 5:05 PM
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
#ifndef T_H_READER_H
#define T_H_READER_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

//------------------------------------------
// Constants
//------------------------------------------
#define DHTTYPE DHT11


struct SensorData {
    // Specifically used when wanting to get both 
    // temp and humidity readings at the same time
    float temperature;
    float humidity;
};


class TempHumidityReader {
    public:
        TempHumidityReader(int sensorPin, int buttonPin, int tiltBtnPin);
        void connectToWifi();
        void setTimeZone();
        void checkButton();
        void checkTiltSwitch();
        void sendToDB(const char* node_name, float temp, float hum, String dataTime);
        SensorData getTempAndHum();
        float getTemperature();
        float getHumidity();
        String getDateTime();

    private:
        int sensorPin;
        int buttonPin;
        int tiltPin;
        bool btnPrsd;
        bool tiltPrsd;
        const char* ssid;
        const char* password;
        const char* timeZone;
        String url = "https://anthonymeyer.io/esp_insert_sensor_db.php";
        String nodeVar = "nodeId=";
        String timeVar = "timeReceived=";
        String tempVar = "nodeTemp=";
        String humVar = "nodeHum=";
        DHT dht;
};
#endif
