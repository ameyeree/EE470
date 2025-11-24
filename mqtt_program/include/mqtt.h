//------------------------------------------
// Title: MQTT Class
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: Publish and subsrcribe to three nodes
//  one to publish voltage values from potentiometer,
//  one to publish a 1 on button press, and 0 5 seconds
//  later, and finally one to subscribe to a node that
//  when a 1 is received it will turn on an LED, and a
//  0 will turn it off. This code was refactored from
//  given code and was expanded on.
// Inputs: 
//      No inputs given into class, everything is handled
//      internally
// Outputs:
//      LED that turns on and off
//      Publish to nodes as described in purpose
// Date: 11/20/2025 5:00 PM
// Compiler: xtensa-lx106-elf-g++ (GCC for ESP8266)
//  on Platform IO using Arduino Framework
// Author: Anthony Meyer Slechta
// Version:
//      V1 - Initial Iteration
//

#ifndef MQTT_H
#define MQTT_H

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include "adc.h"
#include "led.h"

#define MSG_BUFFER_SIZE 50
#define BUILTIN_LED D0

class Mqtt {

    public:
        Mqtt();
        void setupWifi();
        void callback(char* topic, byte* payload, unsigned int length);
        void reconnect();
        void setup();
        void loop();


    private:
        const char* ssid = "";
        const char* password = "";

        const char* mqtt_server = "broker.mqtt-dashboard.com";
        const char* publishTopic = "testtopic/temp/outTopic/878787";
        const char* subscribeTopic = "testtopic/temp/inTopic/878787"; 
        const char* switchPublishTopic = "testtopic/temp/inTopic/sw8787"; 

        // changed to unsigned long to keep equivalency
        // with millis()
        unsigned long publishTimeIntervalMs = 60000; // in milliseconds 
        unsigned long switchReleaseDelayMs = 5000;

        unsigned long lastMsg = 0;
        char msg[MSG_BUFFER_SIZE];
        float value = 0.0;

        int switchPin = D2;
        int lastSwitchState = HIGH;
        bool switchTimerActive = false;
        unsigned long switchTimerStart = 0; 

        WiFiClient espClient;
        PubSubClient client;
        Adc potentiometer;
        Led led;
};
#endif