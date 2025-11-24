//------------------------------------------
// Title: Blink LED Class 
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: To learn how to implement classes
//  for the ESP-8266, and have a simple class
//  that blinks an LED at a specific speed.
// Inputs: 
//      pin: (int) pin number for LED
//      rate: (int) time in ms to blink the LED
// Outputs:
//      blinkRate: blinks the led at the given rate
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
#include "mqtt.h"

extern Mqtt mqtt;

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    mqtt.callback(topic, payload, length);
}

//------------------------------------------
// Class Constructor
//------------------------------------------
Mqtt::Mqtt() : client(espClient), potentiometer(A0), led(D0) {
    pinMode(switchPin, INPUT_PULLUP);
    lastSwitchState = digitalRead(switchPin);
}


void Mqtt::setupWifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}


void Mqtt::callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived ["); // Received the incoming message
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);  // the received value is in (char)payload[i]
    }
    Serial.println();

    if (length > 0 && (char)payload[0] == '1') {
        led.ledOn();
    } else if (length > 0 && (char)payload[0] == '0') {
        led.ledOff();
    }
    // Switch on the LED if an 1 was received as first character
    // add your code here   
}

void Mqtt::reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            // ... and resubscribe
            client.subscribe(subscribeTopic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }    
}


void Mqtt::setup() {
    pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
    // Serial.begin(9600);
    setupWifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(mqttCallback);
}

void Mqtt::loop() {
    if (!client.connected()) {
        reconnect(); // check for the latest value in inTopic 
    }
    client.loop();

    // Publish to outTopic 
    unsigned long now = millis(); 

    if (now - lastMsg > publishTimeIntervalMs) {
        lastMsg = now;
        value = potentiometer.getValue();
        snprintf (msg, MSG_BUFFER_SIZE, "%f", value); // prints Number # 1, Number # 2, .....
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish(publishTopic, msg);
    }   

    // Get switch status
    int state = digitalRead(switchPin);

    if (lastSwitchState == LOW && state == HIGH && switchTimerActive == false) {
        client.publish(switchPublishTopic, "1");
        Serial.println("Switch released: Published 1");

        switchTimerActive = true;
        switchTimerStart = now;
    }

    lastSwitchState = state;

    if (switchTimerActive && (now - switchTimerStart >= switchReleaseDelayMs)) {
        client.publish(switchPublishTopic, "0");
        Serial.println("5 seconds after button release: Published 0");
        switchTimerActive = false;
    }
}