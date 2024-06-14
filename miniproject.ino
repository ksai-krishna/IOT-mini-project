/*
    KARUNADU IOT Workshop
    Problem Statement : Create a device which detects fire and also detect if any accident
    has occured and raise alarm(sound) for both the events when they occur.
    Technique used to solve the problem : 
    I have used the simple smokedetector detect to detect smoke and when the value goes greater than threshold
    a alarm is turn on using the tone() and for the accident detection i have assumed that the z axis will 
    change so i have used an adxl which is connected to arduino kept it still and noted the standing value as the
    threshold value and kept a 10 as the error value suppose if the threshold value is 790 then well check
    if z axis is tilted 779 or 801 then a buzzer is activated and displayed on the lcd that accident occured.
*/



#include <LiquidCrystal.h>

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/* 
 *  rs -> The rs (Register Select) pin determines if the data is command or character data
 *  en -> en (Enable) pin signals when data is ready to be read by the LCD
 *  d4 to d7 -> are used to send data in 4-bit mode to the LCD


*/
int gas = 0;
const int mq2pin = A0;  // Analog input Pins
const int x_pin = A2;
const int y_pin = A3;
const int z_pin = A4;
int z_out = 0;
int buzzer = 8;  // Buzzer pin
int led = 4;
void setup() {

  lcd.begin(16, 2);  // declares a 16*2 display
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);
  pinMode(z_pin, INPUT);
  Serial.begin(9600);
  pinMode(mq2pin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  SmokeDetection(mq2pin);
  accidentDetection(z_pin);
  delay(1000);
}


int SmokeDetection(int mq2pin) {
  float sensorValue;

  sensorValue = analogRead(mq2pin);  // Reading the smoke intensisty value here were using analog read gives integer values but digitalread only gives '0' or '1'
  Serial.println("The sensor value is " + String(sensorValue));
  if (sensorValue > 303.00) {
    tone(buzzer, 500, 500);  //playing a buzzer sound when the sensorValue crosses the threshold value of alchol here assumed as smoke
    lcd.clear();
    lcd.print("The More Smoke is detected ");
    digitalWrite(led, HIGH);  // Sets the Light HIGH as hes drunk
    delay(5000);
  } else {
    digitalWrite(led, LOW);
  }
}

int accidentDetection(int z_pin) {
  z_out = analogRead(z_pin);
  Serial.println(z_out);
  if (z_out < 780.00 || z_out > 790.00)  // Threshold Value
  {
    tone(buzzer, 500, 500);
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("The vehicle is");
    lcd.setCursor(0, 1);
    lcd.print(" Falling ");
    digitalWrite(led, HIGH);
    delay(3000);
  } else {
    digitalWrite(led, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The vehicle is");
    lcd.setCursor(0, 1);
    lcd.print(" Safe");
    delay(1000);
  }
}
