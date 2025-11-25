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

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include "led_control.h"

LedController::LedController(int ledPin, int buttonPin, int redPin, int greenPin, int bluePin, int rgbButtonPin) {
    Serial.begin(9600);
    ssid = "ajm-laptop";
    password = "/690D4e8";  
    this->_ledPin = ledPin;
    this->_buttonPin = buttonPin;
    this->_redPin = redPin;
    this->_greenPin = greenPin;
    this->_bluePin = bluePin;
    this->_rgbButtonPin = rgbButtonPin;
    this->btnPrsd = false;
    this->rgbPrsd = false;

    pinMode(_buttonPin, INPUT_PULLUP);
    pinMode(_rgbButtonPin, INPUT_PULLUP);
    pinMode(_ledPin, OUTPUT);
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);

    ledOff();
    setRGBValues(0, 0, 0);
}

void LedController::connectToWifi() {
    Serial.print("Connecting to Wifi");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi.");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    WiFi.setSleep(false);    
}

void LedController::checkButton() {
    // Will send data to node_1
    if (digitalRead(_buttonPin) == LOW) {
        btnPrsd = true;
        while (digitalRead(_buttonPin) == LOW){
            // simple debounce fix
            delay(100);
        }
        Serial.println("LED button press detected!");
        String state = "";
        state = getState();
        Serial.println("State received: " + state);
        
        if (state == "on") {
            ledOn();
        }else if (state == "off") {
            ledOff();
        } else {
            Serial.println("State received not supported. Only 'on' or 'off' supported.");
        }
        // Send to sheets after handling LED to reduce delay
        sendLedToSheet(state);
        btnPrsd = false;
    }
}

void LedController::checkRgbButton() {
    if (digitalRead(_rgbButtonPin) == LOW) {
        rgbPrsd = true;
        String state = "";
        int red = 0;
        int green = 0;
        int blue = 0;
        while (digitalRead(_rgbButtonPin) == LOW){
            // simple debounce fix
            delay(100);
        }
        Serial.println("RGB button press detected!");
        
        state = getRgbState();
        Serial.println("State received: " + state);
        
        int rPosition = state.indexOf("R:");
        int gPosition = state.indexOf("G:");
        int bPosition = state.indexOf("B:");

        if (rPosition != -1) {
            int end = state.indexOf("\n", rPosition);
            String rString = state.substring(rPosition + 2, (end == -1 ? state.length() : end));
            red = rString.toInt();
        }

        if (gPosition != -1) {
            int end = state.indexOf("\n", gPosition);
            String gString = state.substring(gPosition + 2, (end == -1 ? state.length() : end));
            green = gString.toInt();
        }

        if (bPosition != -1) {
            int end = state.indexOf("\n", bPosition);
            String bString = state.substring(bPosition + 2, (end == -1 ? state.length() : end));
            blue = bString.toInt();
        }

        Serial.printf("Received values: R=%d G=%d B=%d\n", red, green, blue);

        setRGBValues(red, green, blue);
        sendRgbToSheet(red, green, blue);
        rgbPrsd = false;
    }
}

void LedController::ledOff() {
    digitalWrite(_ledPin, LOW);
    _ledOn = false;
}


void LedController::ledOn() {
    digitalWrite(_ledPin, HIGH);
    _ledOn = true;
}


void LedController::setRGBValues(int r, int g, int b) {
    analogWrite(_redPin, r);
    analogWrite(_greenPin, g);
    analogWrite(_bluePin, b);
}


String LedController::getState() {
    String state = "";
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient https;
        WiFiClientSecure client;
        client.setInsecure();

        Serial.println("Requesting: " + url);

        if (https.begin(client, url)) {
            int httpCode = https.GET();

            Serial.println("Response code: " + String(httpCode));
            Serial.printf("code=%d err=%s\n", httpCode, https.errorToString(httpCode).c_str());

            if (httpCode > 0) {
                String body = https.getString();
                Serial.println(body);
                state = body;
            }else {
                Serial.println("ERROR -> Response Code: " + String(httpCode));
            }
            https.end();
        } else {
            Serial.println("[HTTPS] unable to connect.");
        }
    } else {
        Serial.println("Not connected to the internet.");
    }
    return state;
}


String LedController::getRgbState() {
    String state = "";
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient https;
        WiFiClientSecure client;
        client.setInsecure();

        Serial.println("Requesting: " + rgbUrl);

        if (https.begin(client, rgbUrl)) {
            int httpCode = https.GET();

            Serial.println("Response code: " + String(httpCode));
            Serial.printf("code=%d err=%s\n", httpCode, https.errorToString(httpCode).c_str());

            if (httpCode > 0) {
                String body = https.getString();
                Serial.println(body);
                state = body;
            }else {
                Serial.println("ERROR -> Response Code: " + String(httpCode));
            }
            https.end();
        } else {
            Serial.println("[HTTPS] unable to connect.");
        }
    } else {
        Serial.println("Not connected to the internet.");
    }
    return state;
}


void LedController::sendRgbToSheet(int r, int g, int b) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Not connected to the internet.");
        return;
    }

    HTTPClient https;
    https.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    WiFiClientSecure client;
    client.setInsecure();

    // Build URL: ?r=40&g=214&b=103
    String fullUrl = sheetUrl +
                     "?key=rgb"
                     "&r=" + String(r) +
                     "&g=" + String(g) +
                     "&b=" + String(b);

    Serial.println("Requesting (sheet): " + fullUrl);

    if (https.begin(client, fullUrl)) {
        int httpCode = https.GET();

        Serial.println("Response code: " + String(httpCode));
        Serial.printf("code=%d err=%s\n", httpCode, https.errorToString(httpCode).c_str());

        if (httpCode > 0) {
            String body = https.getString();
            Serial.println("Body: " + body);
        } else {
            Serial.println("ERROR -> Response Code: " + String(httpCode));
        }
        https.end();
    } else {
        Serial.println("[HTTPS] unable to connect.");
    }
}


void LedController::sendLedToSheet(const String& state) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Not connected to the internet.");
        return;
    }

    HTTPClient https;
    https.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    WiFiClientSecure client;
    client.setInsecure();

    // Build URL: ?key=led&state=ON
    String fullUrl = sheetUrl +
                     "?key=led" +
                     "&state=" + state;

    Serial.println("Requesting (sheet): " + fullUrl);

    if (https.begin(client, fullUrl)) {
        int httpCode = https.GET();

        Serial.println("Response code: " + String(httpCode));
        Serial.printf("code=%d err=%s\n", httpCode, https.errorToString(httpCode).c_str());

        if (httpCode > 0) {
            String body = https.getString();
            Serial.println("Body: " + body);
        } else {
            Serial.println("ERROR -> Response Code: " + String(httpCode));
        }
        https.end();
    } else {
        Serial.println("[HTTPS] unable to connect.");
    }
}
