
//------------------------------------------
// Title: Photoresistor Lux Reader
//------------------------------------------
// Program Details:
//------------------------------------------
// Purpose: To learn how to calibrate sensors
//  and setup outputs. Gives an estimated lux
//  value in the serial terminal, and changes
//  an RGB from white to brighter shades or red
//  depending on strength of LUX. Buzzer will turn
//  on if lux below threshold, or B is inputted
//  into terminal.
// Inputs: 
//      Photoresistor module S pin (pin A0)
// Outputs:
//      RGB: pins D2, D3, and D4
//      Active Buzzer: pin D1
// Date: 09/28/2025 6:00 AM
// Compiler: Simulator Version 6.8
// Author: Anthony Meyer Slechta
// Version:
//      V1 - Voltage readings on sensor
//      V2 - Created median algorithm
//      V3 - Implemented lux conversion using power series
//      V4 - Changed lux conversion to exponential
//      V5 - Added buzzer, and user input
//      V6 - Added RGB with dynamic colors (final version)

//------------------------------------------
// File Dependencies:
//------------------------------------------
#include <Arduino.h>
#include <algorithm>
#include <math.h>

//------------------------------------------
// Function Declarations
//------------------------------------------
int getMedianValue(int data[]);
float convertToVoltage(int value);
int convertToLuxPower(float voltage);
int convertToLuxExponential(float voltage);
void buzzerOn();
void buzzerOff();
void changeRGPColor(int luxValue);

//------------------------------------------
// Setup
//------------------------------------------
#define analogPinIn A0
#define buzzerPin D1
#define redPin D2
#define greenPin D3
#define bluePin D4
const float VREF = 3.3;
float lightVoltageValue = 0;
int adcValue = 0;
int buzzerCount = 0;
int const arraySize = 15;
int const MAX_RANGE = 3000;
int data[arraySize];
int currentDataIndex = 0;
int medianValue = 0;
float luxValue = 0;
char userChar;

void setup() {
  // Enable serial communication at 9600 baud rate
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Start delay to avoid anything weird happening
  delay(1000);
}

//------------------------------------------
//  Primary Program loop
//------------------------------------------
void loop() {
  adcValue = analogRead(analogPinIn);
  data[currentDataIndex] = adcValue;

  if (Serial.available() > 0){
    userChar = Serial.read();

    if (userChar == 'B'){
      buzzerOn();
      buzzerCount = 5;
    }
  }

  if (currentDataIndex == 14){
    buzzerCount--;

    // Get desired values, and do conversions
    medianValue = getMedianValue(data);
    lightVoltageValue = convertToVoltage(medianValue);
    luxValue = convertToLuxExponential(lightVoltageValue);

    // Handle displaying results
    changeRGPColor(luxValue);
    Serial.print("LUX Value: ");
    Serial.println(luxValue);

    // Handle Buzzer
    if (luxValue < 150){
      buzzerOn();
    } else if (buzzerCount <= 0){
      // If buzzerCount is instantiated should be approximately 4.5-6 seconds 
      // depending on when it was started
      buzzerOff();
    }

    currentDataIndex = 0;
  }else{
    currentDataIndex++;
  }

  // Will take 15 measurements, so a value should be outputted every 1.5 seconds
  delay(100); 

}

//------------------------------------------
// Helper Functions
//------------------------------------------

int getMedianValue(int dataArray[]){
  std::sort(dataArray, dataArray + arraySize);
  return dataArray[arraySize/2];
}

float convertToVoltage(int value){
  // NOTE: A0 takes is 0-3.3V --> 3.2 mV steps
  return ((float)medianValue/1023.0) * VREF;
}

int convertToLuxPower(float voltage){
  // Formula found on Excel
  return 0.528 * powf(voltage, 7.01);
}

int convertToLuxExponential(float voltage){
  // Formula found on Excel
  return 0.0236 * exp(3.62 * voltage );
}

void buzzerOn(){
  digitalWrite(buzzerPin, HIGH);
}

void buzzerOff(){
    digitalWrite(buzzerPin, LOW);
}

void changeRGPColor(int luxValue){
  float percent = (float)luxValue/3000;
  float weight = 10;
  int redValue;
  int blue_green;

  if (luxValue > 3000){
    percent = 100.0;
  }else{
    percent = (float)luxValue/3000.0;
  }

  if (luxValue <= 250){
    blue_green = 255.0 * percent * weight;
    redValue = 255;
  }else{
    blue_green = 255;
    redValue = 255.0 * percent;
  }
  // Serial.print("Blue Green Value: ");
  // Serial.println(blue_green);
  analogWrite(redPin, redValue);
  analogWrite(greenPin, 255 - blue_green);
  analogWrite(bluePin, 255 - blue_green);
}
