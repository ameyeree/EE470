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
// Date: 10/16/2025 5:07 PM
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
#include "t_h_reader.h"


TempHumidityReader::TempHumidityReader(int sensorPin, int buttonPin, int tiltPin) 
: dht(sensorPin, DHTTYPE)
{
    ssid = "ajm-laptop";
    password = "/690D4e8";
    this->sensorPin = sensorPin;
    this->buttonPin = buttonPin;
    this->tiltPin = tiltPin;
    this->btnPrsd = false;
    this->tiltPrsd = false;

    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(tiltPin, INPUT);
    dht.begin();

    // DHT11 sensor requires a 1-2 second delay before first reading after initilization
    delay(2000);
};


void TempHumidityReader::connectToWifi(){
    Serial.print("Connecting to Wifi");
    IPAddress local(192,168,137,50);
    IPAddress gw(192,168,137,1);
    IPAddress mask(255,255,255,0);
    IPAddress dns2(1,1,1,1);
    IPAddress dns1(8,8,8,8);
    WiFi.config(local, gw, mask, dns1, dns2);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi.");

    Serial.println(WiFi.macAddress());

    WiFi.setSleep(false);
};

void TempHumidityReader::setTimeZone(){
    Serial.println("***********************************************");
    Serial.println("Please select desired timezone: ");
    Serial.println("1) Eastern Time Zone (ET) - New York City, NY");
    Serial.println("2) Central Time Zone (CT) - Chicago, IL");
    Serial.println("3) Mountain Time Zone (MT) - Denver, CO");
    Serial.println("4) Pacific Time Zone (PT) - Los Angeles, CA");
    Serial.println("5) Alaska Time Zone (AKT) - Anchorage, AK");
    Serial.println("6) Hawaii-Aleutian Time Zone (HAT) - Honolulu, HI");
    Serial.println("7) Atlantic Time Zone (AT) - San Juan, Puerto Rico (US territory, not part of the contiguous US)");

    while (Serial.available() == 0) {
        // Waiting for user input
    }

    // If the user puts an incorrect value (including a string) it will go to the default
    // which is PST
    int userChoice = Serial.parseInt();

    switch (userChoice) {

        case 1:
            timeZone = "America/New_York";
            break;
        case 2:
            timeZone = "America/Chicago";
            break;
        case 3: 
            timeZone = "America/Denver";
            break;
        case 4:
            timeZone = "America/Los_Angeles";
            break;
        case 5:
            timeZone = "America/Anchorage";
            break;
        case 6:
            timeZone = "Pacific/Honolulu";
            break;
        case 7:
            timeZone = "America/Puerto_Rico";
            break;
        default:
            Serial.println("Default timezone selected, due to entry given.");
            timeZone = "America/Los_Angeles";
            break;
            
    }

    Serial.print("Timezone Selected: ");
    Serial.println(timeZone);
}


void TempHumidityReader::checkButton() {
    // Will send data to node_1
    if (tiltPrsd == false && digitalRead(buttonPin) == LOW) {
        btnPrsd = true;
        while (digitalRead(buttonPin) == LOW){
            // simple debounce fix
            delay(100);
        }
        Serial.println("Button press detected!");
        SensorData sensorData = getTempAndHum();
        String dateTime = getDateTime();
        sendToDB("node_1", sensorData.temperature, sensorData.humidity, dateTime);
        btnPrsd = false;
    }

}


void TempHumidityReader::checkTiltSwitch() {
    // Will send data to node_2

    if (btnPrsd == false && digitalRead(tiltPin) == HIGH) {
        // My tilt sensor is very sensitive, this is to avoid
        // it trigger with a small jostle of the board.
        delay(100);
    }
    if (btnPrsd == false && digitalRead(tiltPin) == HIGH) {
        tiltPrsd = true;
        while (digitalRead(tiltPin) == HIGH){
            // simple debounce fix
            delay(100);
        }
        Serial.println("Tilt detected!");
        SensorData sensorData = getTempAndHum();
        String dateTime = getDateTime();
        sendToDB("node_2", sensorData.temperature, sensorData.humidity, dateTime);

        tiltPrsd = false;
    }

}


void TempHumidityReader::sendToDB(const char* node_name, float temp, float hum, String dateTime) {
    // need also temp, humidity, and time

    if (WiFi.status () == WL_CONNECTED) {
        HTTPClient https;
        WiFiClientSecure client;

        client.setInsecure();
        https.setTimeout(60000);

        String fullUrl = url + "?" + nodeVar + node_name + "&" + tempVar + temp + "&" + humVar + hum + "&" + timeVar + dateTime;
        
        Serial.println("Requesting: " + fullUrl);

        if (https.begin(client, fullUrl)) {
            int httpCode = https.GET();
            // int httpCode = https.POST(fullUrl);

            Serial.println("Response Code: " + String(httpCode));

            if (httpCode > 0) {
                Serial.println(https.getString());
            }
            https.end();

        }else {
            Serial.println("[HTTPS] Unable to connect.");
        }

    } else {
        Serial.println("Not connected to WiFi.");
    }
    
}


String TempHumidityReader::getDateTime() {
    String dateTime = "";

    if (WiFi.status () == WL_CONNECTED) {
        HTTPClient https;
        JsonDocument doc;
        WiFiClientSecure client;

        client.setInsecure();
        https.setTimeout(60000);

        String fullUrl = "https://timeapi.io/api/Time/current/zone?timeZone=" + String(timeZone);
        
        Serial.println("Requesting: " + fullUrl);

        if (https.begin(client, fullUrl)) {
            int httpCode = https.GET();

            Serial.println("Response Code: " + String(httpCode));

            Serial.printf("code=%d err=%s\n", httpCode, https.errorToString(httpCode).c_str());

            if (httpCode > 0) {
                // Serial.println(https.getString());
                deserializeJson(doc, https.getString());
                dateTime = String(doc["dateTime"]);
                dateTime.remove(dateTime.length() - 1);
            }else {
                Serial.println("ERROR -> Response Code: " + String(httpCode));
                dateTime = "";
            }
            https.end();

        }else {
            Serial.println("[HTTPS] Unable to connect.");
        }


    } else {
        Serial.println("Not connected to WiFi.");
        return "";
    }
    Serial.println("Date Time Recieved: " + dateTime);
    return dateTime;
}


SensorData TempHumidityReader::getTempAndHum() {
    SensorData data;
    // DHT11 requires a delay between reading of around 1-1.5 seconds
    delay(1500);
    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();

    return data;
};


float TempHumidityReader::getTemperature() {
    return dht.readTemperature();
}

float TempHumidityReader::getHumidity() {
    return dht.readHumidity();
}

