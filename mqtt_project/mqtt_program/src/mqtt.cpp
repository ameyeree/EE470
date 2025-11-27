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

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include "mqtt.h"

// The below lines are to handle the callback properly
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
    // Received the incoming message
    Serial.print("Message arrived ["); 
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++) {
        // the received value is in (char)payload[i]
        Serial.print((char)payload[i]);  
    }
    Serial.println();

    if (length > 0 && (char)payload[0] == '1') {
        led.ledOn();
    } else if (length > 0 && (char)payload[0] == '0') {
        led.ledOff();
    }
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
    // Initialize the BUILTIN_LED pin as an output
    pinMode(BUILTIN_LED, OUTPUT);     
    // Serial.begin(9600);
    setupWifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(mqttCallback);
}

void Mqtt::loop() {
    if (!client.connected()) {
        // check for the latest value in inTopic 
        reconnect(); 
    }
    client.loop();

    // Publish to outTopic 
    unsigned long now = millis(); 

    if (now - lastMsg > publishTimeIntervalMs) {
        lastMsg = now;
        value = potentiometer.getValue();
        // resolution is 3.2 mV, so round in the mV
        snprintf (msg, MSG_BUFFER_SIZE, "%.3f", value);
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